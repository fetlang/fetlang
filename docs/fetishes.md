# Fetishes
A fetish is a loadable module written in C, C++ and/or Rust that extends
Fetlang. By default, a fetish called `core` loads automatically and contains
the main language functionality.

## Loading Fetishes
Using the phrase `I have a fetish for` in a [comment](comments.md) will load a fetish. Example:  
`(I have a fetish for assertiveness)`  
Will load the fetish `assertiveness`. Fetish loading takes place during
tokenization, before any keyphrases are recognized, so it doesn't matter where
you place the statement.

## Writing fetishes
You can create your own custom fetishes to extend Fetlang. A fetish is a directory structured as follows

    // Directory with name of fetish
    assertiveness 
        // Fetish file - wraps the C code with Fetlang operators, conditional operators, and variables
        fetish.json
        // A unit test written in Fetlang
        unit.fet
        // public C headers directory
        include
            ...
        // C/C++/Rust source and private headers
        source 
            ...

You can use a user-written fetish in your code by compiling your .fet file with `fetlang {options} your_file.fet -f directory_of_your_fetish`  

Remember that `directory_of_your_fetish` is the directory your fetish directory is located in

### C code
The C headers and source contains whatever you want. The files in `./include`
should contain functions and the like you reference either from `fetish.json`
or another fetish. To access another fetish's members, you can `#include
"fetish_name/file_name"`  

The C++ and Rust sources should export unmangled functions to be declared in
the C headers.

### Fetish.json
Every fetish must contain a fetish.json file. You can use
fetishes/core/fetish.json as a good example.

Fields:  
`description`: A string description of the fetish. Used for documentation generation  
`dependencies`: The libraries and fetishes the fetish depends on  
`operators`:  An array of objects describing a Fetlang operator  
`comparison_operators`: An array of objects describing a Fetlang comparison operator  
`builtins`: An array ob objects describing a Fetlang builtin variable  
`preloop_code` : Code that runs before the main do-while loop  
`postloop_code` : Cleanup code that runs after the main do-while loop  

## Fetish documentation
The documentation for each fetish can be seen [here](reference.md)
