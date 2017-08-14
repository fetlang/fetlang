#pragma once
#include <string>
#include "FetType.h"
#include "Gender.h"

/* This class represents a dynamically created variable(or constant, technically,
	but that shouldn't come up outside the derived class.)
*/
class Variable{
	std::string code;
	FetType type;
	Gender gender;
	
protected:
	// Should we construct the variable in C?
	bool needs_constructing;

	// Needs to be protect for overriding setName
	std::string name;

	void setCode(const std::string&);

	// Also sets code based on name
	// In BuiltinVariable, this is not true, so we make it virtual here
	virtual void setName(const std::string&);

	void setType(FetType);

public:

	Variable():needs_constructing(true) {}
	Variable(const std::string& name, FetType);
	virtual ~Variable(){}
	// SETTERS
	void setGender(Gender);

	// GETTERS
	std::string getName() const;
	std::string getCode() const;
	std::string getRawCode() const;
	FetType getType() const;
	Gender getGender() const;
	inline bool needsConstructing() const{return needs_constructing;}


};

/* A builtin variable where the code is set before parsing */
class BuiltinVariable: public Variable{
	void setName(const std::string&) override;
	using Variable::setGender;
public:
	BuiltinVariable(const std::string& name, FetType, const std::string& code,
		Gender gender);
};
