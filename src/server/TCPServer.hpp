#pragma once
#include <boost/asio/io_service.hpp>
#include "TCPConnetction.hpp"

class TCPServer
{
public:
	TCPServer(boost::asio::io_service& io_service, shared_ptr<CPUData> cpuu, shared_ptr<DiskData> diskk, shared_ptr<RAMData> ramm);

private:
	void start_accept();

	void handle_accept(TCPConnection::pointer new_connection, const boost::system::error_code& error);

	boost::asio::io_service& io_service_;
	boost::asio::ip::tcp::acceptor acceptor_;
	shared_ptr<CPUData> cpu;
	shared_ptr<RAMData> ram;
	shared_ptr<DiskData> disk;
};

