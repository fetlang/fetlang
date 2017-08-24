#include "core/include/fraction.h"
#include "core/include/fraction_math.h"
#include "core/include/error.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

Fraction construct_fraction(FractionInt num, FractionInt den)
{
	Fraction frac;
	frac.num = num;
	frac.den = den;
	reduce_fraction(&frac);
	return frac;
}

