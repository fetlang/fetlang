#pragma once
/*
	Fraction Parser namespace
	
	A namespace to handle all the modern-day issues of parsing strings to create a Fraction
*/
#include <string>
#include <stdexcept>
#include "Fraction.h"

namespace FractionParser {
	// Make Fraction from string
	Fraction stringToFraction(const std::string&);

	// Determines if a string is the first part of a fraction literal
	bool startsFractionLiteral(const std::string&);

	// Or any part
	bool partOfFractionLiteral(const std::string&);
}
