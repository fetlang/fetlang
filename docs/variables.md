# Variables
## Tokenizing/Identifiers
Variables names are case insensitive. Characters that can be used in an identifier
can be, but is not limited to: alphanumeric, an underscore, a hyphen, or a
space may be used. Tokenization ends at a newline, a keyphrase, or the
start of a literal.

Identifiers expressing possession are the same as their possessor. For
example:

`Richard Stallman's sexy feet` is the same as `riCHard StallMAN`

## Types
The [type](types.md) of a variable is implied by the first operation it is in. If it
is in a situation in which it could either be a fraction or chain, it
will default to fraction.

Chain type variables are initiated to `""`, while fraction type variables
are initiated to `zero`

## Gender
Variables can be assigned one of four genders: male, female, neutral,
 and nonperson. Additionally, an N/A (not applicable) gender exists, but
 cannot be assigned to a variable by the programmer. No variable starts
 with a gender (that is, they start with `UNASSIGNED_GENDER`), but once a gender is
assigned, it cannot be changed.

Each gender is associated with a group of pronouns:  
Male - `HIM`/`HIMSELF`/`HIS`/`HIS OWN`  
Female - `HER`/`HERSELF`/`HER`/`HER OWN`  
Neutral - `THEY`/`THEMSELF`/`THEIR`/`THEIR OWN`  
Nonperson - `IT`/`ITSELF`/`ITS`/`ITS OWN`  

`HIS` and `HIS OWN` are the possessive versions of `HIM` and `HIMSELF`,
respectively. `HIMSELF` is reflexive. `HIM` is objective.

Male, female, and neutral are used for humanly named variables,
like `Sasha Grey`
Nonperson is used for object-ly named variables, like `violet wand`
N/A is used for non-nouns


## Pronouns
Using a pronoun to describe a variable will imply its gender if it does
not have one yet. Use of an objective pronoun will use the last variable
mentioned that is not in the left-sided operand (not LHO). Use of a
reflexive pronoun will use the variable used in the left-sided operand
(if it cannot, compilation will fail). Use of possessive pronouns act the
same way as possessive identifiers.

Examples:

Subtract `Richard Stallman`(male) from `Richard Stallman`:

    Have Richard Stallman spank himself

Subtract `Rufus Xavier Sarsaparilla` from `Ada Lovelace`
Multiply `Ada Lovelace`(female) by `Linus Torvalds`(no gender):

    Have Rufus Xavier Sarsaparilla spank Ada Lovelace
    Have Linus Torvalds worship her feet

Add `Guido Van Rossum`(male) to `Guido Van Rossum`

    Have Guido Van Rossum lick his own cock

You see, a pronoun was made to take the place of a noun, 'cause saying
all those nouns over and over can really wear you down!
