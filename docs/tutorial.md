# Tutorial

## Installing Fetlang

Follow the directions in [README.md](../README.md)  

## Hello World Program

Assuming you've got Fetlang nice and installed, let's try it out.
Go to whatever directory you want(say `~/Documents`) and create a new file
titled `hello.fet`. Using your preferred text editor, add this code to the file:  

    Make slave scream "Hello! This is my first Fetlang program!"
    
Save it and run:

    $ fetlang hello.fet -o hello
    $ ./hello
    Hello! This is my first Fetlang program!
    
Well, wasn't that exciting! (Hint, if you get a compiler/linker error, try transpiling with `-s`. That will clear the compiled fetishes)  

So, what's going on here? Well, let's analyze it token by token. Try the command:
```shell
$ fetlang -t hello.fet # This shows the tokens
...
$ fetlang -T hello.fet # This shows the syntax tree
...
```

`make` is the [grammar](grammar.md) that we are using for this operation. This tells Fetlang that the next token
will be the left hand operand (i.e, the mutable value in the operation),
the token after that will be an operator, and a optional token after that will be a [chain](types.md) literal.  
`slave` is the Fetlang wrapper around the UNIX stdout. This is what we're using as our left hand operand  
`scream` is an operator from the [core](reference/core.md) fetish, i.e the included-by-default part of
Fetlang's standard library  
`"Hello! This is my first Fetlang program!"` is a chain literal, and the right hand operand of the operation

## Output

Output in Fetlang is tied to two [stream](types.md) builtin variables: `slave`
and `Dungeon Master`, which are wrappers for standard output and standard
error, respectfully.  

The most common operators for use with output streams are:  
`moan` - assign the right hand operand to the left hand operand  
`scream` - assign the right hand operand to the left hand operand, then add a new line  

An example:  
```
Make slave moan "There is not a newline after this colon:"
Make slave scream "But there is a newline after this one:"
```

## Math
Math in Fetlang is handled through [fractions](types.md). That is,
a numerator over a denominator. Fractions, like all types in Fetlang,
are declared implicitly.  

The most common operators for use with fractions are:  
`spank` - subtract the right hand operand from the left hand operand  
`lick` - add the right hand operand to the left hand operand  
`worship` - multiply the left hand operand with the right hand operand  
`flog` - divide the left hand operand by the right hand operand  

Example:
```
(This is a comment)

(Add 5 to Charlie [0+5 = 5])
Lick Charlie's left nipple five times
(Note that "Charlie's left nipple" is equivalent to "Charlie")

(print out "five\n")
Make slave scream Charlie's name

(Multiply Charlie times 3 [5*3 = 15])
Worship Charlie's cock three times

(print out "fifteen\n")
Make slave scream Charlie's name



(Add 1 to Ada [0+1 = 1])
Lick Ada's toes one time

(Add 2 to Euler [0+2 = 2])
Lick Euler's belly button two times

(Add Ada to Euler [2+1 = 3])
(Note that Euler is the LHO because we are using 'have' grammar)
Have Ada Lick Euler's throbbing cock

(print "one\n")
Make slave scream Ada's name

(print "three\n")
Make slave scream Euler's name
```

## Simple Cat Program

A cat program is one that repeats the user's input back to them. In Python:
```python
print(input())
```

In Fetlang, this is less trivial. We have to read each byte from standard input
and append that to our output as a chain. In pseudocode:

```C
char byte;
string output = "";
while(true)
{
	byte = fgetc(stdin);
	if (byte == '\n')
		break;
	output.append(byte);
}
print(output);
```

We can almost translate this one-for-one to Fetlang, with some small changes.
In Fetlang, we can't compare to a character or numeric literal, so we have to
store '\n' in a fraction as an ASCII code: `lick Trisha's toes ten times`.  

We also don't have any equivalent to `while(true)`, so we can use `until amy is
dominant towards alicia`. `Until` loops while a condition is false, and `amy is
dominant towards alicia` is always false, assuming we have not used any of
these two variables elsewhere.  

Why is it always false? `is dominant towards` is Fetlang's
version of "greater than" or ">". All fraction variables initiate to zero(and
these are fractions because there is no other overload for `is dominant
towards` other than `fraction/fraction`). Therefore, `Amy is dominant towards
Alicia` equates to `0>0` which is obviously false  

We know how to print out the output. Just `make slave moan` with what we want as an output as the right hand operand.

Alright, let's start converting
```
(Anything in parentheticals is a comment)
(Set Trisha to 10)
lick Trisha's toes ten times
(Set Clara to "". She will be the final output)
make Clara moan

(while true)
Until Amy is dominant towards Alicia
	(put the rest of the code here)

(print)
Make slave scream Clara's name
```

You may notice that we didn't convert `char byte;` to Fetlang. This is because
you do not need to explicitly declare variables. Rather, they are implicitly
declared when used in an operation.  

What else do we need to do? In the `until` loop, we need to get a byte from standard input, and, if that byte is a newline, break.  

We can get a byte from standard input by using the `torture` operator as so:  
`Have Mistress torture Brian`  

Where `Mistress` is the standard input. Since we are using the `have` grammar, `Mistress` is the right hand operand, while Brian is the left hand operand. This means that Mistress is affecting Brian.  

We can then check if the byte received (`Brian`) is 10(ASCII for a newline). If it is, we can break with `call safeword`  

Finally, we can append the byte to the output using the `hogtie` operator: 

```
(Anything in parentheticals is a comment)
(Set Trisha to 10)
lick Trisha's toes ten times
(Set Clara to "". She will be the final output)
make Clara moan

(while true)
Until Amy is dominant towards Alicia
	(Read a byte from standard input)
	Have Mistress torture Brian's cock

	(Break if newline)
	If Brian is Trisha's fucktoy
		call safeword

	(Append byte to output)
	Have Brian hogtie Clara

(print)
Make slave scream Clara's name
```  

And that's our cat program! If you want to clean it up a bit, you can remove the comments:  
```
lick Trisha's toes ten times
make Clara moan

Until Amy is dominant towards Alicia
	Have Mistress torture Brian's cock
	
	If Brian is Trisha's fucktoy
		call safeword

	Have Brian hogtie Clara
Make slave scream Clara's name
```
