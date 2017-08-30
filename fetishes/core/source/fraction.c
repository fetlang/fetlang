#include <math.h>
#include <stdlib.h>
#include "core/include/fraction.h"
#include "core/include/error.h"
const FractionInt POW_ACCURACY = (1<<8);	/*256 */


Fraction construct_fraction(FractionInt num, FractionInt den)
{
	Fraction frac;
	frac.num = num;
	frac.den = den;
	reduce_fraction(&frac);
	return frac;
}

void reduce_fraction(Fraction * frac)
{
	// Make sure only numerator has negative
	if(frac->den < 0){
		frac->den = -frac->den;
		frac->num = -frac->num;
	}

	// Fraction is basic
	// Basic bitches go home early
	if(frac->den == 1){
		return;
	}

	// Fix "zero" & "infinity" issues
	if(frac->den==0){
		// Convert fraction to the standard infinity(1/0 or -1/0) or 0/0
		frac->num = (frac->num == 0) ? 0 : (frac->num > 0) ? 1 : -1;
		return; 
	}

	if(frac->num == 0){
		// Convert fraction to the standard zero(0/1)
		frac->den = 1;
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
		a = frac->num;
		b = frac->den;
		gcd = a%b;
		while(gcd != 0){
			a = b;
			b = gcd;
			gcd = a%b;
		}
		frac->num /= b;
		frac->den /=b;
	}while(1 != b);
}

Fraction add_fractions(Fraction a, Fraction b)
{
	Fraction new_frac;

	/* Add fractions with different denominators */
	new_frac.num = a.num * b.den + b.num * a.den;
	new_frac.den = a.den * b.den;

	/* Reduce and return */
	reduce_fraction(&new_frac);
	return new_frac;
}

Fraction subtract_fractions(Fraction a, Fraction b)
{
	/* Just add a negative fraction */
	b.num = -b.num;
	return add_fractions(a, b);
}

Fraction multiply_fractions(Fraction a, Fraction b)
{
	/* Multiply numerator to numerator and denominator to denominator */
	a.num *= b.num;
	a.den *= b.den;
	reduce_fraction(&a);
	return a;
}

Fraction divide_fractions(Fraction a, Fraction b)
{
	/* Multiply numerator with denominator and denominator with numerator */
	a.num *= b.den;
	a.den *= b.num;
	reduce_fraction(&a);
	return a;
}

Fraction modulus_fractions(Fraction a, Fraction b)
{
	/* Reduce fraction before checking errors */
	reduce_fraction(&a);
	if (a.den != 1 || b.den != 1) {
		runtime_error("cannot mod non-integers");
	}

	/* Take modulus */
	a.num %= b.num;

	/* No need to reduce since denominator is 1 */
	return a;
}

Fraction pow_fractions(Fraction a, Fraction b)
{
	int reverse = 0;
	FractionInt i = 0;
	Fraction temp;

	/* Increase accuracy */
	if (a.den > 1) {
		a.num *= POW_ACCURACY;
		a.den *= POW_ACCURACY;
	}

	/* Check for 0^0 error */
	if ((a.num == 0 || a.den == 0) && (b.num == 0 || b.num == 0)) {
		runtime_error
		    ("cannot exponentiate zero or infinity to zero or infinity");
	}

	/* Check if inverse needs to be took */
	if (b.num < 0) {
		reverse = 1;
		b.num = -b.num;
	}

	/* Exponentiate a's numerator with b's numerator */
	temp = a;
	a.num = 1;
	a.den = 1;
	for (i = 0; i < b.num; i++) {
		a.num *= temp.num;
		a.den *= temp.den;
	}

	/* Check if a's num can't be rooted by b's denominator */
	if ((a.num < 0) && (b.den % 2 == 0)) {
		runtime_error
		    ("cannot take even-number root of a negative number");
	}

	/* Root a */
	if (b.den != 1) {
		a.num = (FractionInt) powl((long double) a.num,
					  1 / ((long double) b.den));
		a.den = (FractionInt) powl((long double) a.den,
					  1 / ((long double) b.den));
	}

	/* Reduce, and inverse if necessary */
	if (reverse) {
		i = a.den;
		a.den = a.num;
		a.num = i;
	}
	reduce_fraction(&a);
	return a;
}

int compare_fractions(Fraction a, Fraction b)
{
	/* If whole numbers or infinities, just compare numerators */
	if ((a.den == 1 && b.den == 1) || (a.den == 0 && b.den == 0)) {
		return a.num > b.num ? 1 : a.num < b.num ? -1 : 0;
	}

	/* Infinite number vs finite number */
	if (a.den == 0) {
		return a.num > 0 ? 1 : -1;
	}
	if (b.den == 0) {
		return b.num > 0 ? -1 : 1;
	}

	/* Everything else - return 1 if a>b and -1 if b<a, else 0 */
	return a.num * b.den > b.num * a.den ? 1 : a.num * b.den <
	    b.num * a.den ? -1 : 0;
}

Fraction factorial_fraction(Fraction a)
{
	Fraction new_frac = construct_fraction(1, 1);
	FractionInt n;

	/* Reduce before checking errors */
	reduce_fraction(&a);

	/* Check for illegal moves */
	if (a.den != 1) {
		runtime_error("cannot calculate factorial of non-integer");
	}
	if (a.num < 0) {
		runtime_error
		    ("cannot calculate factorial of negative integer");
	}

	/* Take factorial */
	for (n = 1; n <= a.num; n++) {
		new_frac.num *= n;
	}
	return new_frac;
}
