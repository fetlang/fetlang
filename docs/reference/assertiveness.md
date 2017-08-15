# Assertiveness
Runtime assertions - intended for unit testing
## Operators
### assert dominance over
The `assert dominance over` operator asserts that the rho is over the lho
Examples:  
`Have Alice assert dominance over Bob`  
C Code:  
fraction/fraction - `fetlang_assert(compare_fractions(RHO, LHO) == 1, "assertion of dominance failed");`  
### assert equality with
Assertion of equality
Examples:  
`Have Alice assert equality with Eve`  
C Code:  
fraction/fraction - `fetlang_assert(!compare_fractions(RHO, LHO), "assertion of equality between fractions failed");`  
chain/chain - `fetlang_assert(!compare_chains(RHO, LHO), "assertion of equality between chains failed");`  
