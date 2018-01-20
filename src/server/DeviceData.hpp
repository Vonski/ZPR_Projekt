#pragma once
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/thread/mutex.hpp>

struct DeviceData {
	//virtual void getData() = 0;
	boost::mutex mutex;
};