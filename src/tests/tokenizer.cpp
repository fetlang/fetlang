#include "../thirdparty/catch.hpp"
#include "../Tokenizer.h"
using namespace std;

TEST_CASE("Tokenizer, in general, works as expected", "[Tokenizer]"){
	const std::string code =
"have a spank b\n"
"spank c\n"
"have Ada Lovelace (lovingly) spank Richard Stallman\n"
"if Ada Lovelace is Linus Torvalds\n"
"\tspank Linus Torvalds eight hundred AND fOrty six times\n"
"\tspank Richard Stallman\n"
"spank Ada Lovelace\n";

	Tokenizer tokenizer = Tokenizer(code);
	auto tokens = tokenizer.tokenize();
	std::vector<std::pair<std::string, Token::TokenCategory>>
		expected_values =
	{
		{"have",	Token::KEYPHRASE_TOKEN},
		{"a",	 	Token::IDENTIFIER_TOKEN},
		{"spank",	Token::KEYPHRASE_TOKEN},
		{"b",		Token::IDENTIFIER_TOKEN},
		{"spank",	Token::KEYPHRASE_TOKEN},
		{"c",		Token::IDENTIFIER_TOKEN},
		{"have",	Token::KEYPHRASE_TOKEN},
		{"ada lovelace",Token::IDENTIFIER_TOKEN},
		{"spank",	Token::KEYPHRASE_TOKEN},
		{"richard stallman", Token::IDENTIFIER_TOKEN},
		{"if",		Token::KEYPHRASE_TOKEN},
		{"ada lovelace",Token::IDENTIFIER_TOKEN},
		{"is",		Token::KEYPHRASE_TOKEN},
		{"linus torvalds", Token::IDENTIFIER_TOKEN},
		{"spank",	Token::KEYPHRASE_TOKEN},
		{"linus torvalds", Token::IDENTIFIER_TOKEN},
		{"eight hundred and forty six", Token::FRACTION_LITERAL_TOKEN},
		{"times",	Token::KEYPHRASE_TOKEN},
		{"spank",	Token::KEYPHRASE_TOKEN},
		{"richard stallman", Token::IDENTIFIER_TOKEN},
		{"spank",	Token::KEYPHRASE_TOKEN},
		{"ada lovelace",Token::IDENTIFIER_TOKEN},
	};

	for(unsigned int i=0; i<expected_values.size(); i++)
	{
		REQUIRE(expected_values[i].first == tokens[i].getValue());
		REQUIRE(expected_values[i].second == tokens[i].getCategory());
	}
}

TEST_CASE("Possesives", "[Tokenizer]"){	
	std::string code = "Bob's Burgers\nher face\ntheir face";
	Tokenizer tokenizer = Tokenizer(code);
	auto tokens = tokenizer.tokenize();
	REQUIRE(tokens[0].getValue() == "bob");
	REQUIRE(tokens[1].getValue() == "her");
	REQUIRE(tokens[2].getValue() == "their");
}

TEST_CASE("Loading fetishes", "[Tokenizer]"){	
	string code = "(I have a fetish for assertiveness)\nhave a assert dominance over b\n";
	Tokenizer tokenizer = Tokenizer(code);
	vector<Token> tokens;
	REQUIRE_NOTHROW(tokens = tokenizer.tokenize());
	REQUIRE(tokens[0].getValue() == "have");
	REQUIRE(tokens[1].getValue() == "a");
	REQUIRE(tokens[2].getValue() == "assert dominance over");
}

TEST_CASE("Indents", "[Tokenizer]"){
	string code =
"lick a\n"
"lick b\n"
"if a is a\n"
"\tif a is a\n"
"\t\tif a is a\n"
"\t\t\tlick a";
	Tokenizer tokenizer = Tokenizer(code);
	auto tokens = tokenizer.tokenize();


	auto line_indents = tokenizer.getLineIndents();
	REQUIRE(line_indents.size() == 6);
	REQUIRE(line_indents[0] == 0);
	REQUIRE(line_indents[1] == 0);
	REQUIRE(line_indents[2] == 0);
	REQUIRE(line_indents[3] == 1);
	REQUIRE(line_indents[4] == 2);
	REQUIRE(line_indents[5] == 3);
}

