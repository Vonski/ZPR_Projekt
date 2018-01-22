#pragma once
#include <boost/thread/mutex.hpp>
#include <Windows.h>
#include <string>
#include <iostream>
#include <comdef.h>
#include <Wbemidl.h>
#include <locale>
#include <codecvt>
#include <vector>
#include <algorithm>
#include "Collector.hpp"
#include "CPUData.hpp"
#include "DiskData.hpp"
#include "RAMData.hpp"

using namespace std;

class WindowsCollector : public Collector {
public:
	WindowsCollector();
	WindowsCollector(shared_ptr<CPUData> cpu, shared_ptr<RAMData> ram, shared_ptr<DiskData> disk);
	~WindowsCollector();	

	virtual void fillModelWithData();

private:

	//CPU
	int getCPUPercentageUsage();
	string getCpuManufacturer();
	float getCPUMaxClockSpeed();
	int getCPUNumberOfCores();
	int getCPUNumberOfLogicalProcessors();
	string getCPUName();
	float getCPUCurrentClockSpeed();
	float getCPUCurrentVoltage();
	int getCPULoadPercentage();

	//DiskDrive
	string getDiskModel();
	int getDiskPartitionsNumber();
	float getDiskSize();
	float getDiskFreeSpace();
	int getDiskCurrentQueueLength();
	int getDiskAvgQueueLength();
	float getDiskReadKBytesPerSec();
	float getDiskWriteKBytesPerSec();
	int getDiskPercentageUsage();

	//RAM
	int getRAMPercentageUsage();
	float getRAMSize();
	float getFreeRamSize();
	float getCurrentCacheSize();
	int getRAMPageFaultsPerSec();
	int getRAMClockSpeed();
	string getRAMModel();
	int getRAMCacheFaultsPerSec();
	int getRAMSystemCodeSize();
	int getRAMUsedBySystemDriverSize();

	int connectToWMINamespace();
	void disconnectFromWMINamespace();
	int getVtProp(VARIANT &vtProp, string class_name, string property_name);
	int getVtPropVec(vector<VARIANT> &vtPropVec, string class_name, string property_name);
	int getWMIDataStr(string className, string propertyName, string& collectedData);
	int getWMIDataStrFromVec(string className, string propertyName, vector<string>& collectedData);
	int getWMIDataInt(string className, string propertyName, int& collectedData);

	IWbemServices *pSvc;
	IWbemLocator *pLoc;
	shared_ptr<CPUData> cpu_data;
	shared_ptr<RAMData> ram_data;
	shared_ptr<DiskData> disk_data;

};