#pragma once
#include "Observer.hpp"
#include "CPUData.hpp"
#include "TwitterNotifier.hpp"
#include <time.h>
#include <iostream>
#include <chrono>
#include <time.h>

class NotificationsController : public Observer {
public:
	void makeNotification();
	virtual void update();
	void setCPUData(CPUData* cpu_data);
	void setTwitterNotifier(TwitterNotifier* twitter_notifier);
private:
	CPUData* cpu_data;
	TwitterNotifier* twitter_notifier;
	time_t last_notification_time=0;
};