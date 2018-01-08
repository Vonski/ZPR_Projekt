#define BOOST_TEST_MODULE MyTest
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include "Testable.hpp"

BOOST_AUTO_TEST_CASE(my_test)
{
	BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(my_test1)
{
	BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(TestableTests)
{
	Testable test;
	BOOST_CHECK(test.k == 0);

	Testable test2(3);
	BOOST_CHECK(test2.k == 3);

	Testable test3(4);
	BOOST_CHECK(test3.k == 4);
}