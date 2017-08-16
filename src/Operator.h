#pragma once
#include <string>
#include <map>
#include <set>
#include "FetlangException.h"
#include "FetType.h"

class Operator{
private:
	// What the programmer calls in code, like "spank", "lick", etc
	std::string name;

	// Can be "have", "make", or "plain"
	// see spec for more detail
	std::set<std::string> grammars;
	
	// Verify that the grammar being added or whatever
	// follows the above rules
	void verifyGrammar(const std::string&) const;

/*
	// Used by the transpiler to convert to C code
	// LHO is replaced by the C identifier of the left hand operator
	// and RHO by the right hand operator C identifier
	//
	// The keys can be: fraction/fraction, fraction/chain, chain/fraction
	// or chain/chain
	// The word before the slash is the LHO, the right is the RHO
	std::map<std::string, std::string> code;
*/

	std::map<FetType, std::map<FetType, std::string>> code_map;

	// Check that the key code is actually valid (see above)
	// throw an error otherwise
	inline void verifyCodeKey(const std::string& ck) const{
		if(!(ck=="fraction/fraction" || ck=="fraction/chain" || ck=="chain/fraction" || ck=="chain/chain")) throw FetlangException("No such code key");
	}


	// Is the Left Hand Operand the EXACT(i.e. not decayed) type given?
	bool hasExactLHO(FetType t) const;
	// Is the Right Hand Operand the EXACT(i.e. not decayed) type given?
	bool hasExactRHO(FetType t) const;

	// Get C code for exact types
	std::string getCodeForExactly(FetType, FetType) const;
public:
	Operator(){};
	Operator(const std::string& name);
	virtual ~Operator(){}

	// check if the type pair or code key is assigned to any C code
	bool hasCodeForExactly(FetType lho, FetType rho) const;

	// Create string version of code key
	static std::string makeCodeKeyFrom(FetType lho, FetType rho);
	
	// Create pair<lho, rho> version of code key from string
	static std::pair<FetType, FetType> makeTypePairFrom(const std::string&);

	// Getters and setters
	inline std::string getName() const{return name;}
	inline void setName(const std::string& n){name = n;}

	// check if the type pair or code key is assigned to any C code
	bool hasCodeFor(FetType lho, FetType rho) const;
	bool hasCodeFor(const std::string& ck) const;

	// Get implied types
	// infer the LHO type without context
	FetType inferLeftWithoutContext() const;
	// infer the LHO type with the context of the RHO's type
	FetType inferLeftByRight(FetType) const;
	// Similar methods for the RHO
	FetType inferRightWithoutContext() const;
	FetType inferRightByLeft(FetType) const;

	
	// And, actually get that C code
	std::string getCodeFor(FetType lho, FetType rho) const;

	// Or, add some C code
	void addCode(const std::string& code_key, const std::string& code);

	// Grammar managing functions
	virtual void addGrammar(const std::string&);
	virtual bool hasGrammar(const std::string&) const;
};


// This is for "is", "is not", etc
class ComparisonOperator : public Operator{
public:
	ComparisonOperator(){}
	ComparisonOperator(const std::string& name);

	// Just returns true if value is "comparison"
	bool hasGrammar(const std::string& s )const override;

	// Doesn't apply here, so throw an error
	void addGrammar(const std::string& s) override;
};

