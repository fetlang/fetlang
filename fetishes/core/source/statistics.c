#include <stdlib.h>
#include "statistics.h"
#include "fraction_math.h"
#include "error.h"

Fraction chain_sum(Chain chain)
{
	/* Declare iterator */
	Link *it = chain.start;

	/* Declare sum and initiate it to zero */
	Fraction sum = construct_fraction(0, 1);

	/* Compute sum */
	while (it != NULL) {
		sum = add_fractions(sum, it->value);
		it = it->next;
	}

	/* Return sum */
	return sum;
}

Fraction chain_product(Chain chain)
{
	/* Declare iterator */
	Link *it = chain.start;

	/* Declare product and initiate it to one */
	Fraction product = construct_fraction(1, 1);

	/* Compute product */
	while (it != NULL) {
		product = multiply_fractions(product, it->value);
		it = it->next;
	}

	/* Return product */
	return product;
}

Fraction chain_mean(Chain chain)
{
	/* Return sum divided by length */
	return divide_fractions(chain_sum(chain),
				construct_fraction(chain.length, 1));
}

Fraction chain_max(Chain chain)
{
	Fraction max;
	Link *it;

	/* Raise error if needed */
	if (chain.length == 0) {
		runtime_error("cannot find maximum of an empty chain");
	}

	/* Set iterator */
	it = chain.start;

	/* Initial maximum */
	max = it->value;

	/* Find max */
	while (it->next != NULL) {
		/* Forward iterator */
		it = it->next;

		/* Set max equal to new value if new value > old value */
		max =
		    compare_fractions(max,
				      it->value) != -1 ? max : it->value;
	}

	return max;
}

Fraction chain_min(Chain chain)
{
	Fraction min;
	Link *it;

	/* Raise error if needed */
	if (chain.length == 0) {
		runtime_error("cannot find minimum of an empty chain");
	}

	it = chain.start;
	min = it->value;

	while (it->next != NULL) {
		it = it->next;
		min =
		    compare_fractions(min,
				      it->value) == -1 ? min : it->value;
	}

	return min;
}

Fraction chain_variance(Chain chain)
{
	Fraction mean;
	Fraction length;
	Fraction var;
	Fraction temp;
	Fraction exponent;
	Link *it;

	/* Get mean */
	mean = chain_mean(chain);

	/* Get length */
	length = construct_fraction(chain.length, 1);

	/* Set exponent to 2 */
	exponent = construct_fraction(2, 1);

	/* Sum up (x-mean)^2 */
	it = chain.start;
	var = construct_fraction(0, 1);
	while (it != NULL) {
		/* Calculate (x-mean)^2 */
		temp = it->value;
		temp = subtract_fractions(temp, mean);
		temp = pow_fractions(temp, exponent);

		/* Add to  sum */
		var = add_fractions(var, temp);

		/* Forward iterator */
		it = it->next;
	}

	/* Divide by length-1 to get variance */
	length.num -= 1;
	return divide_fractions(var, length);
}

Fraction chain_stdev(Chain chain)
{
	/* Return square root of variance */
	return pow_fractions(chain_variance(chain),
			     construct_fraction(1, 2));
}
