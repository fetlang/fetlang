## Comparison operators
`IS` - `==`  
`IS NOT` - `!=`  
`IS SUBMISSIVE TO` - `>=`  
`IS DOMINANT TOWARDS` - `<=`  

## `IF` statements
    IF <lho> [COMPARISON OPERATOR] <rho>
    ...
    END IF

## `WHILE`/`UNTIL` loops
While loops repeat as long as the condition is fulfilled.
Until loops repeat as long as the condition is NOT fulfilled.

    [WHILE | UNTIL] <lho> [COMPARISON] <rho>
    ...
    MORE PLEASE

## Bondage loops
Bondage loops allow you to iterate through a chain.  
This seems to be the only current way to access a value
inside a chain

The LHO becomes a pointer to the values in the RHO
If RHO is not a chain, LHO just becomes equivalent
to RHO

A variable in bondage will remain in bondage

    BIND <lho> TO <rho>
    ...
    MORE PLEASE

## Safewords
Safewords allow you to exit a scope prematurely.  
Safewords are not bound to any particular scope,
making them effectively `break` or `return`
statements.  

    THE SAFEWORD IS <safeword>
    ...
    <safeword>

