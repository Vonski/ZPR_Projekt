#pragma once
#include <string>

using namespace std;

class Collector {
public:
	//CPU
	virtual int getCPUPercentageUsage() = 0;
	virtual string getCpuManufacturer() = 0;
	virtual float getCPUMaxClockSpeed() = 0;
	virtual int getCPUNumberOfCores() = 0;
	virtual int getCPUNumberOfLogicalProcessors() = 0;
	virtual string getCPUName() = 0;
	virtual float getCPUCurrentClockSpeed() = 0;
	virtual float getCPUCurrentVoltage() = 0;
	virtual int getCPULoadPercentage() = 0;

	//DiskDrive
	virtual string getDiskModel() = 0;
	virtual int getDiskPartitionsNumber() = 0;
	virtual float getDiskSize() = 0;
	virtual float getDiskFreeSpace() = 0;
	virtual int getDiskCurrentQueueLength() = 0;
	virtual int getDiskAvgQueueLength() = 0;
	virtual float getDiskReadKBytesPerSec() = 0;
	virtual float getDiskWriteKBytesPerSec() = 0;
	virtual int getDiskPercentageUsage() = 0;

	//RAM
	virtual int getRAMPercentageUsage() = 0;
	virtual float getRAMSize() = 0;
	virtual float getFreeRamSize() = 0;
	virtual float getCurrentCacheSize() = 0;
	virtual int getRAMPageFaultsPerSec() = 0;
	virtual int getRAMClockSpeed() = 0;
	virtual string getRAMModel() = 0;
	virtual int getRAMCacheFaultsPerSec() = 0;
	virtual int getRAMSystemCodeSize() = 0;
	virtual int getRAMUsedBySystemDriverSize() = 0;
};