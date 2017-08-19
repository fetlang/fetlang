#ifndef FETLANG_FRACTION_H_
#define FETLANG_FRACTION_H_
#include "typedefs.h"

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

/* Get Random Fraction */
Fraction random_fraction();
Fraction cryptorandom_fraction();	/* Cryptographically secure version */

/* Get time as Fraction */
Fraction time_fraction();
#endif
