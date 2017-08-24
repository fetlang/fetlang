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
    
Well, wasn't that exciting! (Hint, if you get a compiler/linker error, try transpiling with `-s`. That will clear the fetish object cache)  

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
