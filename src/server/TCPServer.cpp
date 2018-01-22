#include "TCPServer.hpp"

using namespace boost::asio;
using namespace boost::asio::ip;

TCPServer::TCPServer(boost::asio::io_service& io_service, shared_ptr<CPUData> cpuu, shared_ptr<DiskData> diskk, shared_ptr<RAMData> ramm) : acceptor_(io_service, tcp::endpoint(tcp::v4(), 8001)), io_service_(io_service), cpu(cpuu), disk(diskk), ram(ramm)
{
	start_accept();
}

void TCPServer::start_accept()
{
	TCPConnection::pointer new_connection = TCPConnection::create(io_service_,cpu,disk,ram);

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
