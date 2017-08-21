#include <sstream>
#include <algorithm>
#include <limits>
#include <iterator>
#include <deque>
#include <map>
#include <set>
#include "FractionParser.h"
#include "FetlangException.h"

typedef std::deque<std::string> WordList;

static const std::map<std::string, FractionInt> NUMBER_WORDS = {
{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9},
{"ten", 10}, {"eleven", 11}, {"twelve", 12}, {"thirteen", 13}, {"fourteen", 14}, {"fifteen", 15}, {"sixteen", 16},
{"seventeen", 17}, {"eighteen", 18}, {"nineteen", 19},
{"twenty", 20}, {"thirty", 30}, {"forty", 40}, {"fifty", 50}, {"sixty", 60}, {"seventy", 70}, {"eighty", 80}, {"ninety", 90},
{"hundred", 100},
{"thousand", 1000}, {"million", 1000000}, {"billion", 1000000000}, {"trillion", 1000000000000}, {"quadrillion", 1000000000000000},
{"quintillion", 1000000000000000000}
};

static const std::set<std::string> SPECIAL_WORDS = {"zero", "negative", "positive", "over"};

// Convert a -SINGLE- word to a number
static FractionInt wordToInteger(const std::string& word){
	auto word_pair = NUMBER_WORDS.find(word);
	if (word_pair == NUMBER_WORDS.end()){
		throw FetlangException(word + " is not a valid number");
	}
	return word_pair -> second;
}

// small functions to check what category a number is in
// number between 1-9 inclusive
static bool isOnesPlace(FractionInt i){return (i< 10 && i>0);}
static bool isOnesPlace(const std::string& w){
	return isOnesPlace(wordToInteger(w));
}
// number between 10-19 inclusive
static bool isTeen(FractionInt i){return (i>=10 && i<20);}
static bool isTeen(const std::string& w){
	return isTeen(wordToInteger(w));
}
// number between 20-90 inclusive, excluding those not divisible by 10(like 42)
static bool isTensPlace(FractionInt i){return ((i%10 == 0) && i>=10 && i<=90);}
static bool isTensPlace(const std::string& w){
	return isTensPlace(wordToInteger(w));
}
// Number that separates a triple (one thousand, a million, etc)
static bool isTripleSeparator(FractionInt i){return i>=1000 && (i%1000==0);}
static bool isTripleSeparator(const std::string& w){
	return isTripleSeparator(wordToInteger(w));
}

// Split string into word list
static WordList splitString(const std::string& the_string){
	std::istringstream stream(the_string);
	WordList word_list;
	copy(std::istream_iterator<std::string>(stream),
		std::istream_iterator<std::string>(),
		back_inserter(word_list));
	return word_list;
}
	
	
// Convert a triple to a number (triple is list of words representing a number with a max of three [decimal] digits)
static FractionInt tripleToInteger(WordList& triple){
	// valid forms
	/*
		(eight million)one hundred and forty six
		one hundred and two
		two
		twenty four
		two hundred and seven
		seven hundred and eighty two
		one hundred
		seventy
		and [any other triple] 

		"and" can be in two places: after the start, or after 100 (or both)
	*/		
	// Keep track of the last word uttered
	std::string previous_word = "";

	// Check for "and at the start"
	if(triple.size() > 0 && triple.front() == "and"){
		previous_word = triple.front();
		triple.pop_front();
	}


	FractionInt value = 0;
	bool hundred_can_appear = true;
	bool no_more_words = false;
	
	for(const std::string& word : triple){
		if(no_more_words){
			throw FetlangException("Triple is too long!");
		}
		// And is allowed exist after "hundred"
		if(word == "and"){
			if(previous_word != "hundred"){
				throw FetlangException("'and' is out of place in triple");
			}
		}else if(word == "hundred"){
			// Hundred can appear only once, after 1-9, if it is the second word (not including and)o
			if(hundred_can_appear && isOnesPlace(previous_word)){
				value *= 100;
				hundred_can_appear = false ;
			}else{
				throw FetlangException("'hundred' is out of place in triple");
			}
		}else if(isOnesPlace(word)){
			// A ones place number must only appear before 100, after 'and', or after 'twenty', 'thirty' etc
			// or by itself
			if(hundred_can_appear || (previous_word == "and" || isTensPlace(previous_word))){
				value += wordToInteger(word);
				// If hundred has already passed, no more words can follow this
				if(!hundred_can_appear){
					no_more_words = true;
				}
			}else{
				throw FetlangException("A ones-place number can only appear in a triple before 100, after 'and', or after a ten's place number");
			}
		}else if (isTeen(word)){
			// A teen is similar, but it can't appear after a ten's place word
			// so, only by itself or after an 'and'(which could be after 100, or not; it doesn't matter)
			if(hundred_can_appear || previous_word == "and"){	
				// hundred can't appear after a teen word
				hundred_can_appear = false;
				value += wordToInteger(word);
				// But this word must be the last word!
				no_more_words = true;
			}else{
				throw FetlangException("A 'ten', 'eleven', 'twelve', or 'x-teen' can only appear by itself, or after 'and' in triple");
			}
		}else if (isTensPlace(word)){
			// So a tens place word is exactly the same as the teen word
			// with the exception that a word can appear after it
			if(hundred_can_appear || previous_word == "and"){
				hundred_can_appear = false;
				value+= wordToInteger(word);
			}else{
				throw FetlangException("A ten's place number can only appear by itself, or after 'and', in triple");
			}
		}
		

		previous_word = word;
	}
	
	if(value==0){
		throw FetlangException("Triple is empty");
	}
	return value;
}

