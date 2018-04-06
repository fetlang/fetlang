#pragma once
#include <map>
#include <vector>
#include "Variable.h"

/* Class represents a collections of variables

   Allows us to error-check basic operations */

class VariableCollection {
	std::map<std::string, Variable> variables;
	// Holds pointers to the vars in variables
	// In order added
	std::vector<Variable*> variable_added_list;
	// in order of "access"
	// That is, be the parameter to the function "access"
	std::vector<Variable*> variable_access_list;

public:
	VariableCollection(){};

	// Returns true if a variable with that name exists
	bool has(const std::string&) const;

	// Checks to see if variable with that name exists
	// If it does, return that variable, else throw FetlangException
	Variable& get(const std::string&);

	// Same as "get," but adds to the access list
	Variable& access(const std::string&);

	// Return last variable added, error if no variables added
	Variable& getLastAdded();

	// Return last variable accessed, error if no variables accessed
	Variable& getLastAccessed();

	// Dealing with pronouns and gender
	// Retrieves the last variable that is of that gender, or of an unassigned gender
	Variable& getLastOfGender(Gender, bool excluding_last = false);
	// Like the previous method, but does not count the last added variable
	Variable& getLastOfGenderExcludingLast(Gender);

	// Checks  if the previous two methods can occur without exception
	bool hasLastOfGender(Gender, bool excluding_last = false);
	// Like the previous method, but does not count the last added variable
	bool hasLastOfGenderExcludingLast(Gender);

	inline bool empty(){return variables.empty();}

	inline std::vector<Variable> getAll() const {
		std::vector<Variable> output;
		for(const auto& varpair : variables){
			output.push_back(varpair.second);
		}
		return output;
	}

	// Just add a variable
	void add(const Variable&);

	// Display as a list
	void display();
};
