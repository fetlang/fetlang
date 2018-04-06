#include "../thirdparty/catch.hpp"
#include "../Parser.h"
#include "../Tokenizer.h"
#include "../FetlangManager.h"
#include <exception>
TEST_CASE("Parser Test 1 - verification that variables are correctly added, no pronouns or conditionals", "[Parser]"){
	const std::string code =
"(bloop)spank a\n"
"spank b nine times\n"
"have c spank d\n";

	// Tokenizing
	Tokenizer tokenizer(code);
	std::vector<Token> tokens;
	REQUIRE_NOTHROW(tokens = tokenizer.tokenize());

	// Intermediate - require that no token is a NULL token or an UNSET token
	for(const auto& token: tokens){
		REQUIRE_FALSE(token.getCategory() == Token::NULL_TOKEN);
		REQUIRE_FALSE(token.getCategory() == Token::UNSET_TOKEN);
	}
		

	// Parsing
	Parser parser(tokens, tokenizer.getLineIndents());
	REQUIRE_NOTHROW(parser.formTree());

	
	// Verification
	std::string identifiers_to_check[] = {"a","b","c","d"};
	for(const std::string& identifier: identifiers_to_check)
	{
		CAPTURE(identifier);
		CHECK(parser.getVariables().has(identifier));
	}
	
}

TEST_CASE("Parser Test 2 - verification that bullshit code is detected", "[Parser]"){
	std::vector<std::string> bullshit =
	{
		"if while until",
		"his her one",
		"spank",
		"spank spank",
		"spank spank spank",
		"what",
		"Turnt down for what",
		"Richard Stallman spank",
		"Have Linux spank",
		"Have Linus spank fives times",
		"times times",
		"if if",
	};
	for(const std::string& code : bullshit){
		try{
			Tokenizer tokenizer(code);
			std::vector<Token> tokens;
			try{
				tokens = tokenizer.tokenize();
			}catch(const FetlangException&){
				throw;
			}catch(const std::exception& e){
				FAIL(std::string("Tokenizer failed with: ")+e.what());
			}
			Parser parser(tokens, tokenizer.getLineIndents());
			try{
				parser.formTree();
			}catch(const FetlangException&){
				throw;
			}catch(const std::exception& e){
				FAIL(std::string("Parser.getTree() failed with: ")+e.what());
			}
		}catch(const FetlangException&){
			continue;
		}
		FAIL("Bullshit was not detected with Fetlang exception");
	}
}

TEST_CASE("Parser Test 3 - verification that pronouns are interpreted correctly", "[Parser]"){

	std::string code = "Spank Ada\n"
	"Have Richard spank her\n"
	"spank him";
	Tokenizer tokenizer(code);
	std::vector<Token> tokens;
	REQUIRE_NOTHROW(tokens = tokenizer.tokenize());
	Parser parser(tokens, tokenizer.getLineIndents());
	REQUIRE_NOTHROW(parser.formTree());
	auto vars = parser.getVariables();
	REQUIRE(vars.get("ada").getGender() == FEMALE_GENDER);
	REQUIRE(vars.get("ada").getType() == FRACTION_TYPE);
	REQUIRE(vars.get("richard").getGender() == MALE_GENDER);
	REQUIRE(vars.get("richard").getType() == FRACTION_TYPE);
}

