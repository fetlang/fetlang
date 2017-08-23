#include "../thirdparty/catch.hpp"
#include "../Fraction.h"

TEST_CASE("Fraction works correctly", "[Fraction]"){
	SECTION("Check reduction/construction"){
		REQUIRE(Fraction(100, 5) == Fraction(20, 1));
		REQUIRE(Fraction(100, 5) == Fraction(200, 10));
		REQUIRE_FALSE(Fraction(100, 5) == Fraction(10,5));
		REQUIRE(Fraction(-10, 5) == Fraction(-2, 1));
		REQUIRE(Fraction(-1) == Fraction(-1));
		REQUIRE(Fraction(0) == Fraction(0));
		REQUIRE(Fraction(0, 200) == Fraction(0));
		REQUIRE_FALSE(Fraction(-1) == Fraction(1));
		REQUIRE_FALSE(Fraction(0) == Fraction(1));
		REQUIRE_FALSE(Fraction(0) == Fraction(-1));
		REQUIRE(Fraction(8000000, 8) == Fraction(1000000));
		for(int i=0; i<200; i++){
			int a = rand();
			int b = rand();
			if(b == 0) continue;
			if(a%b == 0)
			{
				CAPTURE(a);
				CAPTURE(b);
				REQUIRE(Fraction(a, b) == Fraction(a/b));
			}
			else
			{
				CAPTURE(a);
				CAPTURE(b);
				REQUIRE_FALSE(Fraction(a, b) == Fraction(a/b));
			}
		}
	}
}

