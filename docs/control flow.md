# Control Flow
## Comparison operators
`is` - `==`  
`is not` - `!=`  
`is submissive to` - `<`  
`is dominant towards` - `>`  

## If statements
The scope of if statements and the like are determined by preceding tabs or spaces,
as in Python. And, as in Python 2, it is not recommended to mix the two.  

You can optionally include `otherwise` to execute code when the condition is
false

    if <lho> <comparison operator> <rho>
        ...
        ...
    otherwise
        ...
        ...

## While/until loops
While loops repeat as long as the condition is fulfilled.
Until loops repeat as long as the condition is NOT fulfilled

    [while | until] <lho> <comparison operator> <rho>
        ...
        ...

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
        ...

## Safeword
`call safeword` allows you to exit a scope prematurely.  
