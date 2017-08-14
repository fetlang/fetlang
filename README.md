# Fetlang
Fetlang is a typed, procedural, fetish-themed, esoteric language and reference
implementation. It is designed such that source code, at first glance, might
look like poorly written erotica.  

This is currently incomplete, but almost usable. It is not recommended to use
this for production code at this moment.

## Example
The following example outputs all numbers in the Fibonacci sequence under a
million:

    lick Bob's cock
    lick Duke's left nipple one million times
    
    while Ada is submissive to Duke
        make slave scream Ada's name
        Have Charlie spank himself
        Have Ada lick his tight little ass
        Have Bob lick Charlie's tight little ass, as well
        make Ada moan Bob's name
        make Bob moan Charlie's name
    more please


## Features
Case insensitive  
Numbers represented internally as fractions instead of floating point
Transpiles to C
Probably turing complete. Or not. I don't know  

## Building
Requirements:
* meson
* ninja
* gcc
* g++

Build Fetlang:  

    git clone https://github.com/Property404/fetlang
	cd fetlang
	meson src build
	cd build
	# Builds and runs tests
	ninja test
	# Make sure it worked
	./fetlang ../examples/hello.fet && ./a.out

Install:  

    ninja install

## Documentaton
[Comments](docs/comments.md)  
[Control Flow](docs/control%20flow.md)  
[Grammar](docs/grammar.md)  
[Types](docs/types.md)  
[Variables](docs/variables.md)  

## License
Fetlang is licensed under the BSDM (BSD, modified) license

