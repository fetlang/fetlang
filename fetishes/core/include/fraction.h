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

/**
 * Get random fraction
 *
 *
 * @return A random fraction
 */
Fraction random_fraction();

/**
 * Get time as fraction
 *
 *
 * @return Unix time as fraction
 */
Fraction time_fraction();

#ifdef __cplusplus
}
#endif
#endif
