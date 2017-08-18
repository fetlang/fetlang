# Fetlang
Fetlang is a statically typed, procedural, esoteric programming language and
reference implementation. It is designed such that source code, at first
glance, might look like poorly written erotica.  

This is currently incomplete, but almost usable. It is not recommended to use
this for production code at this moment.

## Example
The following example outputs the arguments given to the executable:

    Make Betty moan
    Worship Carrie's feet
    
    Bind Amy to Saint Andrew's Cross
        Have Amy hogtie Betty
        If Amy is Carrie's bitch
            Make Slave scream Betty's name
            Make Betty moan


## Features
* Input/output with standard streams and files
* Statically typed - four types: fractions, chains, streams, references
* Gendered variables
* Access previously mentioned variables using pronouns
* Numbers represented internally as fractions instead of floating point
* Transpiles to C
* Case insensitive
* Confusing English-like syntax and unhelpful error messages
* Probably turing complete
* Extensible - just install your fetish in share/fetlang/fetishes

## Building
Requirements:
* meson
* ninja
* gcc/g++ or clang

Build Fetlang:  

    git clone https://github.com/Property404/fetlang
	cd fetlang
	meson src build
	cd build
	# Build and runs tests
	ninja test
	# Make sure it worked
	./fetlang ../examples/hello.fet && ./a.out

Install:  

    ninja install

## Documentaton
[Comments](docs/comments.md)  
[Control Flow](docs/control%20flow.md)  
[Fetish Reference](docs/reference.md)  
[Grammar](docs/grammar.md)  
[Types](docs/types.md)  
[Variables](docs/variables.md)  

## License
Fetlang is licensed under the BSDM (BSD, modified) license

