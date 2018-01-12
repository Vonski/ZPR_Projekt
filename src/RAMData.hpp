#pragma once
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
	
};

