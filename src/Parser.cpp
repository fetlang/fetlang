#include <iostream>
#include <cassert>
#include "Parser.h"
using namespace SyntaxTree;
static bool tokenIsIdentifier(const Token& token){
	return token.getCategory() == Token::IDENTIFIER_TOKEN;
}
static bool tokenIsPronoun(const Token& token){
	return token.getCategory() == Token::KEYPHRASE_TOKEN &&
		token.getKeyphraseCategory() == PRONOUN_KEYPHRASE;
}

static bool tokenIsObjectivePronoun(const Token& token){
	return tokenIsPronoun(token) && manager.
		getPronoun(token.getValue()).isObjective();
}

static bool tokenIsReflexivePronoun(const Token& token){
	return tokenIsPronoun(token) && manager.
		getPronoun(token.getValue()).isReflexive();
}

static bool tokenIsOperator(const Token& token){
	return token.getCategory() == Token::KEYPHRASE_TOKEN &&
		token.getKeyphraseCategory() == OPERATOR_KEYPHRASE;
}

static bool tokenIsComparisonOperator(const Token& token){
	return token.getCategory() == Token::KEYPHRASE_TOKEN &&
		token.getKeyphraseCategory() == COMPARISON_OPERATOR_KEYPHRASE;
}

// Searches n number of tokens, returns false if tokens.end() is found
bool Parser::nextTokensAreAvailable(int next_tokens) const{
	for(auto k=token_iterator; k!= token_iterator + next_tokens + 1; k++){
		if(k == tokens.end()) return false;
	}
	return true;
}	

// Transplace a token with a variable
void Parser::transplaceTokenWithVariable(std::vector<Token>::iterator& token,
	const Variable& variable) {

	Token new_token(variable.getName(), token->getLine());
	new_token.setCategory(Token::IDENTIFIER_TOKEN);
	token = tokens.erase(token);
	token = tokens.insert(token, new_token);
}

// Find the appropriate variable and replace the token with it
// Meant for an leftward objective pronoun
void Parser::transplacePronounToken(std::vector<Token>::iterator& token){
	// Assert an appropriate variable exists
	if(!variables.hasLastOfGender(manager.
		getPronoun(token->getValue()).getGender())){
		throw TokenException("There is no appropriate variable that exists for this pronoun",
		*token);
	}

	// Okay, an appropriate variable does exists, so transplace the 
	// tokenward token with it
	Variable var = variables.getLastOfGender(manager.
		getPronoun(token->getValue()).getGender());
	transplaceTokenWithVariable(token, var);
}

// Find the appropriate variable and replace the token with it
// Meant for a rightward objective pronoun
void Parser::transplaceSecondPronounToken(std::vector<Token>::iterator& token){
	// Assert an appropriate variable exists
	if(!variables.hasLastOfGender(manager.
		getPronoun(token->getValue()).getGender())){
		throw TokenException("There is no appropriate variable that exists for this pronoun",
		*token);
	}

	// Okay, an appropriate variable does exists, so transplace the 
	// tokenward token with it
	Variable var = variables.getLastOfGenderExcludingLast(manager.
		getPronoun(token->getValue()).getGender());
	transplaceTokenWithVariable(token, var);
}

// If the variable doesn't exist, create it
// Okay, this technically doesn't transplace anything,
// But I may be slightly drunk
void Parser::transplaceIdentifierToken(std::vector<Token>::iterator& token,
	FetType other_type, const Operator& op, bool isRightward, bool isReversed){

	// Check if the variable does not exists
	if(!variables.has(token->getValue())){
		// Does not, so we have to create and add one
		FetType actual_type;
		if(other_type == UNKNOWN_TYPE){
			if (isRightward){
				throw TokenException("Can't infer rightward operand without context - what are you, crazy? The leftward operand should have been guessed already",
					*token);
			}
			if(isReversed){
				actual_type = op.inferRightWithoutContext();
			}else{
				actual_type = op.inferLeftWithoutContext();
			}
		}else{
			bool isActuallyRight = isRightward;
			if(isReversed) isActuallyRight = !isActuallyRight;
			actual_type = isActuallyRight?
					op.inferRightByLeft(other_type):
					op.inferLeftByRight(other_type);
		}
		Variable var(token->getValue(), actual_type);
		variables.add(var);
	}
	// Note: We don't need to transplace
	// BECAUSE, if we transplace, we would
	// effectively replacing it with a copy of
	// itself
}

