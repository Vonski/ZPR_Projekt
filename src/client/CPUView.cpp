#include "CPUView.hpp"

CPUView::~CPUView()
{
}

void CPUView::update()
{
	pwin->call_function("View.setCPUDetails1", sciter::value(cpu1->cpu_percentage_usage),
		sciter::value(cpu1->cpu_name),
		sciter::value(cpu1->cpu_number_of_cores),
		sciter::value(cpu1->cpu_number_of_logical_processors));
	pwin->call_function("View.setCPUDetails2", sciter::value(cpu1->cpu_max_clock_speed),
		sciter::value(cpu1->cpu_current_clock_speed),
		sciter::value(cpu1->cpu_current_voltage));
}
