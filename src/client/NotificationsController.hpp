#pragma once
#include <time.h>
#include <iostream>
#include <chrono>
#include <memory>
#include "Observer.hpp"
#include "CPUData.hpp"
#include "TwitterNotifier.hpp"


class NotificationsController : public Observer {
public:
	void makeNotification();
	virtual void update();
	void setCPUData(std::shared_ptr<CPUData> cpu_data);
	void setTwitterNotifier(std::unique_ptr<TwitterNotifier> twitter_notifier);
private:
	std::shared_ptr<CPUData> cpu_data;
	std::unique_ptr<TwitterNotifier> twitter_notifier;
	time_t last_notification_time=0;
};