#include <boost/thread/thread.hpp>
#include <iostream>
#include "DataSender.hpp"
#include "WindowsCollector.hpp"

using namespace std;

int main()
{
	shared_ptr<CPUData> cpu = make_shared<CPUData>();
	shared_ptr<DiskData> disk = make_shared<DiskData>();
	shared_ptr<RAMData> ram = make_shared<RAMData>();
	DataSender ds(cpu, disk, ram);
	
	WindowsCollector collector(cpu, ram, disk);
	collector.fillModelWithData();
	boost::thread thrd1(ref(ds));

	for (;;)
	{
		collector.fillModelWithData();
	}

	thrd1.join();

	cin.get();
	return 0;
}

