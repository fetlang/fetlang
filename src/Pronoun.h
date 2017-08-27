#pragma once
#include <string>
#include "Gender.h"

// Represents a pronoun (duh)
// So there are a fixed, static number of these.
// these are not loaded based on an external file or anything,
// like the operators and comparison operators
class Pronoun {
	// Affects the other
	static const bool OBJECTIVE = true;
	// Affects the self
	static const bool REFLEXIVE = false;

	std::string name;
	Gender gender;
	
	// Determines if it is objective or reflexive
	bool objectivity;

	// Identifiers can proceed after it ignored
	bool possessive;
public:
	Pronoun() {};
	Pronoun(const std::string& n, Gender g, bool o, bool p):
		name(n), gender(g), objectivity(o), possessive(p) {};

	inline std::string getName() const{ return name;}
	inline bool isObjective() const { return objectivity;}
	inline bool isReflexive() const { return !objectivity;}
	inline bool isPossessive() const{ return possessive;}
	inline Gender getGender() const{return gender;}
	
};