TEST_CASE("Parser Test 3.1 - Elimination of reflexive pronoun bug", "[Parser]"){

	std::string code = "have register spank itself";
	Tokenizer tokenizer(code);
	std::vector<Token> tokens;
	REQUIRE_NOTHROW(tokens = tokenizer.tokenize());
	Parser parser(tokens, tokenizer.getLineIndents());
	REQUIRE_NOTHROW(parser.formTree());
	auto vars = parser.getVariables();
	REQUIRE(parser.getTree().getChild(0).getToken().getValue() == "spank");
	REQUIRE(parser.getTree().getChild(0).getChild(0).getToken().getValue() == "register");
	REQUIRE(parser.getTree().getChild(0).getChild(1).getToken().getValue() == "register");
	REQUIRE(vars.get("register").getType() == FRACTION_TYPE);
	REQUIRE(vars.get("register").getGender() == NONPERSON_GENDER);
}
TEST_CASE("Parser Test 3.2 - Elimination of reflexive pronoun bug", "[Parser]"){

	std::string code = "worship register\nlick button\nhave register spank itself";
	Tokenizer tokenizer(code);
	std::vector<Token> tokens;
	REQUIRE_NOTHROW(tokens = tokenizer.tokenize());
	Parser parser(tokens, tokenizer.getLineIndents());
	REQUIRE_NOTHROW(parser.formTree());
	auto vars = parser.getVariables();
	REQUIRE(parser.getTree().getChild(2).getToken().getValue() == "spank");
	REQUIRE(parser.getTree().getChild(2).getChild(0).getToken().getValue() == "register");
	REQUIRE(parser.getTree().getChild(2).getChild(1).getToken().getValue() == "register");
	REQUIRE(vars.get("register").getType() == FRACTION_TYPE);
	REQUIRE(vars.get("register").getGender() == NONPERSON_GENDER);
}
TEST_CASE("Parser Test 3.3 - Elimination of reflexive pronoun bug", "[Parser]"){

	std::string code = "worship register\nlick button\nmake register moan its own name";
	Tokenizer tokenizer(code);
	std::vector<Token> tokens;
	REQUIRE_NOTHROW(tokens = tokenizer.tokenize());
	Parser parser(tokens, tokenizer.getLineIndents());
	REQUIRE_NOTHROW(parser.formTree());
	auto vars = parser.getVariables();
	REQUIRE(parser.getTree().getChild(2).getToken().getValue() == "moan");
	REQUIRE(parser.getTree().getChild(2).getChild(0).getToken().getValue() == "register");
	REQUIRE(parser.getTree().getChild(2).getChild(1).getToken().getValue() == "register");
	REQUIRE(vars.get("register").getType() == FRACTION_TYPE);
	REQUIRE(vars.get("register").getGender() == NONPERSON_GENDER);
}

TEST_CASE("Parser Test 4 - Binding test"){
	std::string code = "bind alpha to beta\n"
						"\tspank Linus one time\n";

	Tokenizer tokenizer(code);
	std::vector<Token> tokens;
	REQUIRE_NOTHROW(tokens = tokenizer.tokenize());
	REQUIRE(tokens[0].getValue() == "bind");
	REQUIRE(tokens[0].getKeyphraseCategory() == CONTROL_KEYPHRASE);
	REQUIRE(tokens[1].getValue() == "alpha");
	REQUIRE(tokens[1].getCategory() == Token::IDENTIFIER_TOKEN);
	REQUIRE(tokens[2].getValue() == "to");
	REQUIRE(tokens[2].getKeyphraseCategory() == OPERATOR_KEYPHRASE);
	REQUIRE(tokens[3].getValue() == "beta");
	REQUIRE(tokens[4].getValue() == "spank");
	REQUIRE(tokens[5].getValue() == "linus");
	REQUIRE(tokens[6].getValue() == "one");
	REQUIRE(tokens[7].getValue() == "time");
	Parser parser(tokens, tokenizer.getLineIndents());
	REQUIRE_NOTHROW(parser.formTree());
	VariableCollection vars = parser.getVariables();
	SyntaxTree::RootNode tree = parser.getTree();

	REQUIRE(vars.get("alpha").getType() == REFERENCE_TYPE);
	REQUIRE(vars.get("beta").getType() == CHAIN_TYPE);

	REQUIRE(tree.getNumberOfChildren() == 1);
	SyntaxTree::Node bind_node = tree.getChild(0);
	SyntaxTree::Node to_node = bind_node.getChild(0);
	SyntaxTree::Node spank_node = bind_node.getChild(1);
	REQUIRE(bind_node.getToken().getValue() == "bind");
	REQUIRE(to_node.getToken().getValue() == "to");
	REQUIRE(to_node.getChild(0).getToken().getValue() == "alpha");
	REQUIRE(to_node.getChild(1).getToken().getValue() == "beta");
	REQUIRE(spank_node.getToken().getValue() == "spank");
	REQUIRE(spank_node.getChild(0).getToken().getValue() == "linus");
	REQUIRE(spank_node.getChild(1).getToken().getValue() == "one");

}

TEST_CASE("Parser Test 5 - yet another gender test", "[Parser]")
{
	std::string code = "Have Rufus spank Ada\nHave Linus Worship her feet";
	Tokenizer tokenizer(code);
	std::vector<Token> tokens;
	REQUIRE_NOTHROW(tokens = tokenizer.tokenize());
	Parser parser(tokens, tokenizer.getLineIndents());
	REQUIRE_NOTHROW(parser.formTree());
	auto vars = parser.getVariables();
	REQUIRE(vars.get("rufus").getGender() == UNASSIGNED_GENDER);
	REQUIRE(vars.get("ada").getGender() == FEMALE_GENDER);
	REQUIRE(vars.get("linus").getGender() == UNASSIGNED_GENDER);
}

