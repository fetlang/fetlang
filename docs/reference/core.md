# Core
This is the core fetish. It effectively defines the language. You do not need to manually include it.
## Operators
### spank
Subtract the RHO from the LHO  

Grammar: have, plain  
Examples:  
`Spank Linus nine times`  

`Have Richard spank Linus`  

C Code:  

    /* fraction/fraction overload */
    LHO=subtract_fractions(LHO, RHO)  

### worship
Multiply the LHO with the RHO  

Grammar: have, plain  
Examples:  
`Worship Amanda's feet`  

`Have Amanda worship Bruce's throbbing cock`  

C Code:  

    /* fraction/fraction overload */
    LHO=multiply_fractions(LHO, RHO)  

### flog
Divide the LHO by the RHO  

Grammar: have, plain  
Examples:  
`Flog Amanda`  

`Have Amanda flog Bruce`  

C Code:  

    /* fraction/fraction overload */
    LHO=divide_fractions(LHO, RHO)  

### lick
Add the RHO from the LHO  

Grammar: have, plain  
Examples:  
`Lick Linus's face nine times`  

`Have Richard lick Linus's tummy`  

C Code:  

    /* fraction/fraction overload */
    LHO=add_fractions(LHO, RHO)  

### tickle
Set the LHO to the remainder of the LHO divided by the RHO  

Grammar: have, plain  
Examples:  
`tickle Richard`  

`Have Richard tickle Linus`  

C Code:  

    /* fraction/fraction overload */
    LHO=modulus_fractions(LHO, RHO)  

### moan
Assign RHO to LHO  

Grammar: make  
C Code:  

    /* fraction/fraction overload */
    LHO=RHO  

    /* fraction/chain overload */
    LHO=chain_to_fraction(RHO)  

    /* chain/fraction overload */
    clear_chain(&LHO);append_fraction_to_chain(&LHO, RHO)  

    /* chain/chain overload */
    clear_chain(&LHO); append_chain_to_chain(&LHO, RHO)  

### scream
Assign RHO to LHO, with new line  

Grammar: make  
C Code:  

    /* chain/fraction overload */
    clear_chain(&LHO);append_fraction_to_chain(&LHO, RHO);append_flink_to_chain(&LHO, construct_fraction(10,1));  

    /* chain/chain overload */
    clear_chain(&LHO);append_chain_to_chain(&LHO, RHO);append_flink_to_chain(&LHO, construct_fraction(10,1));  

### torture
Read the next byte from RHO and place it into LHO  

Grammar: have  
Examples:  
`Have Mistress torture his cock`  

C Code:  

    /* fraction/stream overload */
    LHO = get_next_byte_of_stream(RHO)  

### tie up
Concat RHO to LHO  

Grammar: have  
C Code:  

    /* chain/fraction overload */
    append_fraction_to_chain(&LHO, RHO)  

    /* chain/chain overload */
    append_chain_to_chain(&LHO, RHO)  

### hogtie
Concat RHO as fraction to LHO  

Grammar: have  
C Code:  

    /* chain/fraction overload */
    append_flink_to_chain(&LHO, RHO)  

## Comparison Operators
### is
Return true if LHO==RHO, else return false  

C Code:  

    /* fraction/fraction overload */
    (compare_fractions(LHO, RHO)==0)  

    /* chain/chain overload */
    (compare_chains(LHO, RHO)==0)  

### is not
Return true if LHO!=RHO, else return false  

C Code:  

    /* fraction/fraction overload */
    (compare_fractions(LHO, RHO)!=0)  

    /* chain/chain overload */
    (compare_chains(LHO, RHO)!=0)  

### is submissive to
Return true if LHO<RHO, else return false  

C Code:  

    /* fraction/fraction overload */
    (compare_fractions(LHO, RHO)==-1)  

### is dominant towards
Return true if LHO>RHO, else return false  

C Code:  

    /* fraction/fraction overload */
    (compare_fractions(LHO, RHO)==1)  

## Builtins
### slave
Standard output  

Type: stream  
Gender: unassigned  
C Code: `stdout`  

### mistress
Standard input  

Type: stream  
Gender: female  
C Code: `stdin`  

### dungeon master
Standard error  

Type: stream  
Gender: unassigned  
C Code: `stderr`  

### saint andrew
Chain version of argv with arguments separated by `zero`, intended to be invoked as `Saint Andrew's Cross`  

Type: chain  
Gender: nonperson  
C Code: `argv_chain`  

