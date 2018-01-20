#pragma once

#include <boost/asio/io_service.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/system/error_code.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/lexical_cast.hpp>
#include <string>
#include <iostream>
#include <sstream>
#include "DeviceData.hpp"
#include "CPUData.hpp"
#include "DiskData.hpp"
#include "RAMData.hpp"


class TCPConnection : public std::enable_shared_from_this<TCPConnection>
{
public:
	typedef std::shared_ptr<TCPConnection> pointer;

	static pointer create(boost::asio::io_service& io_service, CPUData & cpuu, DiskData & diskk, RAMData& ramm);
	boost::asio::ip::tcp::socket& socket();
	void start();

	std::string objectToData(CPUData& cpu1);
	std::string objectToData(DiskData& disk);
	std::string objectToData(RAMData& ram);
	std::string prepareConcatenatedMessage();
	void printCPU();


private:
	TCPConnection(boost::asio::io_service& io_service, CPUData & cpuu, DiskData & diskk, RAMData& ramm);

	void handle_write(const boost::system::error_code& error, size_t bytes_transferred);
	void handle_read(const boost::system::error_code& error, size_t bytes_transferred);

	boost::asio::ip::tcp::socket socket_;
	std::string message1_, message2_;
	int id_;
	CPUData& cpu1;
	DiskData& disk;
	RAMData& ram;
};
