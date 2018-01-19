#pragma once
#include "DeviceData.hpp"
//#include <boost/archive/text_oarchive.hpp>
//#include <boost/archive/text_iarchive.hpp>
#include <string>
#include "ObservationSubject.hpp"

using namespace std;

struct CPUData : DeviceData, public ObservationSubject {

	//virtual void getData();
	CPUData() {}
	~CPUData() {}

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




};