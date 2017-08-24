# Tutorial

## Installing Fetlang

Follow the directions in [README.md](../README.md)  

## Hello World

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

    $ fetlang -t hello.fet # This shows the tokens
    ...
    $ fetlang -T hello.fet # This shows the syntax tree
    ...

`make` is the [grammar](grammar.md) that we are using for this operation. This tells Fetlang that the next token
will be the left hand operand (i.e, the mutable value in the operation),
the token after that will be an operator, and a optional token after that will be a [chain](types.md) literal.  
`slave` is the Fetlang wrapper around the UNIX stdout. This is what we're using as our left hand operand  
`scream` is an operator from the [core](reference/core.md) fetish, i.e the included-by-default part of
Fetlang's standard library  
`"Hello! This is my first Fetlang program!"` is a chain literal, and the right hand operand of the operation

## Simple Cat Program

A cat program is one that repeats the user's input back to them. In Python:
```python
print(input())
```

In Fetlang, this is less trivial. We have to read each byte from standard input
and append that to our output as a chain. In psuedocode:

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
store '\n' in a fraction as an ASCII code: `lick Trisha's toes ten times`. The
`'s toes` part of the code isn't necessary because anything after `'` in an
identifier is ignored  

We also don't have any equivalent to `while(true)`, so we can use `until amy is
dominant towards alicia`. `Until` loops while a condition is false, and `amy is
dominant towards alicia` is always false, assuming we have not used any of
these two variables elsewhere. Why is this? `is dominant towards` is Fetlang's
version of "greater than" or ">". All fraction variables initiate to zero(and
these are fractions because there is no other overload for `is dominant
towards` other than `fraction/fraction`). Therefore, `Amy is dominant towards
Alicia` equates to `0>0` which is obviously false

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
```

You may notice that we didn't convert `char byte;` to Fetlang. This is because
you do not need to explicitly declare variables. Rather, they are implicitly
declared when used in an operation.
