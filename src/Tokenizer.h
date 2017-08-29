#pragma once
#include <vector>
#include <string>
#include <unordered_set>
#include "FetlangException.h"
#include "Token.h"

/* Pre-lexer class */
class Tokenizer {
	/* Actual list of tokens */
	std::vector<Token> actual_tokens;

	/* Check if we've tokenized yet */
	bool have_tokenized;


	/*  List of the indent level per line */
	std::vector<int> line_indents;

	std::string code;

	/* Split string into real basic tokens, words and quote only*/
	std::vector<Token> splitCode();

	/* Remove gag/ungag tokens and everything in between them */
	std::vector<Token> removeGags(const std::vector<Token>&) const;

	/* Merge by keyphrase */
	std::vector<Token> mergeTokens(const std::vector<Token>&) const;

	/* Return list of individual keywords (words that make up a keyphrase) */
	std::unordered_set<std::string> getAllKeywords() const;

	// Convert identifiers from possessive form into their true form
	std::vector<Token> removePossessions(const std::vector<Token>& tokens);
public:
	Tokenizer(const std::string& code);
	
	std::vector<Token> tokenize();

	/* Get tokens */
	std::vector<Token> getTokens() const;

	/* Get line indents */
	std::vector<int> getLineIndents() const;
};
