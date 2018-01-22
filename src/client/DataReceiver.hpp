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
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <string>
#include <algorithm>
#include "CPUData.hpp"
#include "DiskData.hpp"
#include "RAMData.hpp"
#include "sciter-x-window.hpp"

class DataReceiver
{
public:
	DataReceiver(std::string ip_address, int port_number, shared_ptr<CPUData> cpuu,	shared_ptr<DiskData> diskk,	shared_ptr<RAMData> ramm, sciter::debug_output_console& console);
	~DataReceiver();
	void tryToConnect();
	int checkForErrors();
	void operator () ();

	std::string receiveData(size_t size);
	void dataToObjects(std::string cmsg, std::string dmsg, std::string rmsg);
	void unpackMessage(std::string msg);
	int intFromMessageToString(std::string str);
	void sendPing();

	void printCPU();
	void sciterPrintData();

private:
	boost::asio::ip::tcp::endpoint ep;
	boost::asio::io_service service;
	boost::asio::ip::tcp::socket socket;
	boost::system::error_code error;
	shared_ptr<CPUData> cpu2;
	shared_ptr<DiskData> disk;
	shared_ptr<RAMData> ram;
	sciter::debug_output_console& console;
};

