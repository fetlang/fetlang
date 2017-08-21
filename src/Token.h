#pragma once
#include <string>
#include <iostream>
#include "KeyphraseCategory.h"
#include "FetlangException.h"

class Token {
public:
	enum TokenCategory {NULL_TOKEN = 0, KEYPHRASE_TOKEN, FRACTION_LITERAL_TOKEN, CHAIN_LITERAL_TOKEN, IDENTIFIER_TOKEN, UNSET_TOKEN};

private:
	/* Category */
	TokenCategory category;

	/* Made lowercase, all extra shit removed, etc */
	std::string value;

	/* Line word/s was/were originally found on */
	int line;
	
	// Raise exception if token is null	
	void checkNull(const std::string& msg="get") const;
public:
	/* Constructors */
	Token(const std::string& original_string, int line);
	// This creates a "null token" - set TokenCategory to NULL_TOKEN;
	Token();

	/* Setters */
	void setCategory(const TokenCategory);
	void setValue(const std::string);
	// We want to be able to print this object out, don't we?
	friend std::ostream &operator<<(std::ostream &out, Token const &in);
	/* Getters*/
	TokenCategory getCategory() const;
	std::string getValue() const;
	int getLine() const;

	// If this is a keyphrase token, return the category
	// with keyphrase manager
	KeyphraseCategory getKeyphraseCategory() const;

	/* Check if token is a "null token"*/
	bool isNullToken() const;
};

class TokenException : public FetlangException{
	Token token;
public:
	TokenException(const std::string& msg) : FetlangException(msg){}
	TokenException(int line, const std::string& msg) : FetlangException(line, msg){};
	TokenException(const std::string& msg, const Token& t) : FetlangException(t.getLine(), msg){
		token = t;
	}
	inline Token getToken() const{return token;}

	void display() const override;
};