// Return the KNOWN FetType of token
// if unknown, return UNKNOWN_TYPE
//
// THIS DOES NOT GUESS/INFER SHIT
FetType Parser::getFetTypeOfOperand(const Token& token){
	// Being a reflexive pronoun or unknown identifier means
	// that we don't know the type, and that it depends on the
	// operator and other operand
	if(tokenIsReflexivePronoun(token)){return UNKNOWN_TYPE;}
	if(token.getCategory() == Token::IDENTIFIER_TOKEN &&
		!variables.has(token.getValue())){return UNKNOWN_TYPE;}

	// Literals we know very easily
	if(token.getCategory() == Token::CHAIN_LITERAL_TOKEN){return CHAIN_TYPE;}
	if(token.getCategory() == Token::FRACTION_LITERAL_TOKEN){return FRACTION_TYPE;}

	// Variables we also know fairly easily
	if(token.getCategory() == Token::IDENTIFIER_TOKEN &&
		variables.has(token.getValue())){

		Variable var = variables.get(token.getValue());
		return var.getType();
	}

	// PRESUMABLY, the other operand's type hasn't been
	// figured out yet, so we don't have to do the "second"
	if(tokenIsObjectivePronoun(token)){
		Variable var = variables.getLastAdded();
		return var.getType();
	}

	// Well, fuck, what is this thing
	throw TokenException("illegal operand", token);
}

void Parser::parseOperation(const Grammar& grammar, std::vector<Token>::iterator left, const Operator& op, std::vector<Token>::iterator right, SyntaxTree::Node& node){

	// Check if we can get rightward type
	FetType rightward_type = getFetTypeOfOperand(*right);
	
	// Check if operator actually has the given grammar
	if(!op.hasGrammar(grammar.getName())){
		throw FetlangException(std::string("'"+op.getName()+ "' operator cannot be used in ")+grammar.getName()+" grammar");
	}

	// Parse/transplace leftward token
	if(tokenIsObjectivePronoun(*left)){
		// Is objective pronoun
		// Assert grammar allows objective pronouns
		if(!grammar.allowsLeftPronoun()){
			throw TokenException(grammar.getName()+
				" grammar does not allow leftward pronouns", *left);
		}

		// And replace with appropriate variable
		transplacePronounToken(left);

	}else if(left->getCategory() == Token::IDENTIFIER_TOKEN){
		// Is an identifier
		// Assert grammar allows identifiers
		if(!grammar.allowsLeftIdentifier()){
			throw TokenException(grammar.getName()+
				" grammar does not allow leftward identifiers", *left);
		}
		// Replace with variable IF NECESSARY
		transplaceIdentifierToken(left, rightward_type, op, false, grammar.isReversed());
	}else{
		throw TokenException("Illegal leftward operand", *left);
	}

	// Have to access for future ref
	variables.access(left->getValue());

	// Parse/transplace rightward token
	if(tokenIsObjectivePronoun(*right)){
		// Is objective pronoun
		// Assert grammar allows objective pronouns
		if(!grammar.allowsRightPronoun()){
			throw TokenException(grammar.getName()+
				" grammar does not allow rightward pronouns", *right);
		}

		// And replace with appropriate variable
		transplaceSecondPronounToken(right);

	}else if(tokenIsReflexivePronoun(*right)){
		//Is a reflexive pronoun
		// Assert grammar allows such a thing
		if(!grammar.allowsRightReflexivePronoun()){
			throw TokenException(grammar.getName()+
				"grammar does not allow rightward reflexive pronouns", *right);
		}
		// Same old
		Variable& var = variables.getLastAccessed();
		var.setGender(
				manager.getPronoun(right->getValue()).getGender());
		transplaceTokenWithVariable(right, var);

	}else if(right->getCategory() == Token::IDENTIFIER_TOKEN){
		// Is an identifier
		// Assert grammar allows identifiers
		if(!grammar.allowsRightIdentifier()){
			throw TokenException(grammar.getName()+
				" grammar does not allow rightward identifiers", *right);
		}
		// Replace with variable IF NECESSARY
		transplaceIdentifierToken(right, getFetTypeOfOperand(*left), op, true, grammar.isReversed());

	}else if(right->getCategory() == Token::CHAIN_LITERAL_TOKEN){
		// Is a chain literal
		// Assert grammar allows this
		if(!grammar.allowsRightChainLiteral()){
			throw TokenException(grammar.getName()+
				" grammar does not allow rightward chain literals", *right);
		}
		/* No need to replace! :D */

	}else if(right->getCategory() == Token::FRACTION_LITERAL_TOKEN){
		// Is a fraction literal
		// Assert grammar allows this
		if(!grammar.allowsRightFractionLiteral()){
			throw TokenException(grammar.getName()+
				" grammar does not allow rightward fraction literals", *right);
		}
		/* No need to replace! :D */
	}else{
		throw TokenException(right->getValue()+ "- Illegal rightward operand", *right);
	}

	if(right->getCategory() == Token::IDENTIFIER_TOKEN){
		variables.access(right->getValue());
	}

	// Actually add the tokens as nodes
	Token operator_token(op.getName(), left->getLine());
	operator_token.setCategory(Token::KEYPHRASE_TOKEN);
	Node& operator_node = node.addChild(operator_token);
	if(grammar.isReversed()){
		operator_node.addChild(*right);
		operator_node.addChild(*left);
	}else{
		operator_node.addChild(*left);
		operator_node.addChild(*right);
	}
}



