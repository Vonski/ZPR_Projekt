#include <boost/test/unit_test.hpp>
#include "client/Observer.hpp"
#define private public
#include "client/ObservationSubject.hpp"
#undef private

class ConcreteObserver : public Observer {
	virtual void update() {}
};

BOOST_AUTO_TEST_SUITE(ObserverPatternTestSuite)

BOOST_AUTO_TEST_CASE(AddingObserver)
{
	ConcreteObserver cObserver;
	ObservationSubject obsSubject;

	obsSubject.addObserver(&cObserver);
	BOOST_CHECK(std::find(obsSubject.observers.begin(), obsSubject.observers.end(), &cObserver) != obsSubject.observers.end());
}

BOOST_AUTO_TEST_CASE(RemovingObserver)
{
	ConcreteObserver cObserver;
	ObservationSubject obsSubject;

	obsSubject.addObserver(&cObserver);
	obsSubject.removeObserver(&cObserver);
	BOOST_CHECK(std::find(obsSubject.observers.begin(), obsSubject.observers.end(), &cObserver) == obsSubject.observers.end());
}

BOOST_AUTO_TEST_SUITE_END()