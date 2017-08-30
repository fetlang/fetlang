#include "Variable.h"
#include "FetlangException.h"

void Variable::setGender(Gender gender){
	this->gender = gender;
}
void Variable::setCode(const std::string& code){
	this->code = code;
}
void Variable::setName(const std::string& name){
	this->name = name;

	/* The code and the C identifier are one in the same, here
	
	It takes this format: fetvar_6_richardstallman 
	
	Where the "6" is a unique identifying number,
	and "richardstallman" is a stripped version of the original
	Fetlang identifier
	*/
	
	// Make sure each var is given a unique identifier
	static unsigned int unique_id = 0;
	unique_id++;

	// First parts of C identifier
	this->code = "fetvar_" + std::to_string(unique_id) + "_";

	// Strip the name and add 
	for(const char& c : name){
		if(isalnum(c)){
			this->code += c;
		}
	}
}

void Variable::setType(FetType type){
	this->type = type;
}

std::string Variable::getName() const{
	return this->name;
}
Gender Variable::getGender() const{
	return this->gender;
}
std::string Variable::getCode() const{
	if(getType() == REFERENCE_TYPE){
		return "(*"+this->code+").value";
	}else{
		return this->code;
	}
}
std::string Variable::getRawCode() const{
	return this->code;
}
FetType Variable::getType() const{
	return this->type;
}

Variable::Variable(const std::string& name, FetType type){
	setName(name);
	setGender(UNASSIGNED_GENDER);
	setType(type);
	needs_constructing=true;
}
	
BuiltinVariable::BuiltinVariable(const std::string& name,
				FetType type,
				const std::string& code,
				Gender gender){
	setName(name);
	setGender(gender);
	setType(type);
	setCode(code);
	needs_constructing = false;
}

void BuiltinVariable::setName(const std::string& name){
	this->name = name;
}

