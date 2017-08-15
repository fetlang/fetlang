#include "../thirdparty/catch.hpp"
#include "../FileUtil.h"
#include "../Builder.h"
using namespace FileUtil;
using namespace std;

TEST_CASE("Build and compile Fetish unit tests", "[Builder][Integration]"){
	string fetish_dir = "../fetishes/";
	auto fetishes = getDirectoriesInDirectory(fetish_dir);

	for(const string& fetish : fetishes)
	{
		Builder bob;
		REQUIRE_NOTHROW(bob.setSource(fetish_dir + fetish + "/unit.fet"));
		REQUIRE_NOTHROW(bob.build());
		system("./a.out");
	}

}
