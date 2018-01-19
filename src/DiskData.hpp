#pragma once
#include "DeviceData.hpp"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
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

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & disk_model;
		ar & disk_partitions_number;
		ar & disk_size;
		ar & disk_free_space;
		ar & disk_current_queue_length;
		ar & disk_avg_queue_length;
		ar & disk_read_kbytes_per_sec;
		ar & disk_write_kbytes_per_sec;
		ar & disk_percentage_usage;
	}

};

