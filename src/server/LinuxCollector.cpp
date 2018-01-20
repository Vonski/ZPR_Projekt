#include "LinuxCollector.hpp"

using namespace std;

const int KB = 1024;
const int MB = 1048576;
const int GB = 1073741824;


LinuxCollector::LinuxCollector()
{
	init();
}

LinuxCollector::~LinuxCollector()
{
}

bool LinuxCollector::init()
{
	if(initHDDStruct()) return false;
	return true;
}

bool LinuxCollector::initHDDStruct()
{
	if (getgid()) {
		cout << "Run this with root permission" << endl;
		return false;
	}
	if (!(fd = open ("/dev/sda", O_RDONLY|O_NONBLOCK))) {
		perror ("/dev/sda");
		return false;
	}
	if(ioctl(fd, HDIO_GET_IDENTITY, &id)) {
		perror ("HDIO_GET_IDENTITY");
	}
//	if(ioctl(fd, BLKSSZGET, &sector_size)) {
//		perror ("BLKSSZGET");
//	}
//	if(ioctl(fd, BLKGETSIZE , &disk_sectors_count)) {
//		perror ("BLKGETSIZE ");
//	}
	if (close(fd)) {
		perror ("/dev/sda");
		return false;
	}
	return true;
}

string LinuxCollector::getDiskModel()
{
	string str(id.model, id.model+sizeof(id.model)/sizeof(id.model[0]));
	return str;
}

int LinuxCollector::getDiskPartitionsNumber()
{
	fstream file;
	string line;
	size_t found;
	int counter=-1;
	file.open("/proc/partitions", ios::in);
	while(file.good())
	{
		getline(file,line);
		found = line.find("sda");
		if (found!=string::npos)
			counter++;
	}
	file.close();
	return counter;
}

string getNthValueFromProcFileRecord(string line, int n)
{
	int i=0;
	int begin=0, end=0;
	bool start_of_value_reached=false;
	bool end_of_value_reached=false;
	for(int j=0; j<n; ++j)
	{
		start_of_value_reached=false;
		end_of_value_reached=false;
		while(!start_of_value_reached || !end_of_value_reached)
		{
			if(line[i]!=' ' && !start_of_value_reached)
			{
				start_of_value_reached=true;
				begin = i;
			}
			else if(line[i]==' ' && start_of_value_reached)
			{
				end_of_value_reached=true;
				end = i;
			}
			i++;
		}
	}
	return line.substr(begin, end-begin);
}

float LinuxCollector::getDiskSize()
{
	fstream file;
	string line;
	file.open("/proc/partitions", ios::in);
	if(file.good())
	{
		for(int i=0;i<3;++i)
			getline(file,line);
		file.close();
	}
	line = getNthValueFromProcFileRecord(line, 3);
	float kbyte_size = stof(line);
	return kbyte_size/(1024.0f*1024.0f);
//	cout << sector_size*disk_sectors_count << endl;
//	return static_cast<float>(disk_sectors_count)/1024.0f;
}

float LinuxCollector::getDiskFreeSpace(){
	struct statvfs disk_data;
    statvfs("/", &disk_data);
    unsigned long long available = (disk_data.f_bavail * disk_data.f_frsize);
    float available_f = (float)available/GB;
	return available_f;
}

int LinuxCollector::getDiskCurrentQueueLength(){
	
	fstream file;
	string line;
	size_t found;
	string length="0";
	file.open("/proc/diskstats", ios::in);
	while(file.good())
	{
		getline(file,line);
		found = line.find("sda");
		if (found!=string::npos){
			length = getNthValueFromProcFileRecord(line, 12);
			break;
		}		
	}
	file.close();
	return stoi(length);
}

float LinuxCollector::getRAMSize(){
	struct sysinfo mem_info;
	sysinfo (&mem_info);
	long long total_phys_mem = mem_info.totalram;
	total_phys_mem *= mem_info.mem_unit;
	float total_phys_mem_f = (float)total_phys_mem/GB;
	return total_phys_mem_f;
}

float LinuxCollector::getFreeRAMSize(){
	struct sysinfo mem_info;
	sysinfo (&mem_info);
	long long free_mem = mem_info.freeram;
	float free_mem_f = (float)free_mem/MB;
	return free_mem_f;
}

