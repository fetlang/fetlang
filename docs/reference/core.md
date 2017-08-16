# Core
This is the core fetish. It effectively defines the language. You do not need to manually include it.
## Operators
### spank
The `spank` operator subtracts the RHO from the LHO  

Examples:  
`Spank Linus nine times`  

`Have Richard spank Linus`  

C Code:  
fraction/fraction - `LHO=subtract_fractions(LHO, RHO)`  

### worship
The `worship` operator multiplies the LHO with the RHO  

Examples:  
`Worship Amanda's feet`  

`Have Amanda worship Bruce's throbbing cock`  

C Code:  
fraction/fraction - `LHO=multiply_fractions(LHO, RHO)`  

### flog
The `flog` operator divides the LHO with the RHO  

Examples:  
`Flog Amanda`  

`Have Amanda flog Bruce`  

C Code:  
fraction/fraction - `LHO=divide_fractions(LHO, RHO)`  

### lick
The `lick` operator adds the RHO from the LHO  

Examples:  
`Lick Linus's face nine times`  

`Have Richard lick Linus's tummy`  

C Code:  
fraction/fraction - `LHO=add_fractions(LHO, RHO)`  

### tickle
The `tickle` operator sets the LHO to the remainder of the LHO divided by the RHO  

Examples:  
`ticke Richard`  

`Have Richard tickle Linus`  

C Code:  
fraction/fraction - `LHO=modulus_fractions(LHO, RHO)`  

### moan
assign RHO to LHO  

C Code:  
fraction/fraction - `LHO=RHO`  
fraction/chain - `LHO=chain_to_fraction(RHO)`  
chain/fraction - `clear_chain(&LHO);append_fraction_to_chain(&LHO, RHO)`  
chain/chain - `clear_chain(&LHO); append_chain_to_chain(&LHO, RHO)`  

### scream
assign RHO to LHO, with new line  

C Code:  
chain/fraction - `clear_chain(&LHO);append_fraction_to_chain(&LHO, RHO);append_flink_to_chain(&LHO, construct_fraction(10,1));`  
chain/chain - `clear_chain(&LHO);append_chain_to_chain(&LHO, RHO);append_flink_to_chain(&LHO, construct_fraction(10,1));`  

### tie up
concat RHO to LHO  

C Code:  
chain/fraction - `append_fraction_to_chain(&LHO, RHO)`  
chain/chain - `append_chain_to_chain(&LHO, RHO)`  

### fist
Read a file to a chain, given a filename  

C Code:  
chain/chain - `read_file_to_chain(&LHO, RHO);`  

### obey
write a chain to file, given a filename  

C Code:  
chain/chain - `write_chain_to_file(LHO, RHO)`  

### to
C Code:  
reference/chain - `--this should never enter the C code--`  

## Comparison Operators
### is
Returns true if LHO==RHO, else returns false  

C Code:  
fraction/fraction - `(compare_fractions(LHO, RHO)==0)`  
chain/chain - `(compare_chains(LHO, RHO)==0)`  

### is not
Returns true if LHO!=RHO, else returns false  

C Code:  
fraction/fraction - `(compare_fractions(LHO, RHO)!=0)`  
chain/chain - `(compare_chains(LHO, RHO)!=0)`  

### is submissive to
Returns true if LHO<RHO, else returns false  

C Code:  
fraction/fraction - `(compare_fractions(LHO, RHO)==-1)`  

### is dominant towards
Returns true if LHO>RHO, else returns false  

C Code:  
fraction/fraction - `(compare_fractions(LHO, RHO)==1)`  

## Builtins
### slave
C Code:  
stdout  

### mistress
C Code:  
stdin  

### dungeon master
C Code:  
stderr  

