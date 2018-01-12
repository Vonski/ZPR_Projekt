#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <linux/hdreg.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/statvfs.h>
#include <boost/algorithm/string.hpp>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <linux/fs.h>
#include <linux/blktrace_api.h>
#include "Collector.hpp"
#include "RAMData.hpp"
#include "CPUData.hpp"
#include "DiskData.hpp"

using namespace std;

class LinuxCollector : Collector
{
public:
	LinuxCollector();
	LinuxCollector(CPUData* c, RAMData* r, DiskData* d);
	~LinuxCollector();
	bool init();
	bool initHDDStruct();
	
	// DiskDrive
	string getDiskModel();
	int getDiskPartitionsNumber();
	float getDiskSize();
	float getDiskFreeSpace();
	int getDiskCurrentQueueLength();
	int getDiskPercentageUsage();

	//RAM
	float getRAMSize();
	float getFreeRAMSize();
	int getRAMPercentageUsage();
	
	//CPU
	int getCPUPercentageUsage();

	virtual void fillModelWithData();

	
private:
	struct hd_driveid id;
//	int sector_size;
//	int disk_sectors_count;
	int fd;

	RAMData* ram_data;
	DiskData* disk_data;
	CPUData* cpu_data;
};

