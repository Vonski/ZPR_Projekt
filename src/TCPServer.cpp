#include "TCPServer.hpp"

using namespace boost::asio;
using namespace boost::asio::ip;

TCPServer::TCPServer(boost::asio::io_service & io_service, CPUData & cpuu, DiskData & diskk, RAMData& ramm) : acceptor_(io_service, tcp::endpoint(tcp::v4(), 8001)), io_service_(io_service), cpu1(cpuu), disk(diskk), ram(ramm)
{
	start_accept();
}

void TCPServer::start_accept()
{
	TCPConnection::pointer new_connection = TCPConnection::create(io_service_,cpu1,disk,ram);

	acceptor_.async_accept(new_connection->socket(),
		boost::bind(&TCPServer::handle_accept, this, new_connection, boost::asio::placeholders::error));
}

void TCPServer::handle_accept(TCPConnection::pointer new_connection, const boost::system::error_code & error)
{
	if (!error)
	{
		new_connection->start();
		start_accept();
	}
}
