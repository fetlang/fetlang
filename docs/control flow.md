# Control Flow
## Comparison operators
`is` - `==`  
`is not` - `!=`  
`is submissive to` - `>=`  
`is dominant towardds` - `<=`  

## If statements
    if <lho> <comparison operator> <rho>
    ...
    end if

## While/until loops
While loops repeat as long as the condition is fulfilled.
Until loops repeat as long as the condition is NOT fulfilled.

    [while | until] <lho> <comparison operator> <rho>
    ...
    more please

## Bondage loops
Bondage loops allow you to iterate through a chain.  
This seems to be the only current way to access a value
inside a chain

The LHO becomes a pointer to the values in the RHO
If RHO is not a chain, LHO just becomes equivalent
to RHO

A variable in bondage will remain in bondage

    bind <lho> to <rho>
    ...
    more please

## Safeword
`call safeword` allows you to exit a scope prematurely.  
