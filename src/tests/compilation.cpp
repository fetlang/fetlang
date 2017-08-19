#include "../thirdparty/catch.hpp"
#include "../FileUtil.h"
#include "../Builder.h"
using namespace FileUtil;
using namespace std;

TEST_CASE("Build and compile Fetish unit tests", "[Builder][Integration]"){
	const string fetish_dir = "../fetishes/";
	const string out = "./output_from_unit_tests.exe";
	const auto fetishes = getDirectoriesInDirectory(fetish_dir);

	ensureFileDoesNotExist(out);
	Builder bob;
	REQUIRE_NOTHROW(bob.clean());

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
