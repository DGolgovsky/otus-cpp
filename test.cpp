#include <spdlog/spdlog.h>

#define BOOST_TEST_MODULE TestMain
#include <boost/test/unit_test.hpp>

#include "bin/version.h"

BOOST_AUTO_TEST_SUITE( test_suite )

BOOST_AUTO_TEST_CASE( test_version )
{
	auto console = spdlog::stdout_logger_st("console");
	console->info("test version()");

    BOOST_CHECK( version() > 0 );
}

BOOST_AUTO_TEST_SUITE_END()
