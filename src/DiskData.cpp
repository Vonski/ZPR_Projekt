#include "DiskData.hpp"
#include "Collector.hpp"

extern Collector* collector;

void DiskData::getData() {

	disk_model = collector->getDiskModel();
	disk_partitions_number=collector->getDiskPartitionsNumber();
	disk_size=collector->getDiskSize();
	disk_free_space=collector->getDiskFreeSpace();
	disk_current_queue_length=collector->getDiskCurrentQueueLength();
	disk_avg_queue_length=collector->getDiskAvgQueueLength();
	disk_read_kbytes_per_sec=collector->getDiskReadKBytesPerSec();
	disk_write_kbytes_per_sec=collector->getDiskWriteKBytesPerSec();
	disk_percentage_usage = collector->getDiskPercentageUsage();

}