int LinuxCollector::getRAMPercentageUsage(){
	return getFreeRAMSize()/getRAMSize()/1024*100;
}

int LinuxCollector::getCPUPercentageUsage(){
	
	fstream file;
	string line;
	long total_jiffies_1 = 0, total_jiffies_2=0;
	long work_jiffies_1 = 0, work_jiffies_2=0;
	file.open("/proc/stat", ios::in);
	getline(file,line);
	for(int i=2; i<9; ++i)
		total_jiffies_1+=stol(getNthValueFromProcFileRecord(line, i));
	for(int i=2; i<5; ++i)
		work_jiffies_1+=stol(getNthValueFromProcFileRecord(line, i));
	file.close();
	sleep(1);
	file.open("/proc/stat", ios::in);
	getline(file,line);
	for(int i=2; i<9; ++i)
		total_jiffies_2+=stol(getNthValueFromProcFileRecord(line, i));
	for(int i=2; i<5; ++i)
		work_jiffies_2+=stol(getNthValueFromProcFileRecord(line, i));
	file.close();
	float ratio=0;
	if(work_jiffies_1!=work_jiffies_2 && total_jiffies_1!=total_jiffies_2)
		ratio = (float)(work_jiffies_2-work_jiffies_1)/(total_jiffies_2-total_jiffies_1);
	return ratio*100;
}

int LinuxCollector::getDiskPercentageUsage(){
	fstream file;
	string line;
	long read_write_ms_1 = 0, read_write_ms_2=0;
	file.open("/proc/diskstats", ios::in);	
	getline(file,line);	

	read_write_ms_1+=stol(getNthValueFromProcFileRecord(line, 7));
	read_write_ms_1+=stol(getNthValueFromProcFileRecord(line, 11));
	
	file.close();
	sleep(1);
	file.open("/proc/diskstats", ios::in);
	getline(file,line);

	read_write_ms_2+=stol(getNthValueFromProcFileRecord(line, 7));
	read_write_ms_2+=stol(getNthValueFromProcFileRecord(line, 11));
	
	file.close();
	float ratio=0;
	if(read_write_ms_1!=read_write_ms_2)
		ratio = (float)(read_write_ms_2-read_write_ms_1)/1000;
	return ratio*100;
}

void LinuxCollector::fillModelWithData(){

		cpu_data->cpu_percentage_usage = getCPUPercentageUsage();
		cpu_data->cpu_manufacturer = "";
		cpu_data->cpu_max_clock_speed = 0;
		cpu_data->cpu_number_of_cores = 0;
		cpu_data->cpu_number_of_logical_processors = 0;
		cpu_data->cpu_name = "";
		cpu_data->cpu_current_clock_speed = 0;
		cpu_data->cpu_current_voltage = 0;
		cpu_data->cpu_load_percentage = 0;

		ram_data->ram_percentage_usage = getRAMPercentageUsage();
		ram_data->ram_size = getRAMSize();
		ram_data->free_ram_size = getFreeRAMSize();
		ram_data->current_cache_size = 0;
		ram_data->ram_page_faults_per_sec = 0;
		ram_data->ram_clock_speed = 0;
		ram_data->ram_model = 0;
		ram_data->ram_cache_faults_per_sec = 0;
		ram_data->ram_system_code_size = 0;
		ram_data->ram_used_by_system_drivers_size = 0;

		disk_data->disk_model = getDiskModel();
		disk_data->disk_partitions_number = getDiskPartitionsNumber();
		disk_data->disk_size = getDiskSize();
		disk_data->disk_free_space = getDiskFreeSpace();
		disk_data->disk_current_queue_length = getDiskCurrentQueueLength();
		disk_data->disk_avg_queue_length = 0;
		disk_data->disk_read_kbytes_per_sec = 0;
		disk_data->disk_write_kbytes_per_sec = 0;
		disk_data->disk_percentage_usage = getDiskPercentageUsage();
	}

LinuxCollector::LinuxCollector(CPUData* c, RAMData* r, DiskData* d) {
	cpu_data = c;
	ram_data = r;
	disk_data = d;
}

	

