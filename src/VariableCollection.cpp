#include <iostream>
#include "VariableCollection.h"
#include "FetlangException.h"

bool VariableCollection::has(const std::string& variable_name) const{
	return variables.find(variable_name) != variables.end();
}

Variable& VariableCollection::get(const std::string& variable_name) {
	if(!has(variable_name)){
		throw FetlangException("No such variable with name "+variable_name);
	}

	return variables[variable_name];
}

Variable& VariableCollection::access(const std::string& variable_name) {
	Variable& return_value = get(variable_name);
	if(variable_access_list.empty() ||
		variable_access_list.back() != &return_value){
		variable_access_list.push_back(&return_value);
	}
	return return_value;
}
	

Variable& VariableCollection::getLastAdded(){
	if(variable_added_list.empty())
	{
		throw FetlangException("Can't retrieve last variable added because the variable list is empty");
	}
	return *(variable_added_list.back());
}
Variable& VariableCollection::getLastAccessed(){
	if(variable_added_list.empty())
	{
		throw FetlangException("Can't retrieve last variable accessed because the access list is empty");
	}
	return *(variable_access_list.back());
}

void VariableCollection::add(const Variable& variable){
	if(has(variable.getName())){
		throw FetlangException("Variable with "+variable.getName()+" already exists");
	}
	
	variables[variable.getName()] = variable;
	variable_added_list.push_back(&(variables[variable.getName()]));
}


Variable& VariableCollection::getLastOfGender(Gender gender, bool exclude_last){
	for(auto it = variable_access_list.rbegin() + (exclude_last?1:0); it != variable_access_list.rend(); it++){
		if((*it)->getGender() == gender){
			return **it;
		}
		if((*it)->getGender() == UNASSIGNED_GENDER){
			(*it)->setGender(gender);
			return **it;
		}
	}
	throw FetlangException("No variable with the appropriate gender");
}
Variable& VariableCollection::getLastOfGenderExcludingLast(Gender gender){
	return getLastOfGender(gender, true);
}
	
bool VariableCollection::hasLastOfGender(Gender gender, bool exclude_last){
	for(auto it = variable_access_list.rbegin() + (exclude_last?1:0); it != variable_access_list.rend(); it++){
		if((*it)->getGender() == gender){
			return true;
		}
		if((*it)->getGender() == UNASSIGNED_GENDER){
			return true;
		}
	}
	return false;
}
bool VariableCollection::hasLastOfGenderExcludingLast(Gender gender){
	return hasLastOfGender(gender, true);
}


void VariableCollection::display(){
	for(const auto& varpair: variables){
		Variable var = varpair.second;
		std::cout<<var.getName()<<"("<<var.getCode()<<"): "<<var.getType()<<"\n";
	}
}
