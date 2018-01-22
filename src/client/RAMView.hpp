#pragma once
#include <memory>
#include <sciter-x-window.hpp>
#include "Observer.hpp"
#include "RAMData.hpp"


class RAMView : public Observer
{
public:
	RAMView(sciter::window* pwindow, std::shared_ptr<RAMData> ramm) : pwin(pwindow), ram(ramm) {}
	~RAMView();
	virtual void update();

private:
	sciter::window* pwin;
	std::shared_ptr<RAMData> ram;
};