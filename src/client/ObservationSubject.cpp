#include "ObservationSubject.hpp"

void ObservationSubject::notify() { 
	for (std::shared_ptr<Observer> o : observers)
		o->update();
}