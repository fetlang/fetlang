#include "QuoteUtil.h"
#include <map>
#include <sstream>

static constexpr int MAX_OCTAL_STRING_SIZE = 3;
static const std::map<char, char> escapeMap= {
{'a', '\a'},
{'b', '\b'},
{'f', '\f'},
{'n', '\n'},
{'r', '\r'},
{'t', '\t'},
{'v', '\v'},
{'\\', '\\'},
{'\'', '\''},
{'\"', '"'},
{'?', '?'},
};

// Escape any character as Octal
static std::string escapeCharacterAsOctal(char c){
	char octal_string[5];
	octal_string[0] = '\\';
	octal_string[1] = '0' + ((c>>6)&7);
	octal_string[2] = '0' + ((c>>3)&7);
	octal_string[3] = '0' + (c&7);
	octal_string[4] = '\0';
	return std::string(octal_string);
}


/*inline static bool isHexCharacter(char c){
	return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f')
		|| (c >= 'A' && c <= 'F');
}*/

static bool isOctalCharacter(char c){
	return (c >= '0' && c <= '7');
}


static char unescapeOctal(std::string octal_sequence){
	char c = 0;
	for(unsigned int i = 0; i<octal_sequence.size(); i++){
		if(!isOctalCharacter(octal_sequence[i])){
			throw FetlangException("Not an octal character");
		}
		c += (octal_sequence[i] - '0') << (3*(octal_sequence.size() - i - 1));
	}
	return c;
}

// Return escape character if the character is
// not printable, or is a double quote or backslash
// (cause those two unescaped chars will fuck shit up)
// Also use some of the common escape sequences
// instead of the octal value every time
//
// Note that '\0' is actually just octal, so
// we give it '\000'
static std::string escapeIfNecessary(char c){
	if (isprint(c) && c != '"' && c != '\\'){
		std::string buffer = "";
		buffer += c;
		return buffer;
	}
	switch(c){
		case '\n':
			return "\\n";
		case '\t':
			return "\\t";
		case '\"':
			return "\\\"";
		default:
			return escapeCharacterAsOctal(c);
	}
}

inline static char unescape(char c){
	return escapeMap.at(c);
}


std::string QuoteUtil::quote(const std::string& sequence){
	std::string new_sequence = "\"";
	for(const char& c: sequence){
		new_sequence += escapeIfNecessary(c);
	}
	new_sequence += "\"";
	return new_sequence;
}

std::string QuoteUtil::unquote(const std::string& sequence){
	if(sequence.size() < 2 || sequence[0] != '"' || sequence.back() != '"'){
		throw FetlangException("String must be surrounded by double quotes(\") to unquote");
	}

	std::string new_sequence = "";
	
	for(unsigned int i = 1; ;i++){
		if(sequence[i] == '"'){
			if(i != sequence.size() - 1){
				throw FetlangException("Quote was prematurely ended");
			}
			break;
		// We hit an escape character
		}else if(sequence[i] == '\\'){
			i++;
			// Check for octal then parse
			if(isOctalCharacter(sequence[i])){
				std::string octal_string = "";
				while(isOctalCharacter(sequence[i])){
					octal_string += sequence[i];
					if(octal_string.size() == MAX_OCTAL_STRING_SIZE){
						break;
					}
					i++;
				}
				new_sequence += unescapeOctal(octal_string);
				i--;
				continue;
			}else{
				new_sequence += unescape(sequence[i]);
				continue;
			}
		}else if(i >= sequence.size()){
			throw FetlangException("Quote is raw and uncontained - it must be terminated");
		}
		new_sequence += sequence[i];
	}
	return new_sequence;
}
			
std::string QuoteUtil::requote(const std::string& sequence){
	return quote(unquote(sequence));
}
