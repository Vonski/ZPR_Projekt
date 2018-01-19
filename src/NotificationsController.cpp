#define _CRT_SECURE_NO_WARNINGS
#include "NotificationsController.hpp"

using namespace std;

void NotificationsController::update() {
	if (cpu_data->cpu_percentage_usage > 90)
		makeNotification();
}

void NotificationsController::makeNotification() {
	auto t = chrono::system_clock::now();
	time_t time = std::chrono::system_clock::to_time_t(t);
	if (time - 300 > last_notification_time) {
		string str = (string)(ctime(&time)) + " CPU usage over 90%";
		twitter_notifier->tweet(str.c_str());
		last_notification_time = time;
	}
}

void NotificationsController::setCPUData(CPUData* cpu_data) {
	this->cpu_data = cpu_data;
}

void NotificationsController::setTwitterNotifier(TwitterNotifier* twitter_notifier) {
	this->twitter_notifier = twitter_notifier;
}