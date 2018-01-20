#pragma once

#include <boost/asio/io_service.hpp>
#include "TCPServer.hpp"

class DataSender
{
public:
	DataSender(CPUData & cpuu, DiskData & diskk, RAMData& ramm) : cpu1(cpuu), disk(diskk), ram(ramm), server(TCPServer(io_service,cpuu,diskk,ramm)) {}
	~DataSender();
	void operator () ();

private:
	boost::asio::io_service io_service;
	TCPServer server;
	CPUData& cpu1;
	DiskData& disk;
	RAMData& ram;
};

