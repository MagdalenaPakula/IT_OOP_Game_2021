#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>

using namespace boost::unit_test;

struct MyConfig
{
};

BOOST_GLOBAL_FIXTURE(MyConfig);