#pragma once
#include "DeviceData.hpp"
#include <string>

using namespace std;

struct CPUData : DeviceData {

	//virtual void getData();

	int cpu_percentage_usage;
	string cpu_manufacturer;
	float cpu_max_clock_speed;
	int cpu_number_of_cores;
	int cpu_number_of_logical_processors;
	string cpu_name;
	float cpu_current_clock_speed;
	float cpu_current_voltage;
	int cpu_load_percentage;
};