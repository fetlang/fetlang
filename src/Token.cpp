#include "Token.h"
#include "QuoteUtil.h"
#include "FetlangManager.h"

Token::Token(const std::string& original_string, int line){
	this->line = line;
	// Normalize original_string to this->value 
	this->value = "";
	// Make lowercase if not a quote
	if(original_string[0]!='"'){
		for(char c : original_string){
			this->value += tolower(c);
		}
	}else{
		this->value = QuoteUtil::requote(original_string);
	}
	this->setCategory(Token::UNSET_TOKEN);
}

Token::Token(){
	this->setCategory(Token::NULL_TOKEN);
}

void Token::checkNull(const std::string& msg) const{
	if(this->category == NULL_TOKEN){
		throw TokenException(std::string("Can't '")+msg+"' in a NULL token", *this);
	}
}

void Token::setCategory(const Token::TokenCategory category){
	this->category = category;
}

void Token::setValue(const std::string value){
	this->value = value;
}


Token::TokenCategory Token::getCategory() const{
	checkNull("getCategory");
	return this->category;
}

std::string Token::getValue() const{
	checkNull("getValue");
	return this->value;
}


int Token::getLine() const{
	return this->line;
}

bool Token::isNullToken() const {
	return (this->category == Token::NULL_TOKEN);
}
	

KeyphraseCategory Token::getKeyphraseCategory() const {
	checkNull("getKeyphraseCategory");
	return manager.getKeyphraseCategory(this->value);
}


std::ostream& operator<<(std::ostream &out, Token const &in){
	std::string token_cat = "{{!Unknown Token!}}";
	//std::string phrase_cat = "";

	switch(in.category){
		case Token::NULL_TOKEN: token_cat = "NULL_TOKEN";break;
		case Token::KEYPHRASE_TOKEN: token_cat = "KEYPHRASE_TOKEN";break;
		case Token::FRACTION_LITERAL_TOKEN: token_cat = "FRACTION_LITERAL_TOKEN";break;
		case Token::CHAIN_LITERAL_TOKEN: token_cat = "CHAIN_LITERAL_TOKEN";break;
		case Token::IDENTIFIER_TOKEN: token_cat = "IDENTIFIER_TOKEN";break;
		default: ;
	}
	out << "{[" << in.value << "], [" << token_cat <<"]}";
	return out;

}

void TokenException::display() const{
	displayLineAndMessage();
	std::cerr << "\t" << token << "\n";
}
