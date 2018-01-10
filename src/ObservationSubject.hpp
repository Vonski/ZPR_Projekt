#pragma once
#include "Observer.hpp"
#include <vector>


class ObservationSubject {
	void add(Observer* o) { observers.push_back(o); }
	void notify();
	virtual ~ObservationSubject() = 0;
private:
	std::vector<Observer*> observers;
};
