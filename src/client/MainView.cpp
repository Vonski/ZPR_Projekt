#include "MainView.hpp"


MainView::~MainView()
{
}

void MainView::update()
{
	pwin->call_function("Accounts.cpuUpdate", sciter::value(cpu1->cpu_percentage_usage));
}
