#include "../thirdparty/catch.hpp"
#include "../QuoteUtil.h"

TEST_CASE("QuoteUtil works correctly", "[QuoteUtil]"){
	SECTION("QuoteUtil quotes correctly"){
		REQUIRE(QuoteUtil::quote("Hello") == "\"Hello\"");
		REQUIRE(QuoteUtil::quote("H\nllo World!") == "\"H\\nllo World!\"");
		// Should be in Octal
		// 0x12 == 16+2 == 18 == 2*8 + 2 
		REQUIRE(QuoteUtil::quote("\x12") == "\"\\022\"");
	}

	SECTION("QuoteUtil unquotes correctly"){
		REQUIRE(QuoteUtil::unquote("\"Hello World!\\n\"") == "Hello World!\n");
		REQUIRE(QuoteUtil::unquote("\"\\5\"") == "\5");
		REQUIRE(QuoteUtil::unquote("\"\\5\n\t\a\"") == "\5\n\t\a");
		REQUIRE(QuoteUtil::unquote("\"\\\"\"") == "\"");
		REQUIRE(QuoteUtil::unquote("\"\"") == "");
	}
}
