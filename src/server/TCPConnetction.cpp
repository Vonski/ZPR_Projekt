#include "TCPConnetction.hpp"

using namespace boost::asio;
using namespace boost::asio::ip;

int counter = 0;
int tmp = 0;

TCPConnection::pointer TCPConnection::create(boost::asio::io_service & io_service, CPUData & cpuu, DiskData & diskk, RAMData& ramm)
{
	return pointer(new TCPConnection(io_service,cpuu,diskk,ramm));
}

tcp::socket& TCPConnection::socket()
{
	return socket_;
}

void TCPConnection::start()
{
	counter++;
	id_ = counter;

	message1_ = prepareConcatenatedMessage();
	printCPU();

	async_write(socket_, buffer(message1_),
		boost::bind(&TCPConnection::handle_write, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

std::string TCPConnection::objectToData(CPUData& cpu1)
{
	std::stringstream oss;
	{
		boost::mutex::scoped_lock(cpu1.mutex);
		boost::archive::text_oarchive oa(oss);
		oa << cpu1;
	}
	return oss.str();
}

std::string TCPConnection::objectToData(DiskData & disk)
{
	std::stringstream oss;
	{
		boost::mutex::scoped_lock(disk.mutex);
		boost::archive::text_oarchive oa(oss);
		oa << disk;
	}
	return oss.str();
}

std::string TCPConnection::objectToData(RAMData & ram)
{
	std::stringstream oss;
	{
		boost::mutex::scoped_lock(ram.mutex);
		boost::archive::text_oarchive oa(oss);
		oa << ram;
	}
	return oss.str();
}

std::string TCPConnection::prepareConcatenatedMessage()
{
	std::string cpudata = objectToData(cpu1);
	std::string diskdata = objectToData(disk);
	std::string ramdata = objectToData(ram);
	std::cout << ramdata << std::endl;
	std::string firstEnd = boost::lexical_cast<std::string>(cpudata.size());
	firstEnd.resize(5);
	std::string secondEnd = boost::lexical_cast<std::string>(diskdata.size());
	secondEnd.resize(5);
	std::string thirdEnd = boost::lexical_cast<std::string>(ramdata.size());
	thirdEnd.resize(5);
	return firstEnd + secondEnd + thirdEnd + cpudata + diskdata + ramdata;
}

void TCPConnection::printCPU()
{
	std::cout << "Sending to 1: " << cpu1.cpu_current_clock_speed << " " << cpu1.cpu_current_voltage << " " << cpu1.cpu_manufacturer << " " << ram.ram_model << std::endl;
}

TCPConnection::TCPConnection(boost::asio::io_service & io_service, CPUData & cpuu, DiskData & diskk, RAMData& ramm) : socket_(tcp::socket(io_service)), cpu1(cpuu), disk(diskk), ram(ramm)
{
}

void TCPConnection::handle_write(const boost::system::error_code & error, size_t bytes_transferred)
{
	std::cout << "sended to " << id_ << std::endl;
	message2_ = "blan";
	async_read(socket_, buffer(message2_),
		boost::bind(&TCPConnection::handle_read, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void TCPConnection::handle_read(const boost::system::error_code & error, size_t bytes_transferred)
{
	if (message2_ == "blan")
		return;
	
	message1_ = prepareConcatenatedMessage();
	printCPU();

	async_write(socket_, buffer(message1_),
		boost::bind(&TCPConnection::handle_write, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}
