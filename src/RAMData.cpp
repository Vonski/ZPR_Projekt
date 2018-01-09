#include "RAMData.hpp"
#include "Collector.hpp"

extern Collector* collector;

void RAMData::getData() {

	ram_percentage_usage = collector->getRAMPercentageUsage();
	ram_size = collector->getRAMSize();
	free_ram_size = collector->getFreeRamSize();
	current_cache_size = collector->getCurrentCacheSize();
	ram_page_faults_per_sec=collector->getRAMPageFaultsPerSec();
	ram_clock_speed=collector->getRAMClockSpeed();
	ram_model=collector->getRAMModel();
	ram_cache_faults_per_sec=collector->getRAMCacheFaultsPerSec();
	ram_system_code_size=collector->getRAMSystemCodeSize();
	ram_used_by_system_drivers_size = collector->getRAMUsedBySystemDriverSize();
	
}