// Convert any list representing an integer value to its actual value(as an integer fraction, or infinity)
static Fraction numberListToBasicFraction(WordList& number){
	// Negative should only appear at the beginning 
	bool make_final_value_negative = false;
	if(number.size() > 0 && number.front() == "negative"){
		make_final_value_negative = true;
		number.pop_front();
	}	

	if(number.size() == 0){
		throw FetlangException("Number is empty");
	}

	// Allow for some esoteric values
	if(number.size() == 1){
		if(number.front() == "zero"){
			return Fraction(0);
		}else if(number.front() == "infinity"){
			return Fraction(1, 0);
		}
	}

	// Forbid an initial and
	if(number.front() == "and"){
		throw FetlangException("'And' is forbidden in this location");
	}
		

	// Make sure the separators  go in descending order
	// Set to max value because the initial value can be anything
	// (divisible by 1000, ofc)
	FractionInt previous_separator_value = std::numeric_limits<FractionInt>::max();
	// Iterate through
	// Until  you find a triple separator (1000, 1000000, etc), just keep processing as a triple
	// Then multiply by the separator value
	FractionInt final_value = 0;
	WordList triple_buffer;
	for(const std::string& word: number){
		if(word != "and" && isTripleSeparator(word)){
			const FractionInt triple_value = tripleToInteger(triple_buffer);
			const FractionInt separator_value = wordToInteger(word);
			if(separator_value >= previous_separator_value){
				throw FetlangException("Triple separator values must be in descending order with no repeats");
			}
			final_value += triple_value * separator_value;
			previous_separator_value = separator_value;
			triple_buffer.clear();
		}else{
			triple_buffer.push_back(word);
		}
	}
	// one last time
	if(!triple_buffer.empty()) final_value += tripleToInteger(triple_buffer);


	if(make_final_value_negative) final_value *= -1;
	return final_value;//Fraction(final_value);
}

// Actual namespace functions
Fraction FractionParser::stringToFraction(const std::string& fraction_string){
	WordList fraction_list = splitString(fraction_string);
	Fraction return_value(0,1);
	
	// Split into top and bottom, if "over" exist
	int switched_to_bottom = false; //heh heh
	WordList temp;
	for(const std::string& word : fraction_list){
		if(word != "over"){
			temp.push_back(word);	
		}else{
			if(switched_to_bottom){
				throw FetlangException("Over cannot appear twice in a fraction");
			}

			switched_to_bottom = true;
			return_value = numberListToBasicFraction(temp);
			temp.clear();
		}
	}
	if(switched_to_bottom){
		return_value /= numberListToBasicFraction(temp);
	}else{
		return_value = numberListToBasicFraction(temp);
	}

	return return_value;
}

bool FractionParser::startsFractionLiteral(const std::string& word){
	try{
		wordToInteger(word);
		return true;
	}catch(const std::exception& e){
		if(word == "negative" || word == "zero" || word == "infinity"){
			return true;
		}

		return false;
	}
}

bool FractionParser::partOfFractionLiteral(const std::string& word){
	return startsFractionLiteral(word) || word == "over" || word=="and";
}
