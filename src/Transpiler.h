#pragma once
#include "SyntaxTree.h"
#include "VariableCollection.h"

/*
 * This glass transforms an abstract syntax tree into the full C code output.
 * It does not handle compilation, linkage, or any other such nonsense
 */

class Transpiler{
	// The AST we received what was created by the parser
	SyntaxTree::RootNode tree;
	// Variables we received what was created by the parser
	VariableCollection variables;

	// Just transpile the token at a particular node
	// Don't do anything with its children (or anybody else's children, you
	// sick fuck)
	std::string transpileNode(const SyntaxTree::Node&);
	
public://public only for devel purposes
	// Just do the AST-traversing part of the transpiling process
	// Recursive
	std::string transpileBranch(SyntaxTree::Node&);

public:
	Transpiler(const SyntaxTree::RootNode& rootnode, const VariableCollection&
		vars_arg) : tree(rootnode), variables(vars_arg){}

	// Output the C source code
	// This includes the boiler plate code, etc
	std::string transpile();

};



