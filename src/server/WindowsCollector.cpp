#define _WIN32_DCOM
#pragma comment(lib, "wbemuuid.lib")
#include "WindowsCollector.hpp"

using namespace std;

const int GB = 1073741824;
const int MB = 1048576;
const int KB = 1024;

wstring s2ws(const std::string& str);
string ws2s(const std::wstring& wstr);


WindowsCollector::~WindowsCollector() {
	disconnectFromWMINamespace();
}

WindowsCollector::WindowsCollector() {
	pSvc = NULL;
	pLoc = NULL;
}

WindowsCollector::WindowsCollector(CPUData* c, RAMData* r, DiskData* d) {
	pSvc = NULL;
	pLoc = NULL;
	cpu_data = c;
	ram_data = r;
	disk_data = d;
}

int WindowsCollector::connectToWMINamespace() {
	HRESULT hres;
	// Step 1: --------------------------------------------------
	// Initialize COM. ------------------------------------------

	hres = CoInitializeEx(0, COINIT_MULTITHREADED);
	if (FAILED(hres))
	{
		cout << "Failed to initialize COM library. Error code = 0x"
			<< hex << hres << endl;
		return 1;                  // Program has failed.
	}

	// Step 2: --------------------------------------------------
	// Set general COM security levels --------------------------

	hres = CoInitializeSecurity(
		NULL,
		-1,                          // COM authentication
		NULL,                        // Authentication services
		NULL,                        // Reserved
		RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
		RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
		NULL,                        // Authentication info
		EOAC_NONE,                   // Additional capabilities 
		NULL                         // Reserved
	);


	if (FAILED(hres))
	{
		cout << "Failed to initialize security. Error code = 0x"
			<< hex << hres << endl;
		CoUninitialize();
		return 1;                    // Program has failed.
	}

	// Step 3: ---------------------------------------------------
	// Obtain the initial locator to WMI -------------------------

	pLoc = NULL;

	hres = CoCreateInstance(
		CLSID_WbemLocator,
		0,
		CLSCTX_INPROC_SERVER,
		IID_IWbemLocator, (LPVOID *)&pLoc);

	if (FAILED(hres))
	{
		cout << "Failed to create IWbemLocator object."
			<< " Err code = 0x"
			<< hex << hres << endl;
		CoUninitialize();
		return 1;                 // Program has failed.
	}

	// Step 4: -----------------------------------------------------
	// Connect to WMI through the IWbemLocator::ConnectServer method

	pSvc = NULL;

	// Connect to the root\cimv2 namespace with
	// the current user and obtain pointer pSvc
	// to make IWbemServices calls.
	hres = pLoc->ConnectServer(
		_bstr_t(L"ROOT\\CIMV2"), // Object path of WMI namespace
		NULL,                    // User name. NULL = current user
		NULL,                    // User password. NULL = current
		0,                       // Locale. NULL indicates current
		NULL,                    // Security flags.
		0,                       // Authority (for example, Kerberos)
		0,                       // Context object 
		&pSvc                    // pointer to IWbemServices proxy
	);

	if (FAILED(hres))
	{
		cout << "Could not connect. Error code = 0x"
			<< hex << hres << endl;
		pLoc->Release();
		CoUninitialize();
		return 1;                // Program has failed.
	}

	cout << "Connected to ROOT\\CIMV2 WMI namespace" << endl;


	// Step 5: --------------------------------------------------
	// Set security levels on the proxy -------------------------

	hres = CoSetProxyBlanket(
		pSvc,                        // Indicates the proxy to set
		RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
		RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
		NULL,                        // Server principal name 
		RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
		RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
		NULL,                        // client identity
		EOAC_NONE                    // proxy capabilities 
	);

	if (FAILED(hres))
	{
		cout << "Could not set proxy blanket. Error code = 0x"
			<< hex << hres << endl;
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return 1;               // Program has failed.
	}

}

void WindowsCollector::disconnectFromWMINamespace() {
	pSvc->Release();
	pLoc->Release();
	CoUninitialize();
}

int WindowsCollector::getVtProp(VARIANT &vtProp, string class_name, string property_name) {
	HRESULT hres;	
	// Step 6: --------------------------------------------------
	// Use the IWbemServices pointer to make requests of WMI ----

	// For example, get the name of the operating system
	IEnumWbemClassObject* pEnumerator = NULL;
	hres = pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t(("SELECT * FROM " + class_name).c_str()),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);

	if (FAILED(hres))
	{
		cout << "Query for operating system name failed."
			<< " Error code = 0x"
			<< hex << hres << endl;
		return 1;               // Program has failed.
	}

	// Step 7: -------------------------------------------------
	// Get the data from the query in step 6 -------------------

	IWbemClassObject *pclsObj = NULL;
	ULONG uReturn = 0;

	while (pEnumerator)
	{
		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
			&pclsObj, &uReturn);

		if (0 == uReturn)
		{
			break;
		}
		// Get the value of the Name property
		std::wstring stmp = s2ws(property_name);
		LPCWSTR result = stmp.c_str();
		hr = pclsObj->Get(result, 0, &vtProp, 0, 0);

		pclsObj->Release();
	}
	
	pEnumerator->Release();

	return 0;   // Program successfully completed.
}

