#pragma once
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
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

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & cpu_percentage_usage;
		ar & cpu_manufacturer;
		ar & cpu_max_clock_speed;
		ar & cpu_number_of_cores;
		ar & cpu_number_of_logical_processors;
		ar & cpu_name;
		ar & cpu_current_clock_speed;
		ar & cpu_current_voltage;
		ar & cpu_load_percentage;
	}

	string printToString()
	{
		stringstream ss;
		ss << "CPU" << endl;
		ss << "manufacturer: " << cpu_manufacturer << endl;
		ss << "Name: " << cpu_name << endl;
		ss << "load: " << cpu_load_percentage << "%" << endl;
		ss << "usage: " << cpu_percentage_usage << "%" << endl;
		ss << "max clock speed: " << cpu_max_clock_speed << endl;
		ss << "current clock speed: " << cpu_current_clock_speed << endl;
		ss << "current voltage: " << cpu_current_voltage << endl;
		ss << "number of cores: " << cpu_number_of_cores << endl;
		ss << "number of logical processors: " << cpu_number_of_logical_processors << endl;
		return ss.str();
	}
};