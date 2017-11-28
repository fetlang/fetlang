#include "Operator.h"
#include "FetlangException.h"
std::string Operator::makeCodeKeyFrom(FetType lho, FetType rho) {
	lho = decayFetType(lho);
	rho = decayFetType(rho);
	std::string return_value;
	switch(lho){
	case FRACTION_TYPE:
		return_value += "fraction";
		break;
	case CHAIN_TYPE:
		return_value += "chain";
		break;
	default:
		throw FetlangException("Can't make code key out of this type");
	}
	switch(rho){
	case FRACTION_TYPE:
		return return_value + "/fraction";
	case CHAIN_TYPE:
		return return_value + "/chain";
	default:
		throw FetlangException("Can't make code key out of this type");
	}
}

FetType makeSingleTypeFrom(const std::string& s){
	if(s=="reference"){
		return REFERENCE_TYPE;
	}else if(s=="stream"){
		return STREAM_TYPE;
	}else if(s=="fraction"){
		return FRACTION_TYPE;
	}else if(s=="chain"){
		return CHAIN_TYPE;
	}
	throw FetlangException("No such type '"+s+"'");
}

std::pair<FetType, FetType> Operator::makeTypePairFrom(const std::string& s){
	if(s.find("/") == std::string::npos){
		throw FetlangException("No slash in code key '"+s+"'");
	}
	FetType first = makeSingleTypeFrom(s.substr(0, s.find("/")));
	FetType second = makeSingleTypeFrom(s.substr(s.find("/")+1));

	return std::pair<FetType, FetType>(first, second);
}


bool Operator::hasCodeForExactly(FetType lho, FetType rho) const{
	if(code_map.find(lho) != code_map.end()){
		if(code_map.at(lho).find(rho) != code_map.at(lho).end()){
			return true;
		}
	}
	return false;
}

std::string Operator::getCodeForExactly(FetType lho, FetType rho) const{
	if(!hasCodeForExactly(lho, rho)){
		throw("Operator "+name+" does not have code for exact types given");
	}
	return code_map.at(lho).at(rho);
}

bool Operator::hasCodeFor(FetType lho, FetType rho) const{
	if(hasCodeForExactly(lho, rho)||
		hasCodeForExactly(lho, decayFetType(rho))||
		hasCodeForExactly(decayFetType(lho), rho)||
		hasCodeForExactly(decayFetType(lho), decayFetType(rho))){
		return true;
	}
	return false;
}

std::string Operator::getCodeFor(FetType lho, FetType rho) const{
	if(hasCodeForExactly(lho, rho))
		return getCodeForExactly(lho, rho);
	if(hasCodeForExactly(lho, decayFetType(rho)))
		return getCodeForExactly(lho, decayFetType(rho));
	if(hasCodeForExactly(decayFetType(lho), rho))
		return getCodeForExactly(decayFetType(lho), rho);
	if(hasCodeForExactly(decayFetType(lho), decayFetType(rho)))
		return getCodeForExactly(decayFetType(lho), decayFetType(rho));
	throw FetlangException("Operator `"+name+"` does not have code for types given");
}
	
bool Operator::hasCodeFor(const std::string& ck) const{
	auto type_pair = makeTypePairFrom(ck);
	return hasCodeFor(type_pair.first, type_pair.second);
}


	
void Operator::addCode(const std::string& code_key, const std::string& code){
	auto type_pair = makeTypePairFrom(code_key);

	if(hasCodeFor(type_pair.first, type_pair.second)){
		throw FetlangException("Can't add code, code already exists for code key in operator " + getName());
	}
	
	code_map[type_pair.first][type_pair.second] = code;
}

// Get the exact LHO without decaying
bool Operator::hasExactLHO(FetType t) const{
	return code_map.find(t) != code_map.end();
}
bool Operator::hasExactRHO(FetType t) const{
	const int number_of_types = 4;
	const FetType types[number_of_types] = {FRACTION_TYPE, CHAIN_TYPE,
		REFERENCE_TYPE, STREAM_TYPE};
	
	for(int i=0; i < number_of_types; i++){
		if(hasCodeForExactly(types[i], t)){
			return true;
		}
	}

	return false;
}


FetType Operator::inferLeftWithoutContext() const{
	if(hasExactLHO(CHAIN_TYPE))
		return CHAIN_TYPE;
	if(hasExactLHO(FRACTION_TYPE))
		return FRACTION_TYPE;
	if(hasExactLHO(STREAM_TYPE))
		return STREAM_TYPE;
	if(hasExactLHO(REFERENCE_TYPE))
		return REFERENCE_TYPE;
	throw FetlangException("Can't infer lho type - apparently no LHO types exists in operator `"+getName()+"`");
}

FetType Operator::inferRightWithoutContext() const{
	if(hasExactRHO(CHAIN_TYPE))
		return CHAIN_TYPE;
	if(hasExactRHO(FRACTION_TYPE))
		return FRACTION_TYPE;
	if(hasExactRHO(STREAM_TYPE))
		return STREAM_TYPE;
	if(hasExactRHO(REFERENCE_TYPE))
		return REFERENCE_TYPE;
	throw FetlangException("Can't infer rho type - apparently no RHO types exists in operator `"+getName()+"`");
}

FetType Operator::inferLeftByRight(FetType rho) const{
	if(hasCodeFor(CHAIN_TYPE, rho))
		return CHAIN_TYPE;
	if(hasCodeFor(FRACTION_TYPE, rho))
		return FRACTION_TYPE;
	if(hasCodeFor(STREAM_TYPE, rho))
		return STREAM_TYPE;
	if(hasCodeFor(REFERENCE_TYPE, rho))
		return REFERENCE_TYPE;
	throw FetlangException("Can't infer left type in operator `" +
		getName()+
			"`(no overloaded form of the operator exists for these types)");
}

FetType Operator::inferRightByLeft(FetType lho) const{
	if(hasCodeFor(lho, CHAIN_TYPE))
		return CHAIN_TYPE;
	if(hasCodeFor(lho, FRACTION_TYPE))
		return FRACTION_TYPE;
	if(hasCodeFor(lho, STREAM_TYPE))
		return STREAM_TYPE;
	if(hasCodeFor(lho, REFERENCE_TYPE))
		return REFERENCE_TYPE;
	throw FetlangException("Can't infer the right type in operator `" +
		getName()+
			"`(no overloaded form of the operator exists for these types)");
}

void Operator::verifyGrammar(const std::string& grammar) const{
	if(!(grammar=="have" || grammar=="make" || grammar=="plain" || grammar=="bind")){
		throw FetlangException("Grammar must be have, make, or plain(given "+grammar+")");
	}
}

Operator::Operator(const std::string& name){
	setName(name);
}

void Operator::addGrammar(const std::string& grammar){
	verifyGrammar(grammar);
	grammars.emplace(grammar);
}

bool Operator::hasGrammar(const std::string& grammar) const{
	verifyGrammar(grammar);
	return grammars.find(grammar) != grammars.end();
}

ComparisonOperator::ComparisonOperator(const std::string& name){
	setName(name);
}

bool ComparisonOperator::hasGrammar(const std::string& s) const{
	return s=="comparison";
}

void ComparisonOperator::addGrammar(const std::string&){
	throw FetlangException("ComparisonOperator can't add grammar");
}


