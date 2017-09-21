#include "../thirdparty/catch.hpp"
#include "../FractionParser.h"
using namespace FractionParser;

TEST_CASE("FractionParser works correctly", "[FractionParser]"){
	SECTION("stringToFraction works correctly"){
		REQUIRE(stringToFraction("one") == Fraction(1,1));
		REQUIRE(stringToFraction("one over two") == Fraction(1,2));
		REQUIRE(stringToFraction("negative eight over two hundred and forty six") == Fraction(-8, 246));
		REQUIRE(stringToFraction("negative one thousand") == Fraction(-1000, 1));
		REQUIRE(stringToFraction("eight over two") == Fraction(4));
		REQUIRE(stringToFraction("one over negative sixteen") == Fraction(-1, 16));
		REQUIRE(stringToFraction("one over negative sixteen") == Fraction(1, -16));
		REQUIRE(stringToFraction("five million eight thousand and four") == Fraction(5008004));
		REQUIRE(stringToFraction("zero") == Fraction(0));
		REQUIRE(stringToFraction("infinity") == Fraction(1, 0));
		REQUIRE_THROWS(stringToFraction("poop"));
	}

	SECTION("startsFractionLiteral works correctly"){
		REQUIRE(startsFractionLiteral("one") ==true);
		REQUIRE(startsFractionLiteral("negative") ==true);
		REQUIRE(startsFractionLiteral("eight") ==true);
		REQUIRE(startsFractionLiteral("sixteen") ==true);
		REQUIRE(startsFractionLiteral("poop") == false);
		REQUIRE(startsFractionLiteral("over") == false);
		REQUIRE(startsFractionLiteral("and") == false);
		REQUIRE(startsFractionLiteral("infinity") == true);
		REQUIRE(startsFractionLiteral("zero") == true);
	
	}

	SECTION("partOfFractionLiteral works correctly"){
		REQUIRE(partOfFractionLiteral("one") == true);
		REQUIRE(partOfFractionLiteral("over") == true);
		REQUIRE(partOfFractionLiteral("negative") == true);
		REQUIRE(partOfFractionLiteral("fifty") == true);
		REQUIRE(partOfFractionLiteral("million") == true);
		REQUIRE(partOfFractionLiteral("hundred") == true);
		REQUIRE(partOfFractionLiteral("and") == true);
		REQUIRE(partOfFractionLiteral("poop") == false);
	}
}

