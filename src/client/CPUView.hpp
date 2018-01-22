#pragma once
#include <memory>
#include <sciter-x-window.hpp>
#include "Observer.hpp"
#include "CPUData.hpp"


class CPUView : public Observer
{
public:
	CPUView(sciter::window* pwindow, std::shared_ptr<CPUData> cpuu) : pwin(pwindow), cpu1(cpuu) {}
	~CPUView();
	virtual void update();

private:
	sciter::window* pwin;
	std::shared_ptr<CPUData> cpu1;
};