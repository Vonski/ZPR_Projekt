#include "ViewController.hpp"



ViewController::ViewController(sciter::window* pwindow, shared_ptr<CPUData> cpuu, shared_ptr<DiskData> diskk, shared_ptr<RAMData> ramm) : pwin(pwindow), cpu1(cpuu), disk(diskk), ram(ramm)
{
	mv = make_shared<MainView>(pwin, cpu1, disk, ram);
	cpuv = make_shared<CPUView>(pwin, cpu1);
	diskv = make_shared<DiskView>(pwin, disk);
	ramv = make_shared<RAMView>(pwin, ram);
	cpu1->addObserver(mv);
	disk->addObserver(mv);
	ram->addObserver(mv);
	active = ActiveView::MAIN;
}


ViewController::~ViewController()
{
}

void ViewController::changeView(int nextView)
{
	if (nextView == 0)
	{
		if(active==ActiveView::CPU)
			cpu1->removeObserver(cpuv);
		else if (active == ActiveView::DISK)
			disk->removeObserver(diskv);
		else if (active == ActiveView::RAM)
			ram->removeObserver(ramv);

		cpu1->addObserver(mv);
		disk->addObserver(mv);
		ram->addObserver(mv);
		active = ActiveView::MAIN;
		return;
	}

	cpu1->removeObserver(mv);
	disk->removeObserver(mv);
	ram->removeObserver(mv);
	if (nextView == 1)
	{
		cpu1->addObserver(cpuv);
		active = ActiveView::CPU;
	}
	if (nextView == 2)
	{
		disk->addObserver(diskv);
		active = ActiveView::DISK;
	} 
	if (nextView == 3)
	{
		ram->addObserver(ramv);
		active = ActiveView::RAM;
	}
}
