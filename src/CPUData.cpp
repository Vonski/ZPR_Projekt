#include "CPUData.hpp"
#include "Collector.hpp"

extern Collector* collector;

void CPUData::getData(){

	cpu_percentage_usage = collector->getCPUPercentageUsage();
	cpu_manufacturer = collector->getCpuManufacturer();
	cpu_max_clock_speed=collector->getCPUMaxClockSpeed();
	cpu_number_of_cores=collector->getCPUNumberOfCores();
	cpu_number_of_logical_processors=collector->getCPUNumberOfLogicalProcessors();
	cpu_name=collector->getCPUName();
	cpu_current_clock_speed=collector->getCPUCurrentClockSpeed();
	cpu_current_voltage=collector->getCPUCurrentVoltage();
	cpu_load_percentage=collector->getCPULoadPercentage();
}