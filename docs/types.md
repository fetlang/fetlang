# Types
## Fractions
All numbers in Fetlang are represented as fractions: a numerator over a
denominator.
As a result, there is very little floating point math in Fetlang.

Fraction literals are represented by words. For example, -45153/71 is
represented by:

    negative forty five thousand one hundred and fifty three over
    seventy one

When printed to stdout, fractions are written with commas:

    negative forty five thousand, one hundred and fifty three over
    seventy one

When read from stdin, fractions are inputed as:

    -45153/71

Normally, 0/0 is not allowed, but when inputed by the user it is equal
to 1/1.

## Variables in Bondage, or Reference Types
A [variable](variables.md) in bondage (reference type) is bound to particular fraction,
and decays to that fraction. The major difference is that it can be 
rebound to a different fraction, namely a fraction in a chain  

This is the only way to iterate a chain using the core fetish


## Chains
Chains are lists of fractions. They can be used as strings, or just an
array of numbers. When printed as a string, each fraction is converted
into an ASCII code.

Chain literals are similar to C `char*` literals:

    "Hello World!\n"

But are escaped by octal only.  

Chain literals cannot be concatenated by placing them next to each
other, and multi-line chain literals cannot exist.

Chains are not null-terminated, but their literals are.


## Streams
Streams are treated like chains in Fetlang. The three stream builtin variables
are: stdout, stdin, and stderr. They are referred to by identifiers
as shown in [reference/core.md](reference/core.md)
