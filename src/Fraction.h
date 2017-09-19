#pragma once
/*
	Fraction class:
		Holds a numerator(top) and a denominator(bottom)
		"Top" and "bottom" sacrifice clarity in favor 
		of keeping up with BDSM themes (obviously more important)
*/
#include <stdint.h>
#include <string>

// Numeric type of top and bottom
typedef int64_t  FractionInt;

class Fraction {
	// Numerator
	FractionInt top;

	// Denominator 
	FractionInt bottom;
	
	// Reduces fraction if top and bottom have a common denominator
	void reduce();

public:
	// Just create the Fraction, bro (and call reduce())
	Fraction(FractionInt top, FractionInt bottom = 1);
	Fraction(const std::string&);
	
	// Getters
	FractionInt getTop() const;
	FractionInt getBottom() const;

	// Setters(call reduce() after setting, please and thank you)
	void setTop(FractionInt);
	void setBottom(FractionInt);

	// Numerical operations
	bool operator==(const Fraction&) const;
	Fraction& operator=(const Fraction&);
	Fraction& operator/=(const Fraction&);
	Fraction operator/(const Fraction&);


};
