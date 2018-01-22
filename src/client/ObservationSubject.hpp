#pragma once
#include "Observer.hpp"
#include <vector>
#include <algorithm>
#include <memory>

class ObservationSubject {
public:
	void addObserver(std::shared_ptr<Observer> o) { observers.push_back(o); }
	void removeObserver(std::shared_ptr<Observer> o) { observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end()); }
	void notify();
	//virtual ~ObservationSubject() {};
private:
	std::vector<std::shared_ptr<Observer>> observers;
};
