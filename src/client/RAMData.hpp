#pragma once
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "DeviceData.hpp"
#include <string>

using namespace std;

struct RAMData : DeviceData {

	//virtual void getData();

	int ram_percentage_usage;
	float ram_size;
	float free_ram_size;
	float current_cache_size;
	int ram_page_faults_per_sec;
	int ram_clock_speed;
	string ram_model;
	int ram_cache_faults_per_sec;
	int ram_system_code_size;
	int ram_used_by_system_drivers_size;
	
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		try
		{
			ar & ram_percentage_usage;
			ar & ram_size;
			ar & free_ram_size;
			ar & current_cache_size;
			ar & ram_page_faults_per_sec;
			ar & ram_clock_speed;
			ar & ram_model;
			ar & ram_cache_faults_per_sec;
			ar & ram_system_code_size;
			ar & ram_used_by_system_drivers_size;
		}
		catch (std::exception& e) {
			stringstream ss;
			ss << e.what() << endl;
			int i = 0;
		}
	}

	string printToString()
	{
		stringstream ss;
		ss << "RAM" << endl;
		ss << "total ram: " << ram_size << "GB" << endl;
		ss << "usage: " << ram_percentage_usage << "%" << endl;
		ss << "free ram: " << free_ram_size << "GB" << endl;
		ss << "cache size: " << current_cache_size << "MB" << endl;
		ss << "page faults/s: " << ram_page_faults_per_sec << endl;
		ss << "clock: " << ram_clock_speed << endl;
		ss << "model: " << ram_model << endl;
		ss << "cache faults/s: " << ram_cache_faults_per_sec << endl;
		ss << "system code: " << ram_system_code_size << "MB" << endl;
		ss << "drivers: " << ram_used_by_system_drivers_size << "MB" << endl;
		return ss.str();
	}

};

