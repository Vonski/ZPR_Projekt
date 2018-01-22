#include "RAMView.hpp"

RAMView::~RAMView()
{
}

void RAMView::update()
{
	boost::mutex::scoped_lock(ram->mutex);
	pwin->call_function("View.setRAMDetails1", sciter::value(ram->ram_percentage_usage),
		sciter::value(ram->ram_size),
		sciter::value(ram->free_ram_size),
		sciter::value(ram->current_cache_size));
	pwin->call_function("View.setRAMDetails2", sciter::value(ram->ram_clock_speed),
		sciter::value(ram->ram_cache_faults_per_sec),
		sciter::value(ram->ram_page_faults_per_sec));
}
