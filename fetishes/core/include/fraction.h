#ifndef ORGY_FRACTION_H_
#define ORGY_FRACTION_H_
#include "typedefs.h"

/* Fraction structure for Orgy */
typedef struct OrgyFractionStructure {
	FractionInt num;	/* numerator */
	FractionInt den;	/* denominator */
} Fraction;

/* Fake constructor for Fraction */
Fraction construct_fraction(FractionInt num, FractionInt den);

/* Get Random Fraction */
Fraction random_fraction();
Fraction cryptorandom_fraction();	/* Cryptographically secure version */

/* Get time as Fraction */
Fraction time_fraction();
#endif
