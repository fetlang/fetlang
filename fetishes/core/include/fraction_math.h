#ifndef ORGY_FRACTION_MATH_H_
#define ORGY_FRACTION_MATH_H_

#include "fraction.h"
/*
	Fraction math rules:
		1) 0/0 is not allowed
		2) n/0 IS allowed, as long as |n|>0
		3) n/0 is treated as infinity, but 2/0 > 1/0
		4) 0 should only exist in the form 0/1
		5) 0^0 is not allowed
		6) Modulus and factorial should involve integers only
		7) Only numerators can be negative
*/

/* Exact rational math */
/* Reduction */
void reduce_fraction(Fraction * a);
/* Fraction math */
Fraction add_fractions(Fraction a, Fraction b);
Fraction subtract_fractions(Fraction a, Fraction b);
Fraction multiply_fractions(Fraction a, Fraction b);
Fraction divide_fractions(Fraction a, Fraction b);
/* Integer math (error if non integer) */
Fraction modulus_fractions(Fraction a, Fraction b);
Fraction factorial_fraction(Fraction a);

/* Comparative math
   1 : a>b
   0 : a==b
   -1 : a<b
*/
int compare_fractions(Fraction a, Fraction b);

/* Estimation math */
Fraction pow_fractions(Fraction a, Fraction b);
#endif
