# Grammar
There are three functional grammars, as well as a conditional grammar and bind
grammar (see [control flow](control%20flow.md))  

Functional grammars are used to perform operations between operands. Each
operation has a left hand operand, and operator, and a right hand operand
(often implicit). The grammar defines how these are syntactically placed.
Sometimes the right hand operator will be on the left, while the left hand
operator will be on the right. A left hand operator must be a mutable value
(that is, a variable or pronoun)

The three functional grammars are: `make`, `have`, and `plain`

## Make Grammar:
Make grammar can follow these formats:  
`make` \<lho - mutable\> \<operator\>  
`make` \<lho - mutable\> \<operator\> \<rho - mutable\>  
`make` \<lho - mutable\> \<operator\> \<rho - chain literal\>  

When there is no right-hand operand given, an implicit value of `""` is used

Examples:  

    (Assign an empty chain literal plus a newline to Linus)
    Make Linus scream
    
	(Pipe Linus's value to stdout)
	Make slave moan his name

	(Assign "If I could just interject" to Richard)
	Make Richard moan "If I could just interject"

## Plain Grammar:
Plain grammar can follow these formats:  
\<operator\> \<lho - mutable\>   
\<operator\> \<lho - mutable\> \<rho - fraction literal\> time/s  
  
Plain grammar without a given rho has an implicit value of `one`. When the given
value of the rho is not one, `times` must be used. Otherwise, `time` is used
for a value of `one`, which is not actually needed, since it is the implicit
value, anyway  

Examples:  

    (Subtract one from Luna)
	Spank Luna

	(Also subtract one from Luna)
	Spank Luna one time

	(And subtract 1023 from Luna)
    Spank Luna one thousand and twenty three times

## Have Grammar
Have grammar can only follow this format  
`have` \<rho - mutable\> \<operator\> \<lho - mutable\>  

Example:  

	(Subtract Harry from Gina)
    Have Harry spank Gina

