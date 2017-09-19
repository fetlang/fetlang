#include "../thirdparty/catch.hpp"
#include "core/include/fraction.h"

struct CFraction{
	FractionInt num;
	FractionInt den;

	bool operator== (const CFraction& rho) const
	{
		return (rho.num == num);
	}
	CFraction(FractionInt n, FractionInt d)
	{
		num = n;
		den = d;
	}
};

CFraction con_fraction(int a, int b=1)
{
	Fraction frac = construct_fraction(a, b);
	return CFraction(frac.num, frac.den);
}
TEST_CASE("Check C Fractions", "[Fraction][con_fraction]"){
	SECTION("Check C Fraction construction/reduction"){
		REQUIRE(con_fraction(100, 5) == con_fraction(20, 1));
		REQUIRE(con_fraction(100, 5) == con_fraction(200, 10));
		REQUIRE_FALSE(con_fraction(100, 5) == con_fraction(10,5));
		REQUIRE(con_fraction(-10, 5) == con_fraction(-2, 1));
		REQUIRE(con_fraction(-1, 1) == con_fraction(-1, 1));
		REQUIRE(con_fraction(0, 1) == con_fraction(0, 1));
		REQUIRE(con_fraction(0, 200) == con_fraction(0, 1));
		REQUIRE_FALSE(con_fraction(-1) == con_fraction(1, 1));
		REQUIRE_FALSE(con_fraction(0, 1) == con_fraction(1, 1));
		REQUIRE_FALSE(con_fraction(0, 1) == con_fraction(-1, 1));
		REQUIRE(con_fraction(8000000, 8) == con_fraction(1000000, 1));
		for(int i=0; i<200; i++){
			int a = rand();
			int b = rand();
			if(b == 0) continue;
			if(a%b == 0)
			{
				CAPTURE(a);
				CAPTURE(b);
				REQUIRE(con_fraction(a, b) == con_fraction(a/b, 1));
			}
			else
			{
				CAPTURE(a);
				CAPTURE(b);
				REQUIRE_FALSE(con_fraction(a, b) == con_fraction(a/b, 1));
			}
		}
	}
}

