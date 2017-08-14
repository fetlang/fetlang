#pragma once
#include <vector>
#include <string>
#include <unordered_set>
#include "FetlangException.h"
#include "Token.h"

/* Pre-lexer class */
class Tokenizer {
	/* Split string into real basic tokens, words and quote onlys*/
	std::vector<Token> splitCode(const std::string&) const;

	/* Remove gag/ungag tokens and everything inbetween them */
	std::vector<Token> removeGags(const std::vector<Token>&) const;

	/* Merge by keyphrase */
	std::vector<Token> mergeTokens(const std::vector<Token>&) const;

	/* Return list of individual keywords (words that make up a keyphrase) */
	std::unordered_set<std::string> getAllKeywords() const;


	// Convert identifiers from possesive form into their true form
	std::vector<Token> removePossessions(const std::vector<Token>& tokens);
public:
	Tokenizer();

	/* Call private functions only - possibly minimal logic*/
	std::vector<Token> tokenize(const std::string&);
};

class TokenizerException : public FetlangException{
public:
	TokenizerException(const std::string& message) : FetlangException(message) {}
	TokenizerException(int line, const std::string& message) : FetlangException(line, message) {}
};