void Parser::formBranch(Node& node){
	switch(token_iterator->getCategory()){
	case Token::KEYPHRASE_TOKEN:
		switch(token_iterator->getKeyphraseCategory()){
		case CONTROL_KEYPHRASE:
		{
			if(token_iterator->getValue() == "call safeword")
			{
				// This is a 1-1 translation with break, so we don't need to do
				// anything special other than just add the token as a node
				node.addChild(*token_iterator);
				token_iterator++;
				return;
			}
			if(token_iterator->getValue() == "bind"){
				// Bind syntax:
				// bind <lho> to <rho>
				// 	...
				//	...

				int indent_level = getLineIndent(token_iterator->getLine());

				// Make sure we got enough to do our thing
				// lho+to+rho+more please = 4
				if(!nextTokensAreAvailable(4)){
					throw TokenException("`bind` expects to be followed by at "
						"least four tokens", *token_iterator);
				}

				// Need the `bind`
				Node& bind_node = node.addChild(*token_iterator);
				token_iterator++;

				// Assert the lho is of the right type
				if(!(tokenIsIdentifier(*token_iterator) || tokenIsObjectivePronoun(*token_iterator))){
					throw TokenException("`bind` expects to be followed by "
						"objective pronoun or identifier", *token_iterator);
				}
				auto lho = token_iterator;
				token_iterator++;

				// Assert 'to' exists
				if(token_iterator->getValue() != "to"){
					throw TokenException("Expected `to` after the LHO after bind", *token_iterator);
				}
				Operator op = manager.getOperator(token_iterator->getValue());
				token_iterator++;

				// Assert the rho is objective pronoun, identifier, or chain literal
				if(!(tokenIsIdentifier(*token_iterator) ||
					tokenIsObjectivePronoun(*token_iterator) ||
						token_iterator->getCategory() ==
							Token::CHAIN_LITERAL_TOKEN)){
					throw TokenException("Expected an objective pronoun, "
						"identifier, or chain literal as the RHO for the `bind`"
							" command");
				}
				auto rho = token_iterator;
				token_iterator++;

				// Add those three nodes
				Grammar bind_grammar("bind");
				bind_grammar.addAllowedLeftwardOperands({Grammar::IDENTIFIER, Grammar::PRONOUN}); 
				bind_grammar.addAllowedRightwardOperands({Grammar::IDENTIFIER, Grammar::PRONOUN, Grammar::CHAIN_LITERAL}); 
				parseOperation(bind_grammar, lho, op, rho, bind_node);

				// BUT we also have to add the other children, at least until
				// we reach the same level of indent
				while(token_iterator != tokens.end() && indent_level < getLineIndent(token_iterator->getLine())){
					formBranch(bind_node);
				}

				return;

			
				
			}else if(token_iterator->getValue() == "if" || token_iterator->getValue() == "while"
				|| token_iterator->getValue() == "until"){
				// If/while/until syntax:
				//	if/while/until <lho> <comparison operator> <rho>
				//		...
				//		...
				// + optional "otherwise"
				
				// We have to know exactly what we're doing
				// For, like, error messages
				std::string controller = token_iterator->getValue();

				int indent_level = getLineIndent(token_iterator->getLine());

				// Make sure we hve enough to do our thing
				//	lho+operator+rho+ending statement = 4
				if(!nextTokensAreAvailable(4)){
					throw TokenException("`"+controller+
						"` expects to be followed by at least four tokens", *token_iterator);
				}

				// Make our if/while/until node
				Node& conditional_node = node.addChild(*token_iterator);
				
				token_iterator++;

				// Get lho (must be identifier)
				if(token_iterator->getCategory() != Token::IDENTIFIER_TOKEN){
					throw TokenException("Expected identifier as lho in comparison operation", *token_iterator);
				}
				auto lho = token_iterator;
				token_iterator++;

				// Get the comparison operator
				if(!tokenIsComparisonOperator(*token_iterator)){
					throw TokenException("Expected comparison operator in comparison operation", *token_iterator);
				}
				auto comparison_operator = manager.
					getComparisonOperator(token_iterator->getValue());
				token_iterator++;

				// Get rho 
				if(token_iterator->getCategory() != Token::IDENTIFIER_TOKEN
				&& !tokenIsPronoun(*token_iterator)){
					throw TokenException("Expected identifier or pronoun as rho in comparison operation", *token_iterator);
				}
				auto rho = token_iterator;
				token_iterator++;

				// Add comparison operator and its children
				Grammar comparison_grammar("comparison");
				comparison_grammar.addAllowedLeftwardOperands({Grammar::IDENTIFIER});
				comparison_grammar.addAllowedRightwardOperands({Grammar::IDENTIFIER});
				comparison_grammar.addAllowedRightwardOperands({Grammar::PRONOUN});
				comparison_grammar.addAllowedRightwardOperands({Grammar::REFLEXIVE_PRONOUN});
				parseOperation(comparison_grammar, lho, comparison_operator, rho, conditional_node);

				// BUT we also have to add the other children, at least until
				// we reach the same level of indent
				while(token_iterator != tokens.end() && indent_level < getLineIndent(token_iterator->getLine())){
					formBranch(conditional_node);
				}

				// 'else'/'otherwise' statement after if
				if(token_iterator != tokens.end()
					&& token_iterator->getValue() == "otherwise"
						&& indent_level == getLineIndent(token_iterator->getLine())){

					if(controller != "if"){
						throw TokenException("Can only use `otherwise` after an `if` statement", *token_iterator);
					}
					Node& otherwise_node = node.addChild(*token_iterator);
					token_iterator++;
					// Add all the otherwise'd children
					while(token_iterator != tokens.end() && indent_level < getLineIndent(token_iterator->getLine())){
						formBranch(otherwise_node);
					}
				}
				return;
			}else if(token_iterator->getValue() == "have") {
				// This is a have grammar operation
				// It can take this form only:
				//	have <rho> <operator> <lho>
				//	Notice how this is reversed

				// Make sure we have the next three tokens to work with
				if(!nextTokensAreAvailable(3)){
					throw TokenException("`Have` grammar expects to be followed by three tokens");
				}
				
				// Define our grammar
				Grammar have_grammar("have");
				have_grammar.setReversed(true);
				have_grammar.addAllowedLeftwardOperands({
					Grammar::PRONOUN,
					Grammar::IDENTIFIER
				});
				have_grammar.addAllowedRightwardOperands({
					Grammar::PRONOUN,
					Grammar::IDENTIFIER,
					Grammar::REFLEXIVE_PRONOUN
				});
			
				// Have token
				token_iterator++;
				// rho
				auto rho = token_iterator;
				token_iterator++;
				// operator
				auto op = manager.getOperator(token_iterator->getValue());
				token_iterator++;
				// lho
				auto lho = token_iterator;
				token_iterator++;

				// Actually process this stupid operation
				parseOperation(have_grammar, rho, op, lho, node);

				// And DONE
				return;
			}else if(token_iterator->getValue() == "make") {
				// This is a make grammar operation
				// It can take the following forms:
				//	make <lho> <operator> <rho>
				//	make <lho> <operator>
				//	make <lho> <operator> <chain literal>

				// Make sure we have the next two tokens to work with
				if(!nextTokensAreAvailable(2)){
					throw TokenException("`Make` grammar expects to be followed by two tokens");
				}
				
				// Define our grammar
				Grammar make_grammar("make");
				make_grammar.addAllowedLeftwardOperands({
					Grammar::PRONOUN,
					Grammar::IDENTIFIER
				});
				make_grammar.addAllowedRightwardOperands({
					Grammar::PRONOUN,
					Grammar::IDENTIFIER,
					Grammar::REFLEXIVE_PRONOUN,
					Grammar::CHAIN_LITERAL,
				});
			
				// Left-hand operand
				token_iterator++;
				std::vector<Token>::iterator lho = token_iterator;
				token_iterator++;

				// operator token
				if(!tokenIsOperator(*token_iterator)){
					throw TokenException("Expected operator here", *token_iterator);
				}
				Operator op = manager.getOperator(token_iterator->getValue());
				token_iterator++;

				// Right-hand operator
				std::vector<Token>::iterator rho;
				// Container to put the RHO if we make it up
				std::vector<Token> rho_container;
				// Check if there's a given RHO
				if(token_iterator != tokens.end() &&
					(token_iterator->getCategory() == Token::CHAIN_LITERAL_TOKEN ||
						token_iterator->getCategory() == Token::IDENTIFIER_TOKEN ||
							tokenIsPronoun(*token_iterator))){
					rho = token_iterator;
					token_iterator+=1;
				}else{
					// Just make it up lol
					Token rho_token("\"\"", lho->getLine());
					rho_token.setCategory(Token::CHAIN_LITERAL_TOKEN);

					// And contain it
					rho_container.push_back(rho_token);
					rho = rho_container.begin();

				}

				// Actually process this stupid operation
				parseOperation(make_grammar, lho, op, rho, node);

				// And DONE
				return;
			}else{
				throw TokenException("Parser does not know what to do with keyphrase `"
					+token_iterator->getValue()+"`",*token_iterator);
			}
		}
		case OPERATOR_KEYPHRASE:
		{
			// This is a plain grammar operation
			// It can take these forms:
				//<operator> <lho>
				//<operator> <lho> <fraction literal> times
					// Note that <lho> can be a pronoun:
					// Spank him five times
			// With either the fraction literal becoming the RHO
			// OR with a default RHO

			if(!nextTokensAreAvailable(1)){
				throw TokenException("Plain grammar expects two tokens", *token_iterator);
			}

			// Define our grammar
			Grammar plain_grammar("plain");
			plain_grammar.addAllowedLeftwardOperands({
				Grammar::PRONOUN,
				Grammar::IDENTIFIER
			});
			plain_grammar.addAllowedRightwardOperands({
				Grammar::FRACTION_LITERAL
			});
		
			// operator token
			Operator operator_token = manager.getOperator(token_iterator->getValue());
			token_iterator++;

			// Left-hand operand
			std::vector<Token>::iterator lho = token_iterator;
			token_iterator++;

			std::vector<Token>::iterator rho;
			// Container to put the RHO if we make it up
			std::vector<Token> rho_container;
			// Check if there's a given RHO
			if(token_iterator != tokens.end() && token_iterator->getCategory() == Token::FRACTION_LITERAL_TOKEN){
				// Make some assertions about the format of the grammar
				if((token_iterator+1) != tokens.end()){
					if(token_iterator->getValue() == "one"){
						if((token_iterator+1)->getValue() != "time"){
							throw TokenException("Expected 'time' after fraction literal 'one' in plain grammar", *(token_iterator+1));
						}
					}else if((token_iterator+1)->getValue() != "times"){
						throw TokenException("Expected 'times' after fraction literal here", *(token_iterator+1));
					}
				}else{
					throw TokenException("Expected 'time' or 'times' after fraction literal but there are no more tokens left",
						*token_iterator);
				}

				// Now we can actually get the literal in peace
				rho = token_iterator;
				token_iterator+=2;
			}else{
				// Just make it up lol
				Token rho_token("one", lho->getLine());
				rho_token.setCategory(Token::FRACTION_LITERAL_TOKEN);

				// And contain it
				rho_container.push_back(rho_token);
				rho = rho_container.begin();

			}

			// Actually process this stupid operation
			parseOperation(plain_grammar, lho, operator_token, rho, node);

			// And DONE
			return;
		}

		default:
			throw TokenException("Parser isn't sure how to deal with this type of keyword at this point in time",
				*token_iterator);
		}
		break;
	default:
		throw TokenException("Parser isn't sure how to deal with this type of token at the top level", *token_iterator);
	}
}

void Parser::formTree()
{
	// First load builtins
	for(const BuiltinVariable& var : manager.getBuiltins()){
		variables.add(var);
	}

	// Then form all of the bottom branches
	token_iterator = tokens.begin();
	while(token_iterator != tokens.end()){
		formBranch(tree);
	}
}

