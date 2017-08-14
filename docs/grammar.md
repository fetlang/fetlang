## Grammar
There are three functional grammars, as well as a conditional grammar and bind
grammar (see control flow)  

Functional grammars are used to perform operations between operands. Each
operation has a left hand operand, and operator, and a right hand operand
(often implicit). The grammar defines how these are syntactically placed.
Sometimes the right hand operator will be on the left, while the left hand
operator will be on the right. A left hand operator must be a mutable value
(that is, a variable or pronoun)

The three functional grammars are: `make`, `have`, and `plain`

### Make Grammar:
Make grammar can follow these formats:
`make` <lho> <operator>
`make` <lho> <operator> <rho - mutable>
`make` <lho> <operator> <rho - chain literal>

When there is no right-hand operand given, an implicit value of "" is used

## Plain Grammar:
Plain grammar can follow these formats:
<operator> <lho>  
<operator> <lho> <rho - fraction literal> time/s
  
Plain grammar without a given rho has an implicit value of 1. When the given
value of the rho is not one, `times` must be used. Otherwise, `time` is used
for a value of 1.(which is not needed, since it is the implicit value, anyway)

## Have Grammar
Have grammar can follow this format
`have`<lho> <operator> <rho - mutable>



