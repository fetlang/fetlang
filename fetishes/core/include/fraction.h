#ifndef FETLANG_CORE_FRACTION_H_
#define FETLANG_CORE_FRACTION_H_
#include "core/include/typedefs.h"
#ifdef __cplusplus
extern "C" {
#endif

/* Fraction structure for Fetlang */
typedef struct Fraction {
	FractionInt num;	/* numerator */
	FractionInt den;	/* denominator */
} Fraction;

/**
 * Construct Fraction
 *
 *
 * @param num The numerator
 * @param den The denominator
 * @return The fraction constructed
 */
Fraction construct_fraction(FractionInt num, FractionInt den);

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

/**
 * Reduce fraction to most basic form
 *
 *
 * @param a The fraction to be reduced
 */
void reduce_fraction(Fraction * a);

/* Fraction math */
/**
 * Add two fractions
 *
 *
 * @param a The first fraction
 * @param b The second fraction
 * @result a+b
 */
Fraction add_fractions(Fraction a, Fraction b);
/**
 * Subtract two fractions
 *
 *
 * @param a The first fraction
 * @param b The second fraction
 * @result a-b
 */
Fraction subtract_fractions(Fraction a, Fraction b);
/**
 * Multiply two fractions
 *
 *
 * @param a The first fraction
 * @param b The second fraction
 * @result a*b
 */
Fraction multiply_fractions(Fraction a, Fraction b);
/**
 * Divide two fractions
 *
 *
 * @param a The first fraction
 * @param b The second fraction
 * @result a/b
 */
Fraction divide_fractions(Fraction a, Fraction b);

/**
 * Modulus fractions
 *
 * Get remainder after dividing two fractions. Throw an error if the fractions
 * are non-integers
 *
 * @param a The first fraction
 * @param b The second fraction
 * @result a%b
 */
Fraction modulus_fractions(Fraction a, Fraction b);
/**
 * Get factorial of fraction
 *
 * Return the factorial of a fraction. Throw an error if the fractions
 * are non-integers
 *
 * @param a The fraction to be factorialized
 * @result a!
 */
Fraction factorial_fraction(Fraction a);

/**
 * Compare fractions
 *
 * Return 0 if fractions are equal, -1 if a<b, and 1 if a>b
 *
 * @param a The first fraction
 * @param b The second fraction
 * @result The comparison result
 */
int compare_fractions(Fraction a, Fraction b);

/**
 * Exponentiate fractions
 *
 * Return a to the bth power. This uses floating point math, so the answer will
 * not be exact. Invalid arguments will throw an error.
 *
 * @param a The first fraction
 * @param b The second fraction
 * @result a^b
 */
Fraction pow_fractions(Fraction a, Fraction b);

#ifdef __cplusplus
}
#endif
#endif
