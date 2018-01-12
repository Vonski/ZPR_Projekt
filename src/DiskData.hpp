#pragma once
#include "DeviceData.hpp"
#include <string>

using namespace std;

struct DiskData : DeviceData {

	//void getData();

	string disk_model;
	int disk_partitions_number;
	float disk_size;
	float disk_free_space;
	int disk_current_queue_length;
	int disk_avg_queue_length;
	float disk_read_kbytes_per_sec;
	float disk_write_kbytes_per_sec;
	int disk_percentage_usage;
};