int WindowsCollector::getVtPropVec(vector<VARIANT> &vtPropVec, string class_name, string property_name) {
	HRESULT hres;
	// Step 6: --------------------------------------------------
	// Use the IWbemServices pointer to make requests of WMI ----

	// For example, get the name of the operating system
	IEnumWbemClassObject* pEnumerator = NULL;
	hres = pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t(("SELECT * FROM " + class_name).c_str()),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);

	if (FAILED(hres))
	{
		cout << "Query for operating system name failed."
			<< " Error code = 0x"
			<< hex << hres << endl;
		return 1;               // Program has failed.
	}

	// Step 7: -------------------------------------------------
	// Get the data from the query in step 6 -------------------

	IWbemClassObject *pclsObj = NULL;
	ULONG uReturn = 0;

	while (pEnumerator)
	{
		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
			&pclsObj, &uReturn);

		if (0 == uReturn)
		{
			break;
		}

		// Get the value of the Name property
		std::wstring stmp = s2ws(property_name);
		LPCWSTR result = stmp.c_str();

		VARIANT v;
		hr = pclsObj->Get(result, 0, &v, 0, 0);
		vtPropVec.push_back(v);
		pclsObj->Release();
	}

	pEnumerator->Release();

	return 0;   // Program successfully completed.
}

int WindowsCollector::getWMIDataStr(string class_name, string property_name, string &collected_data){
	if (pSvc == NULL || pLoc == NULL)
		if (connectToWMINamespace())
			return 1;
	VARIANT vtProp;
	if (getVtProp(vtProp, class_name, property_name))
		return 1;

	//bad data type
	if (vtProp.vt != VT_BSTR)
		return 1;

	collected_data = ws2s(vtProp.bstrVal);
	VariantClear(&vtProp);
	return 0;   // Program successfully completed.

}

int WindowsCollector::getWMIDataStrFromVec(string class_name, string property_name, vector<string> &collected_data) {
	if (pSvc == NULL || pLoc == NULL)
		if (connectToWMINamespace())
			return 1;
	vector<VARIANT> vtPropVec;
	if (getVtPropVec(vtPropVec, class_name, property_name))
		return 1;

	for (vector<VARIANT>::iterator iter = vtPropVec.begin(); iter != vtPropVec.end(); iter++) {
		VARIANT vtProp = *iter;
		if (vtProp.vt != VT_BSTR) 
			return 1;

		collected_data.push_back(ws2s(vtProp.bstrVal));
		VariantClear(&vtProp);
	}
	return 0;   // Program successfully completed.

}

int WindowsCollector::getWMIDataInt(string class_name, string property_name, int &collected_data) {
	//not connected to WMI namespace
	if (pSvc == NULL || pLoc == NULL)
		if (connectToWMINamespace())
			return 1;
	VARIANT vtProp;
	if (getVtProp(vtProp, class_name, property_name))
		return 1;

	//bad data type
	if (vtProp.vt != VT_I4)
		return 1;
	
	collected_data = vtProp.intVal;
	VariantClear(&vtProp);
	return 0;   // Program successfully completed.

}


///////////////////////////////////////////////////
//	CPU
///////////////////////////////////////////////////


int WindowsCollector::getCPUPercentageUsage() {
	string cpu_usage;
	if (getWMIDataStr("Win32_PerfFormattedData_PerfOS_Processor ", "PercentProcessorTime", cpu_usage))
		cpu_usage="0";
	return stoi(cpu_usage);
}
string  WindowsCollector::getCpuManufacturer() {
	string manufacturer;
	if (getWMIDataStr("Win32_Processor ", "Manufacturer", manufacturer))
		manufacturer = "";
	return manufacturer;
}
//returns max clock speed in GHz
float  WindowsCollector::getCPUMaxClockSpeed() {
	int clock_speed;
	if (getWMIDataInt("Win32_Processor ", "MaxClockSpeed", clock_speed))
		clock_speed = 0;
	float clock_speed_f = clock_speed/1000.0f;
	return clock_speed_f;
}
int  WindowsCollector::getCPUNumberOfCores() {
	int cores_nr;
	if (getWMIDataInt("Win32_Processor ", "NumberOfCores", cores_nr))
		cores_nr = 0;
	return cores_nr;
}
int  WindowsCollector::getCPUNumberOfLogicalProcessors() {
	int logical_processors_nr;
	if (getWMIDataInt("Win32_Processor ", "NumberOfLogicalProcessors", logical_processors_nr))
		logical_processors_nr = 0;
	return logical_processors_nr;
}
string  WindowsCollector::getCPUName() {
	string name;
	if (getWMIDataStr("Win32_Processor ", "Name", name))
		name = "";
	return name;
}
//returns clock speed in GHz
float  WindowsCollector::getCPUCurrentClockSpeed() {
	int clock_speed;
	if (getWMIDataInt("Win32_Processor ", "CurrentClockSpeed", clock_speed))
		clock_speed = 0;
	float clock_speed_f = clock_speed / 1000.0f;
	return clock_speed_f;
}

