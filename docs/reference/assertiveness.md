# Assertiveness
Runtime assertions - intended for unit testing
## Operators
### assert dominance over
Assert that the RHO is greater than the LHO  

Examples:  
`Have Alice assert dominance over Bob`  

C Code:  
fraction/fraction - `fetlang_assert(compare_fractions(RHO, LHO) == 1, "assertion of dominance failed");`  

### assert equality with
Assert that the LHO and RHO are equal  

Examples:  
`Have Alice assert equality with Eve`  

C Code:  
fraction/fraction - `fetlang_assert(!compare_fractions(RHO, LHO), "assertion of equality between fractions failed");`  
chain/chain - `fetlang_assert(!compare_chains(RHO, LHO), "assertion of equality between chains failed");`  

