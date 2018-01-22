#include "DiskView.hpp"

DiskView::~DiskView()
{
}

void DiskView::update()
{
	boost::mutex::scoped_lock(disk->mutex);
	pwin->call_function("View.setDiskDetails1", sciter::value(disk->disk_percentage_usage),
		sciter::value(disk->disk_size),
		sciter::value(disk->disk_free_space),
		sciter::value(disk->disk_partitions_number));
	pwin->call_function("View.setDiskDetails2", sciter::value(disk->disk_write_kbytes_per_sec),
		sciter::value(disk->disk_read_kbytes_per_sec),
		sciter::value(disk->disk_current_queue_length));
}
