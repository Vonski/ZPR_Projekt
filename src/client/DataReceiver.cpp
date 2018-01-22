#include "DataReceiver.hpp"

using namespace boost::asio;
using namespace boost::asio::ip;

DataReceiver::DataReceiver(std::string ip_address, int port_number, shared_ptr<CPUData> cpuu, shared_ptr<DiskData> diskk, shared_ptr<RAMData> ramm, sciter::debug_output_console& consolee) : socket(tcp::socket(service)), cpu2(cpuu), disk(diskk), ram(ramm), console(consolee)
{
	ep = tcp::endpoint(address::from_string(ip_address), port_number);
	error = error::host_not_found;
}


DataReceiver::~DataReceiver()
{
}

void DataReceiver::tryToConnect()
{
	try
	{
		if (error)
		{
			socket.close();
			socket.connect(ep, error);
		}
		if (error)
			throw boost::system::system_error(error);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

int DataReceiver::checkForErrors()
{
	try
	{
		if (error == boost::asio::error::eof)
			return 1; // Connection closed cleanly by peer.
		else if (error)
			throw boost::system::system_error(error); // Some other error.
		return 0;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
}

void DataReceiver::operator()()
{
	for (;;)
	{
		std::string msg = receiveData(10);
		unpackMessage(msg);
		cpu2->notify();
		disk->notify();
		ram->notify();
		sciterPrintData();
		if (checkForErrors())
			break;
		
		Sleep(1000);

		sendPing();
		if (checkForErrors())
			break;
	}
}

std::string DataReceiver::receiveData(size_t size)
{
	std::string msg;
	msg.resize(1024);

	size_t len = 0;
	while (len<size)
		len += socket.read_some(buffer(msg), error);
	
	return msg;
}

void DataReceiver::dataToObjects(std::string cmsg, std::string dmsg, std::string rmsg)
{
	std::stringstream ifs(cmsg);
	{
		boost::mutex::scoped_lock(cpu2->mutex);
		boost::archive::text_iarchive ia(ifs);
		ia >> *cpu2;
	}

	ifs = std::stringstream(dmsg);
	{
		boost::mutex::scoped_lock(disk->mutex);
		boost::archive::text_iarchive ia(ifs);
		ia >> *disk;
	}

	ifs = std::stringstream(rmsg);
	{
		boost::mutex::scoped_lock(ram->mutex);
		boost::archive::text_iarchive ia(ifs);
		ia >> *ram;
	}
}

void DataReceiver::unpackMessage(std::string msg)
{
	int firstEnd = intFromMessageToString(msg.substr(0, 5));
	int secondEnd = intFromMessageToString(msg.substr(5, 10));
	int thirdEnd = intFromMessageToString(msg.substr(10, 15));
	std::string cpudata = msg.substr(15, firstEnd);
	std::string diskdata = msg.substr(15 + firstEnd, secondEnd);
	std::string ramdata = msg.substr(15 + firstEnd + secondEnd, thirdEnd);
	dataToObjects(cpudata, diskdata, ramdata);
}

int DataReceiver::intFromMessageToString(std::string str)
{
	int i = 0;
	while (str[i] != '\0')
		i++;
	str = str.substr(0, i);
	return boost::lexical_cast<int>(str);
}

void DataReceiver::printCPU()
{
	std::cout << cpu2->cpu_current_clock_speed << " " << cpu2->cpu_current_voltage << " " << cpu2->cpu_manufacturer << std::endl;
	std::cout << disk->disk_free_space << std::endl;
	std::cout << ram->free_ram_size << std::endl;
}

void DataReceiver::sciterPrintData()
{
	string allData = cpu2->printToString() + "\n" + disk->printToString() + "\n" + ram->printToString() + "\n";
	console.print(allData.c_str());
}

void DataReceiver::sendPing()
{
	std::string msg = "ping";
	socket.write_some(buffer(msg), error);
}
