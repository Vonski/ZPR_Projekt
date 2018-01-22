#pragma once
#include <memory>
#include <sciter-x-window.hpp>
#include "CPUData.hpp"
#include "DiskData.hpp"
#include "RAMData.hpp"
#include "MainView.hpp"
#include "CPUView.hpp"
#include "DiskView.hpp"
#include "RAMView.hpp"

enum class ActiveView { MAIN, CPU, DISK, RAM };

class ViewController
{
public:
	ViewController(sciter::window* pwindow, shared_ptr<CPUData> cpuu, shared_ptr<DiskData> diskk, shared_ptr<RAMData> ramm);
	~ViewController();
	void changeView(int nextView);

private:
	sciter::window* pwin;
	std::shared_ptr<MainView> mv;
	std::shared_ptr<CPUView> cpuv;
	std::shared_ptr<DiskView> diskv;
	std::shared_ptr<RAMView> ramv;
	std::shared_ptr<CPUData> cpu1;
	std::shared_ptr<DiskData> disk;
	std::shared_ptr<RAMData> ram;
	ActiveView active;
};

