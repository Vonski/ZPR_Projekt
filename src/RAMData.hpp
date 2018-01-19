#pragma once
#include "DeviceData.hpp"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
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

};

