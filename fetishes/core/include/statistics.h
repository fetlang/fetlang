#ifndef ORGY_STATISTICS_H_
#define ORGY_STATISTICS_H_
#include "fraction.h"
#include "chain.h"

/* Sum up chain and return as fraction, empty sum is zero */
Fraction chain_sum(Chain chain);

/* Return product, empty product is 1 */
Fraction chain_product(Chain chain);

/* Return sum divided by length */
Fraction chain_mean(Chain chain);

/* Return highest fraction, error if length<1 */
Fraction chain_max(Chain chain);

/* Return lowest fraction, error if length<1 */
Fraction chain_min(Chain chain);

/* Return variance of chain, error if length<2 */
Fraction chain_variance(Chain chain);

/* Return standard deviation of chain, error if length<2 */
Fraction chain_stdev(Chain chain);
#endif
