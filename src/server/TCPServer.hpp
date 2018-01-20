#pragma once

#include <boost/asio/io_service.hpp>
#include "TCPConnetction.hpp"

class TCPServer
{
public:
	TCPServer(boost::asio::io_service& io_service, CPUData & cpuu, DiskData & diskk, RAMData& ramm);

private:
	void start_accept();

	void handle_accept(TCPConnection::pointer new_connection, const boost::system::error_code& error);

	boost::asio::io_service& io_service_;
	boost::asio::ip::tcp::acceptor acceptor_;
	CPUData& cpu1;
	DiskData& disk;
	RAMData& ram;
};

