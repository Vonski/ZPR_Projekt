#pragma once
#include <memory>
#include <sciter-x-window.hpp>
#include "Observer.hpp"
#include "CPUData.hpp"
#include "DiskData.hpp"
#include "RAMData.hpp"

class MainView : public Observer
{
public:
	MainView(sciter::window* pwindow, std::shared_ptr<CPUData> cpuu, std::shared_ptr<DiskData> diskk, std::shared_ptr<RAMData> ramm) : pwin(pwindow), cpu1(cpuu), disk(diskk), ram(ramm) {}
	~MainView();
	virtual void update();

private:
	sciter::window* pwin;
	std::shared_ptr<CPUData> cpu1;
	std::shared_ptr<DiskData> disk;
	std::shared_ptr<RAMData> ram;
};

