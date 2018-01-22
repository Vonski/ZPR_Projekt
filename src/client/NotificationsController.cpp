#define _CRT_SECURE_NO_WARNINGS
#include "NotificationsController.hpp"

using namespace std;

void NotificationsController::update() {
	cout << "notified" << endl;
	if (cpu_data->cpu_percentage_usage > 20)
		makeNotification();
}

void NotificationsController::makeNotification() {
	auto t = chrono::system_clock::now();
	time_t time = std::chrono::system_clock::to_time_t(t);
	if (time - 300 > last_notification_time) {
		string str = (string)(ctime(&time)) + " CPU usage = " + to_string(cpu_data->cpu_percentage_usage) + "%";
		twitter_notifier->tweet(str.c_str());
		last_notification_time = time;
	}
}

void NotificationsController::setCPUData(std::shared_ptr<CPUData> cpu_data) {
	this->cpu_data = cpu_data;
}

void NotificationsController::setTwitterNotifier(std::unique_ptr<TwitterNotifier> twitter_notifier) {
	this->twitter_notifier = move(twitter_notifier);
}