// WindowsCollector.cpp : Defines the entry point for the console application.
//

#include <boost/thread/thread.hpp>
#include <iostream>
#include "DataSender.hpp"
#include "WindowsCollector.hpp"

using namespace std;

int main()
{
	CPUData cpu1;
	DiskData disk;
	RAMData ram;
	DataSender ds(cpu1, disk, ram);
	
	WindowsCollector w(&cpu1, &ram, &disk);
	w.fillModelWithData();
	boost::thread thrd1(ref(ds));

	for (;;)
	{
		w.fillModelWithData();
	}


	thrd1.join();

	cin.get();
	return 0;
}

