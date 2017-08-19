# Fetishes
A fetish is a loadable module written in C that extends Fetlang. By default, a fetish called `core` automatically and contains the main language functionality.

## Loading Fetishes
Using the phrase `I have a fetish for` in a comment will load a fetish. Example:  
`(I have a fetish for assertiveness)`  
Will load the fetish `assertiveness`. Fetish loading takes place during tokenization, before any keyphrases are recognized, so it doesn't matter where you place the statement.

## Writing fetishes
You can create your own custom fetishes to exend Fetlang. A fetish is a directory structured as follows

    assertiveness // Directory with name of fetish
    	fetish.json // Fetish file - wraps the C code with Fetlang operators, conditional operators, and variables
    	unit.fet // A unit test written in Fetlang
	    include // public C headers directory
	        ...
    	source // C source and private C headers
    		...

### C code
The C headers and source contains whatever you want. The files in ./include should contain functions and the like you reference either from fetish.json or another fetish. To access another fetish's members, you can `#include "fetish_name/file_name"`

### Fetish.json
Every fetish must contain a fetish.json file. You can use fetishes/core/fetish.json as a good example.

Fields:  
`description`: A string description of the fetish. Used for documentation generation  
`operators`:  An array of objects describing a Fetlang operator  
`comparison_operators`: An array of objects describing a Fetlang comparison operator  
`builtins`: An array ob objects describing a Fetlang builtin variable  
`preloop_code` : Code that runs before the main do-while loop  
`postloop_code` : Cleanup code that runs after the main do-while loop  
