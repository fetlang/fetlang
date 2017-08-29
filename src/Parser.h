#pragma once
#include <vector>
#include "VariableCollection.h"
#include "SyntaxTree.h"
#include "Grammar.h"

/* This class uses the output from the lexer to create an
   Abstract Syntax Tree (AST) which is then passed to the 
   transpiler
 */

class Parser {
	// Tokens what was received as input
	std::vector<Token> tokens;

	std::vector<int> line_indents;

	inline int getLineIndent(int line){
		if(line<0 || static_cast<unsigned int>(line) >
				line_indents.size()){
			throw FetlangException("Invalid line number while getting indent level");
		}
		return line_indents.at(line-1);
	}

	// Where we currently are in tokens
	std::vector<Token>::iterator token_iterator;

	// The abstract syntax tree that will be eventually returned
	// through one of the getters
	SyntaxTree::RootNode tree;

	// Keep track of all variables in the user's program
	// This should also be 'returned'
	VariableCollection variables;

	// Searches n number of tokens, returns false if tokens.end() is found
	bool nextTokensAreAvailable(int next_tokens) const;

	// Transplace a token with a variable
	void transplaceTokenWithVariable(std::vector<Token>::iterator&, const Variable&);

	// Find the appropriate variable and replace the token with it
	void transplacePronounToken(std::vector<Token>::iterator& token);
	// Meant for the rightward identifier
	void transplaceSecondPronounToken(std::vector<Token>::iterator& token);

	// If the variable doesn't exist, create it
	// Okay, this technically doesn't transplace anything,
	// But I may be slightly drunk
	void transplaceIdentifierToken(std::vector<Token>::iterator&, FetType, const Operator&, bool, bool);

	// Return the KNOWN FetType of token
	// if unknown, return UNKNOWN_TYPE
	//
	// THIS DOES NOT GUESS/INFER SHIT
	FetType getFetTypeOfOperand(const Token& token);

	// Given a grammar, the leftward and rightward operands, an operator,
	// and a node. This will appropriately add the processed lho and rho
	// and operator to the node according to the given grammar("make",
	// "have", "plain");
	//
	// It is the caller's responsibility to find the leftward and rightward
	// (DIFFERENT FROM LHO AND RHO, which are lvalues and rvalues)
	//
	void parseOperation(const Grammar&, std::vector<Token>::iterator left, const Operator&, std::vector<Token>::iterator right, SyntaxTree::Node& node);

	// Create an AST branch from the tokens list
	// Recursive by nature
	// 
	// Before calling anything, it creates a new
	// child on the given Node, it DOES NOT edit
	// the token of the given Node
	// NOR does it create sibling nodes
	void formBranch(SyntaxTree::Node&);

public:
	Parser(std::vector<Token> tokens_arg, std::vector<int> line_indent_args) : tokens(tokens_arg), line_indents(line_indent_args){}

	// Calls fromBranch iteratively
	void formTree();

	// returns the root node as a tree structure
	inline SyntaxTree::RootNode getTree(){return tree;}

	// Returns the list of variables
	inline VariableCollection getVariables(){return variables;}
};