//returns voltage in V
float  WindowsCollector::getCPUCurrentVoltage() {
	int cur_voltage;
	if (getWMIDataInt("Win32_Processor ", "CurrentVoltage", cur_voltage))
		cur_voltage = 0;
	float cur_voltage_f = cur_voltage / 10.0f;
	return cur_voltage_f;
}
int  WindowsCollector::getCPULoadPercentage() {
	int load_percentage;
	if (getWMIDataInt("Win32_Processor ", "LoadPercentage", load_percentage))
		load_percentage = 0;
	return load_percentage;
}

/////////////////////////////////////////////////////////
//	DISK DRIVE
////////////////////////////////////////////////////////

string  WindowsCollector::getDiskModel() {
	string name;
	if (getWMIDataStr("Win32_DiskDrive ", "Model", name))
		name = "";
	return name;
}
int  WindowsCollector::getDiskPartitionsNumber() {
	int partitions_nr;
	if (getWMIDataInt("Win32_DiskDrive ", "Partitions", partitions_nr))
		partitions_nr = 0;
	return partitions_nr;
}

//returns disk size in GB
float  WindowsCollector::getDiskSize() {
	string size;
	if (getWMIDataStr("Win32_DiskDrive", "Size", size))
		size = "0";
	//long size_l = stol(size);
	float size_f = stof(size) / GB;
	return size_f;
}

//returns free disk space in GB
float  WindowsCollector::getDiskFreeSpace() {
	vector<string> size_vec;
	float size=0;
	getWMIDataStrFromVec("Win32_LogicalDisk", "FreeSpace", size_vec);

	for (vector<string>::iterator iter = size_vec.begin(); iter != size_vec.end(); iter++) {
		size += stof(*iter);
	}
	return size/GB;
}
int  WindowsCollector::getDiskCurrentQueueLength() {
	int length;
	if (getWMIDataInt("Win32_PerfFormattedData_PerfDisk_PhysicalDisk", "CurrentDiskQueueLength", length))
		length = 0;
	return length;
}
int  WindowsCollector::getDiskAvgQueueLength() {
	string length;
	if (getWMIDataStr("Win32_PerfFormattedData_PerfDisk_PhysicalDisk", "AvgDiskWriteQueueLength", length))
		length = "0";	
	return stoi(length);
}
float  WindowsCollector::getDiskReadKBytesPerSec() {
	string read;
	if (getWMIDataStr("Win32_PerfFormattedData_PerfDisk_PhysicalDisk", "DiskReadBytesPerSec", read))
		read = "0";
	float read_f = stof(read)/KB;
	return read_f;
}
float WindowsCollector::getDiskWriteKBytesPerSec() {
	string write;
	if (getWMIDataStr("Win32_PerfFormattedData_PerfDisk_PhysicalDisk", "DiskWriteBytesPerSec", write))
		write = "0";
	float write_f = stof(write) / KB;
	return write_f;
}
int  WindowsCollector::getDiskPercentageUsage() {
	string usage;
	if (getWMIDataStr("Win32_PerfFormattedData_PerfDisk_PhysicalDisk", "PercentDiskTime", usage))
		usage = "0";
	return stoi(usage);
}

/////////////////////////////////////////
//	RAM
////////////////////////////////////////

//returns RAM size in GB
float WindowsCollector::getRAMSize() {
	MEMORYSTATUSEX mem_stat;
	mem_stat.dwLength = sizeof(mem_stat);
	GlobalMemoryStatusEx(&mem_stat);
	DWORDLONG ram_amount = mem_stat.ullTotalPhys;
	float ram_amount_f = (float)ram_amount / GB;
	return ram_amount_f;
}

int WindowsCollector::getRAMPercentageUsage() {
	MEMORYSTATUSEX mem_stat;
	mem_stat.dwLength = sizeof(mem_stat);
	GlobalMemoryStatusEx(&mem_stat);
	DWORD usage = mem_stat.dwMemoryLoad;
	return (int)usage;
}

