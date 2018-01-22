#pragma once
#include <boost/asio/io_service.hpp>
#include "TCPServer.hpp"

class DataSender
{
public:
	DataSender(shared_ptr<CPUData> cpuu, shared_ptr<DiskData> diskk, shared_ptr<RAMData> ramm) : cpu(cpuu), disk(diskk), ram(ramm),
		server(TCPServer(io_service,cpuu,diskk,ramm)) {}
	~DataSender();
	void operator () ();

private:
	boost::asio::io_service io_service;
	TCPServer server;
	shared_ptr<CPUData> cpu;
	shared_ptr<RAMData> ram;
	shared_ptr<DiskData> disk;

};

