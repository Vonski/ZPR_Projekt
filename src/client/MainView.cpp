#include "MainView.hpp"


MainView::~MainView()
{
}

void MainView::update()
{
	boost::mutex::scoped_lock(cpu1->mutex);
	boost::mutex::scoped_lock(disk->mutex);
	boost::mutex::scoped_lock(ram->mutex);
	pwin->call_function("View.cpuUpdate", sciter::value(cpu1->cpu_percentage_usage));
	pwin->call_function("View.diskUpdate", sciter::value(disk->disk_percentage_usage));
	pwin->call_function("View.ramUpdate", sciter::value(ram->ram_percentage_usage));
}

void MainView::tmp()
{
	pwin->call_function("View.cpuUpdate", sciter::value("XD"));
}
