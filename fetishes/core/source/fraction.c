#include "fraction.h"
#include "fraction_math.h"
#include "error.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

Fraction construct_fraction(FractionInt num, FractionInt den)
{
	Fraction frac;
	frac.num = num;
	frac.den = den;
	return frac;
}

/* Produces a random 64-bit signed integer */
static int64_t random64()
{
	/* Seed with time if have not done so */
	static int have_seeded = 0;
	if (have_seeded == 0) {
		srand(time(NULL));
		have_seeded = 1;
	}

	/* rand() is guaranteed to be at least 16-bits, therefore
	   we treat the following code this way. */

	/* We will combine four numbers to create a 64-bit number */
	return ((int64_t) rand() << 0) ^
	    ((int64_t) rand() << 16) ^
	    ((int64_t) rand() << 32) ^ ((int64_t) rand() << 48);

}

/* Produces a crytographically secure 64-bit signed integer */
/* Get numbers from /dev/urandom on POSIX systems
   Use WinAPI on Windows systems */
static int64_t cryptorandom64()
{
	FILE *urandom = fopen("/dev/urandom", "r");
	int64_t result = 0;
	unsigned int i;

	if (urandom == NULL) {
		runtime_error("could not access /dev/urandom");
	}

	for (i = 0; i <= sizeof(result); i++) {
		int c = (signed char) fgetc(urandom);
		result += (result << 8) | ((int64_t) (c & 255));
	}

	fclose(urandom);
	return result;
}

Fraction random_fraction()
{
	FractionInt den = (FractionInt) random64();
	Fraction rfrac = construct_fraction((FractionInt) random64(),
					    den > 0 ? den : -den);
	reduce_fraction(&rfrac);
	return rfrac;
}

Fraction cryptorandom_fraction()
{
	FractionInt den = (FractionInt) cryptorandom64();
	Fraction rfrac = construct_fraction((FractionInt) cryptorandom64(),
					    den > 0 ? den : -den);
	reduce_fraction(&rfrac);
	return rfrac;
}

Fraction time_fraction()
{
	return construct_fraction((FractionInt) time(NULL), 1);
}
