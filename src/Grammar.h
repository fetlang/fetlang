#pragma once
#include <vector>
#include <string>
#include <set>

/* This class is used to defined the rules for a particular grammar. This does
 * not define how a grammar is organized in source code, as that is the
 * parser's job, but how the grammar uses its operands.
 *
 * Effectively, we are defining what operands a grammar can have
 *
 * Note that this does not just apply to make, plain, and have, but also to
 * conditionals and loops, such as `if`, `while`, and `until`
 */

class Grammar {
public:
	/* This enumeration defines possible operand types */
	enum OperandType { IDENTIFIER, PRONOUN, REFLEXIVE_PRONOUN,
				CHAIN_LITERAL, FRACTION_LITERAL};

private:
	// "make", "have", "comparison", or "plain"
	std::string name;

	// Which leftward and rightward operands are allowed
	// Notice a terminology difference:
	// 	Leftward: literally appears on the left-hand side
	// 	Left Hand Operand: Is an lvalue
	std::set<OperandType> allowed_leftward_operands;
	std::set<OperandType> allowed_rightward_operands;

	// If is_reversed is false, leftward and lho are the same
	// Otherwise, the leftward operand is the rho
	bool is_reversed;

	// Checks the fields for elements left and right, respectively
	bool allowsLeft(OperandType left) const;
	bool allowsRight(OperandType right) const;
public:
	Grammar(const std::string& name_arg) : name(name_arg), is_reversed(false){};
	
	void setReversed(bool reverse = true);

	// These allow calls like
	// setAllowedLeftwardOperands({Grammar::IDENTIFIER,
	// Grammar::CHAIN_LITERAL});
	// These do not assign, but add to their respective fields 
	void addAllowedLeftwardOperands(const std::vector<OperandType>&);
	void addAllowedRightwardOperands(const std::vector<OperandType>&);

	inline bool isReversed() const {return is_reversed;}
	
	inline std::string getName() const{return name;}

	// Because accessing the enum gets obnoxious, we just have these functions
	inline bool allowsLeftIdentifier()	const {return allowsLeft(IDENTIFIER);}
	inline bool allowsLeftPronoun()		const {return allowsLeft(PRONOUN);}
	inline bool allowsLeftReflexivePronoun() const {return allowsLeft(REFLEXIVE_PRONOUN);}
	inline bool allowsLeftChainLiteral()	const {return allowsLeft(CHAIN_LITERAL);}
	inline bool allowsLeftFractionLiteral()	const {return allowsLeft(FRACTION_LITERAL);}

	inline bool allowsRightIdentifier()	const {return allowsRight(IDENTIFIER);}
	inline bool allowsRightPronoun()	const {return allowsRight(PRONOUN);}
	inline bool allowsRightReflexivePronoun() const {return allowsRight(REFLEXIVE_PRONOUN);}
	inline bool allowsRightChainLiteral()	const {return allowsRight(CHAIN_LITERAL);}
	inline bool allowsRightFractionLiteral()	const {return allowsRight(FRACTION_LITERAL);}

	
};
