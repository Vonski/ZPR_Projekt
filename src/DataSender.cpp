#include "DataSender.hpp"




DataSender::~DataSender()
{
}

void DataSender::operator()()
{
	try
	{
		io_service.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}