//Returns free RAM size in MB
float WindowsCollector::getFreeRamSize() {
	string size;
	if (getWMIDataStr("Win32_PerfFormattedData_PerfOS_Memory", "AvailableBytes", size))
		size = "0";
	long long size_l = stoll(size);
	float size_f =(float) size_l / MB;
	return size_f;
}
//returns free cache size in MB
float WindowsCollector::getCurrentCacheSize() {
	string size;
	if (getWMIDataStr("Win32_PerfFormattedData_PerfOS_Memory", "CacheBytes", size))
		size = "0";
	long long size_l = stoll(size);
	float size_f = (float)size_l / MB;
	return size_f;
}
int WindowsCollector::getRAMPageFaultsPerSec() {
	int faults;
	if (getWMIDataInt("Win32_PerfFormattedData_PerfOS_Memory", "PageFaultsPerSec", faults))
		faults = 0;
	return faults;
}
//returns RAM clock speed in MHz
int WindowsCollector::getRAMClockSpeed() {
	int speed;
	if (getWMIDataInt("Win32_PhysicalMemory", "ConfiguredClockSpeed", speed))
		speed = 0;
	return speed;
}
string WindowsCollector::getRAMModel() {
	string model;
	if (getWMIDataStr("Win32_PhysicalMemory", "Model", model))
		model = "0";	
	return model;	
}
int WindowsCollector::getRAMCacheFaultsPerSec() {
	int faults;
	if (getWMIDataInt("Win32_PerfFormattedData_PerfOS_Memory", "CacheFaultsPerSec", faults))
		faults = 0;
	return faults;
}
//returns system code size in RAM in MB
int WindowsCollector::getRAMSystemCodeSize() {
	string size;
	if (getWMIDataStr("Win32_PerfFormattedData_PerfOS_Memory", "SystemCodeTotalBytes", size))
		size = "0";
	long long size_l = stoll(size);
	float size_f = (float)size_l / MB;
	return size_f;
}
//returns RAM used by system drivers in MB
int WindowsCollector::getRAMUsedBySystemDriverSize() {
	string size;
	if (getWMIDataStr("Win32_PerfFormattedData_PerfOS_Memory", "SystemDriverTotalBytes", size))
		size = "0";
	long long size_l = stoll(size);
	float size_f = (float)size_l / MB;
	return size_f;
}

void WindowsCollector::fillModelWithData() {
	{
		boost::mutex::scoped_lock(cpu_data->mutex);
		cpu_data->cpu_percentage_usage = getCPUPercentageUsage();
		cpu_data->cpu_manufacturer = getCpuManufacturer();
		cpu_data->cpu_max_clock_speed = getCPUMaxClockSpeed();
		cpu_data->cpu_number_of_cores = getCPUNumberOfCores();
		cpu_data->cpu_number_of_logical_processors = getCPUNumberOfLogicalProcessors();
		cpu_data->cpu_name = getCPUName();
		cpu_data->cpu_current_clock_speed = getCPUCurrentClockSpeed();
		cpu_data->cpu_current_voltage = getCPUCurrentVoltage();
		cpu_data->cpu_load_percentage = getCPULoadPercentage();
	}

	{
		boost::mutex::scoped_lock(ram_data->mutex);
		ram_data->ram_percentage_usage = getRAMPercentageUsage();
		ram_data->ram_size = getRAMSize();
		ram_data->free_ram_size = getFreeRamSize();
		ram_data->current_cache_size = getCurrentCacheSize();
		ram_data->ram_page_faults_per_sec = getRAMPageFaultsPerSec();
		ram_data->ram_clock_speed = getRAMClockSpeed();
		ram_data->ram_model = getRAMModel();
		ram_data->ram_cache_faults_per_sec = getRAMCacheFaultsPerSec();
		ram_data->ram_system_code_size = getRAMSystemCodeSize();
		ram_data->ram_used_by_system_drivers_size = getRAMUsedBySystemDriverSize();
	}

	{
		boost::mutex::scoped_lock(disk_data->mutex);
		disk_data->disk_model = getDiskModel();
		disk_data->disk_partitions_number = getDiskPartitionsNumber();
		disk_data->disk_size = getDiskSize();
		disk_data->disk_free_space = getDiskFreeSpace();
		disk_data->disk_current_queue_length = getDiskCurrentQueueLength();
		disk_data->disk_avg_queue_length = getDiskAvgQueueLength();
		disk_data->disk_read_kbytes_per_sec = getDiskReadKBytesPerSec();
		disk_data->disk_write_kbytes_per_sec = getDiskWriteKBytesPerSec();
		disk_data->disk_percentage_usage = getDiskPercentageUsage();
	}
}



wstring s2ws(const std::string& str)
{
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.from_bytes(str);
}

string ws2s(const std::wstring& wstr)
{
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.to_bytes(wstr);
}
