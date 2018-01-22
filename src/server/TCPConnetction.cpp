#include "TCPConnetction.hpp"

using namespace boost::asio;
using namespace boost::asio::ip;

int counter = 0;
int tmp = 0;

TCPConnection::pointer TCPConnection::create(boost::asio::io_service& io_service, shared_ptr<CPUData> cpuu, shared_ptr<DiskData> diskk, shared_ptr<RAMData> ramm)
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

std::string TCPConnection::objectToData(shared_ptr<CPUData> cpu)
{
	std::stringstream oss;
	{
		boost::mutex::scoped_lock(cpu->mutex);
		boost::archive::text_oarchive oa(oss);
		oa << *cpu;
	}
	return oss.str();
}

std::string TCPConnection::objectToData(shared_ptr<DiskData> disk)
{
	std::stringstream oss;
	{
		boost::mutex::scoped_lock(disk->mutex);
		boost::archive::text_oarchive oa(oss);
		oa << *disk;
	}
	return oss.str();
}

std::string TCPConnection::objectToData(shared_ptr<RAMData> ram)
{
	std::stringstream oss;
	{
		boost::mutex::scoped_lock(ram->mutex);
		boost::archive::text_oarchive oa(oss);
		oa << *ram;
	}
	return oss.str();
}

std::string TCPConnection::prepareConcatenatedMessage()
{
	std::string cpudata = objectToData(cpu);
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
	std::cout << "Sending to 1: " << cpu->cpu_current_clock_speed << " " << cpu->cpu_current_voltage << " " << cpu->cpu_manufacturer << " " << ram->ram_model << std::endl;
}

TCPConnection::TCPConnection(boost::asio::io_service& io_service, shared_ptr<CPUData> cpuu, shared_ptr<DiskData> diskk, shared_ptr<RAMData> ramm) : socket_(tcp::socket(io_service)), cpu(cpuu), disk(diskk), ram(ramm)
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
