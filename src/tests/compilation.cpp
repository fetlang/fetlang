#include "../thirdparty/catch.hpp"
#include "../FileUtil.h"
#include "../Builder.h"
using namespace FileUtil;
using namespace std;
const string fetish_dir = "../fetishes/";
const auto fetishes = getDirectoriesInDirectory(fetish_dir);
const string out = "./output_from_unit_tests.exe";

// Run the unit.fet file in every fetish
void runFetishUnitTests(Builder& bob){
	for(const string& fetish : fetishes)
	{
		REQUIRE_NOTHROW(bob.setSource(fetish_dir + fetish + "/unit.fet"));
		REQUIRE_NOTHROW(bob.setDestination(out));
		REQUIRE_NOTHROW(bob.build());
		if(system(out.c_str()))
		{
			CAPTURE(fetish);
			FAIL("Compiled fetish unit test returned error");
		}
	}
}

TEST_CASE("Build and compile Fetish unit tests", "[Builder][Integration]"){

	ensureFileDoesNotExist(out);
	Builder bob;
	REQUIRE_NOTHROW(bob.clean());

	SECTION("Build and compile unoptimized Fetish unit tests"){
		bob.setLinkTimeOptimization(false);
		bob.setOptimization(false);
		runFetishUnitTests(bob);
	}

	SECTION("Build and compile link time optimized Fetish unit tests"){
		bob.setLinkTimeOptimization(true);
		bob.setOptimization(false);
		runFetishUnitTests(bob);
	}

	SECTION("Build and compile fully optimized Fetish unit tests"){
		bob.setLinkTimeOptimization(true);
		bob.setOptimization(true);
		runFetishUnitTests(bob);
	}

	SECTION("Build and compile optimized Fetish unit tests"){
		bob.setLinkTimeOptimization(false);
		bob.setOptimization(true);
		runFetishUnitTests(bob);
	}

}
