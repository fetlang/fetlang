#include "../thirdparty/catch.hpp"
#include "../Tokenizer.h"

TEST_CASE("Tokenizer, in general, works as expected", "[Tokenizer]"){
	const std::string code =
"have a spank b\n"
"spank c\n"
"have Ada Lovelace (lovingly) spank Richard Stallman\n"
"if Ada Lovelace is Linus Torvalds\n"
"spank Linus Torvalds eight hundred AND fOrty six times\n"
"spank Richard Stallman\n"
"end if\n"
"spank Ada Lovelace\n";

	Tokenizer tokenizer = Tokenizer();
	auto tokens = tokenizer.tokenize(code);
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
		{"end if",	Token::KEYPHRASE_TOKEN},
		{"spank",	Token::KEYPHRASE_TOKEN},
		{"ada lovelace",Token::IDENTIFIER_TOKEN},
	};

	for(int i=0; i<expected_values.size(); i++)
	{
		REQUIRE(expected_values[i].first == tokens[i].getValue());
		REQUIRE(expected_values[i].second == tokens[i].getCategory());
	}
}

TEST_CASE("Possesives", "[Tokenizer]"){	
	std::string code = "Bob's Burgers\nher face\ntheir face";
	Tokenizer tokenizer = Tokenizer();
	auto tokens = tokenizer.tokenize(code);
	REQUIRE(tokens[0].getValue() == "bob");
	REQUIRE(tokens[1].getValue() == "her");
	REQUIRE(tokens[2].getValue() == "their");
}

