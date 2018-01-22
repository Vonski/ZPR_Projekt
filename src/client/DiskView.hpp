#pragma once
#include <boost/thread/mutex.hpp>
#include <memory>
#include <sciter-x-window.hpp>
#include "Observer.hpp"
#include "DiskData.hpp"


class DiskView : public Observer
{
public:
	DiskView(sciter::window* pwindow, std::shared_ptr<DiskData> diskk) : pwin(pwindow), disk(diskk) {}
	~DiskView();
	virtual void update();

private:
	sciter::window* pwin;
	std::shared_ptr<DiskData> disk;
};