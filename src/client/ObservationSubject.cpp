#include "ObservationSubject.hpp"

void ObservationSubject::notify() { 
	for (Observer* o : observers)
		o->update();
}