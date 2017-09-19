#include "Fraction.h"
#include "FractionParser.h"
#include <cmath>

Fraction::Fraction(FractionInt top, FractionInt bottom){
	this->top = top;
	this->bottom = bottom;
	this->reduce();
}

Fraction::Fraction(const std::string& fraction_string){
	Fraction fraction = FractionParser::stringToFraction(fraction_string);
	this->top = fraction.getTop();
	this->bottom = fraction.getBottom();
}

FractionInt Fraction::getTop() const{
	return this->top;
}

FractionInt Fraction::getBottom() const{
	return this->bottom;
}

// Make sure we reduce the fraction
// every time we change its values
void Fraction::setTop(FractionInt top) {
	this->top = top;
	this->reduce();
}

void Fraction::setBottom(FractionInt bottom){
	this->bottom = bottom;
	this->reduce();
}

void Fraction::reduce(){
	// Make sure only numerator has negative
	if(this->bottom < 0){
		this->bottom = -this->bottom;
		this->top = -this->top;
	}

	// Fraction is basic
	// Basic bitches go home early
	if(this->bottom == 1){
		return;
	}

	// Fix "zero" & "infinity" issues
	if(this->bottom==0){
		// Convert fraction to the standard infinity(1/0 or -1/0) or 0/0
		this->top = (this->top == 0) ? 0 : (this->top > 0) ? 1 : -1;
		return; 
	}

	if(this->top == 0){
		// Convert fraction to the standard zero(0/1)
		this->bottom = 1;
		return;
	}

	// Reduce the fraction something something greatest
	// common denominator something something algorithm
	//
	// It's a good thing I took discrete math
	FractionInt gcd;
	FractionInt a;
	FractionInt b; 
	do{
		a = this->top;
		b = this->bottom;
		gcd = a%b;
		while(gcd != 0){
			a = b;
			b = gcd;
			gcd = a%b;
		}
		this->top /= b;
		this->bottom /=b;
	}while(1 != b);
}

bool Fraction::operator==(const Fraction& rhs) const{
	return (this->top == rhs.top) && (this->bottom == rhs.bottom);
}

Fraction& Fraction::operator=(const Fraction& rhs){
	this->top = rhs.top;
	this->bottom = rhs.bottom;
	// Other fraction should already be reduce()'d, so
	// we don't need to reduce() again
	return *this;
}
Fraction Fraction::operator/(const Fraction& rhs){
	Fraction return_value = *this;
	return_value.top *= rhs.bottom;
	return_value.bottom *= rhs.top;
	// Here we do need to reduce()
	// because we are changing values to something
	// new
	return_value.reduce();
	return return_value;
}
Fraction& Fraction::operator/=(const Fraction& rhs){
	// Reduce() is called with '/' operator
	*this = *this / rhs;
	return *this;
}
