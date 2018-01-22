#define BOOST_TEST_MODULE HardwareMonitorTestModule
#include <boost/test/unit_test.hpp>
#include "client/CPUData.hpp"
#include "client/DiskData.hpp"
#include "client/RAMData.hpp"

BOOST_AUTO_TEST_SUITE(Serialization)

BOOST_AUTO_TEST_CASE(CPUSerialization)
{
	std::stringstream ofs;
	CPUData cpu1;
	{
		boost::archive::text_oarchive oa(ofs);
		oa << cpu1;
	}
	std::string net = ofs.str();

	CPUData cpu2;
	std::stringstream ifs(net);
	{
		boost::archive::text_iarchive ia(ifs);
		ia >> cpu2;
	}

	BOOST_CHECK(cpu1.cpu_current_clock_speed == cpu2.cpu_current_clock_speed);
	BOOST_CHECK(cpu1.cpu_current_voltage == cpu2.cpu_current_voltage);
	BOOST_CHECK(cpu1.cpu_load_percentage == cpu2.cpu_load_percentage);
	BOOST_CHECK(cpu1.cpu_manufacturer == cpu2.cpu_manufacturer);
	BOOST_CHECK(cpu1.cpu_max_clock_speed == cpu2.cpu_max_clock_speed);
	BOOST_CHECK(cpu1.cpu_name == cpu2.cpu_name);
	BOOST_CHECK(cpu1.cpu_number_of_cores == cpu2.cpu_number_of_cores);
	BOOST_CHECK(cpu1.cpu_number_of_logical_processors == cpu2.cpu_number_of_logical_processors);
	BOOST_CHECK(cpu1.cpu_percentage_usage == cpu2.cpu_percentage_usage);

}

BOOST_AUTO_TEST_CASE(DiskSerialization)
{
	std::stringstream ofs;
	DiskData disk1;
	disk1.disk_free_space = 100;
	{
		boost::archive::text_oarchive oa(ofs);
		oa << disk1;
	}
	std::string net = ofs.str();

	DiskData disk2;
	std::stringstream ifs(net);
	{
		boost::archive::text_iarchive ia(ifs);
		ia >> disk2;
	}

	BOOST_CHECK(disk1.disk_avg_queue_length == disk2.disk_avg_queue_length);
	BOOST_CHECK(disk1.disk_current_queue_length == disk2.disk_current_queue_length);
	BOOST_CHECK(disk1.disk_free_space == disk2.disk_free_space);
	BOOST_CHECK(disk1.disk_model == disk2.disk_model);
	BOOST_CHECK(disk1.disk_partitions_number == disk2.disk_partitions_number);
	BOOST_CHECK(disk1.disk_percentage_usage == disk2.disk_percentage_usage);
	BOOST_CHECK(disk1.disk_read_kbytes_per_sec == disk2.disk_read_kbytes_per_sec);
	BOOST_CHECK(disk1.disk_size == disk2.disk_size);
	BOOST_CHECK(disk1.disk_write_kbytes_per_sec == disk2.disk_write_kbytes_per_sec);
}

BOOST_AUTO_TEST_CASE(RAMSerialization)
{
	std::stringstream ofs;
	RAMData ram;
	ram.free_ram_size = 1232;
	{
		boost::archive::text_oarchive oa(ofs);
		oa << ram;
	}
	std::string net = ofs.str();

	RAMData ram2;
	std::stringstream ifs(net);
	{
		boost::archive::text_iarchive ia(ifs);
		ia >> ram2;
	}

	BOOST_CHECK(ram.current_cache_size == ram2.current_cache_size);
	BOOST_CHECK(ram.free_ram_size == ram2.free_ram_size);
	BOOST_CHECK(ram.ram_cache_faults_per_sec == ram2.ram_cache_faults_per_sec);
	BOOST_CHECK(ram.ram_clock_speed == ram2.ram_clock_speed);
	BOOST_CHECK(ram.ram_model == ram2.ram_model);
	BOOST_CHECK(ram.ram_page_faults_per_sec == ram2.ram_page_faults_per_sec);
	BOOST_CHECK(ram.ram_percentage_usage == ram2.ram_percentage_usage);
	BOOST_CHECK(ram.ram_size == ram2.ram_size);
	BOOST_CHECK(ram.ram_system_code_size == ram2.ram_system_code_size);
	BOOST_CHECK(ram.ram_used_by_system_drivers_size == ram2.ram_used_by_system_drivers_size);
}



BOOST_AUTO_TEST_SUITE_END()