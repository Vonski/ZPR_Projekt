#pragma once
#include "Observer.hpp"
#include <vector>


class ObservationSubject {
public:
	void add(Observer* o) { observers.push_back(o); }
	void notify();
	//virtual ~ObservationSubject() {};
private:
	std::vector<Observer*> observers;
};
