#include <fstream>
#include "FileUtil.h"
#include "thirdparty/json.hpp"
#include "FetlangManager.h"
using json = nlohmann::json;

// public getting/finding/whatever methods
bool FetlangManager::isPartOfKeyphrase(const std::string& word) const{
	return keywords.find(word) != keywords.end();
}

bool FetlangManager::isKeyphrase(const std::string& phrase) const{
	return keyphrases.find(phrase) != keyphrases.end();
}

KeyphraseCategory FetlangManager::getKeyphraseCategory(const std::string& phrase) const{
	if(!isKeyphrase(phrase)){
		throw FetlangException(phrase + " is not a keyphrase");
	}
	return keyphrases.at(phrase);
}

Operator FetlangManager::getOperator(const std::string& operator_name) const{
	if(getKeyphraseCategory(operator_name) != OPERATOR_KEYPHRASE){
		throw FetlangException("`"+operator_name+"`  is not an operator");
	}
	return operators.at(operator_name);
}

ComparisonOperator FetlangManager::getComparisonOperator(const std::string& operator_name) const{
	if(getKeyphraseCategory(operator_name) != COMPARISON_OPERATOR_KEYPHRASE){
		throw FetlangException("`"+operator_name+"`  is not an comparison operator");
	}
	return comparison_operators.at(operator_name);
}

Pronoun FetlangManager::getPronoun(const std::string& pronoun_name) const{
	if(getKeyphraseCategory(pronoun_name) != PRONOUN_KEYPHRASE){
		throw FetlangException("`"+pronoun_name+"`  is not an pronoun");
	}
	return pronouns.at(pronoun_name);
}

		
// Fill the list of pronouns
void FetlangManager::loadPronouns(){
	Pronoun pronoun_array[] = {
		// Objective pronouns
		Pronoun("him", MALE_GENDER, true, false),
		Pronoun("her", FEMALE_GENDER, true, true),// Special case, because her can be possessive or not
		Pronoun("them", NEUTRAL_GENDER, true, false),
		Pronoun("it", NONPERSON_GENDER, true, false),

		// Reflexive pronouns
		Pronoun("himself", MALE_GENDER, false, false),
		Pronoun("herself", FEMALE_GENDER, false, false),
		Pronoun("themself", NEUTRAL_GENDER, false, false),
		Pronoun("itself", NONPERSON_GENDER, false, false),

		// Possessive (and tech. objective)pronouns
		Pronoun("his", MALE_GENDER, true, true),
		//Pronoun("her", FEMALE_GENDER, true, true),
		Pronoun("their", NEUTRAL_GENDER, true, true),
		Pronoun("its", NONPERSON_GENDER, true, true),

		// Possessive reflexive pronouns
		Pronoun("his own", MALE_GENDER, false, true),
		Pronoun("her own", FEMALE_GENDER, false, true),
		Pronoun("their own", NEUTRAL_GENDER, false, true),
		Pronoun("its own", NONPERSON_GENDER, false, true),
		};	

	for(const Pronoun& pronoun : pronoun_array){
		pronouns[pronoun.getName()] = pronoun;
	}
}

// Add a new fetish directory
void FetlangManager::addFetishDirectory(const std::string& path){
	fetish_directories.push_back(path);
}

// Convert text from a file into a JSON object
static json loadFileAsJson(const std::string& filename){
	json return_value;
	std::ifstream file(filename);
	file >> return_value;
	file.close();
	return return_value;
}

void FetlangManager::loadFetishFile(Fetish& fetish, const std::string& filename){
	json data = loadFileAsJson(filename);

	// Load dependencies
	if(data.find("dependencies") != data.end()){
		auto dependencies = data["dependencies"];
		if(dependencies.find("libraries") != dependencies.end()){
			auto libraries = dependencies["libraries"];
			for(const auto& lib : libraries){
				fetish.addLibrary(lib.get<std::string>());
			}
		}
		if(dependencies.find("fetishes") != dependencies.end()){
			auto fetishes = dependencies["fetishes"];
			for(const auto& fet : fetishes){
				loadFetish(fet);
			}
		}
	}
	// load operators
	for(const auto& operator_data : data["operators"]){
		Operator op(operator_data["name"].get<std::string>());
		// Just load fields
		for(const auto& grammar : operator_data["grammars"]){
			op.addGrammar(grammar.get<std::string>());
		}
		for(auto code = operator_data["code"].begin();code != operator_data["code"].end();code++){
			op.addCode(code.key(), code.value());
		}
	
		// Add the operator, but 
		operators[op.getName()] = op;
		// If there an an alternate name of this
		if(operator_data.find("alt") != operator_data.end()){
			operators[operator_data["alt"].get<std::string>()] = op;
		}
	}

	// Load -comparison- operators
	for(const auto& operator_data : data["comparison_operators"]){
		ComparisonOperator op(operator_data["name"].get<std::string>());
		for(auto code = operator_data["code"].begin();code != operator_data["code"].end();code++){
			op.addCode(code.key(), code.value());
		}
		comparison_operators[op.getName()] = op;
		if(operator_data.find("alt") != operator_data.end()){
			comparison_operators[operator_data["alt"].get<std::string>()] = op;
		}
	}

	// Load builtin variables
	for(const auto& builtin_data : data["builtins"]){
		// Interpret type
		FetType type;
		if(builtin_data.find("type") == builtin_data.end()){
			throw FetlangException("Builtin doesn't give attribute `type` in fetish");
		}
		std::string type_as_string = builtin_data["type"].get<std::string>();
		if(type_as_string == "chain"){
			type = CHAIN_TYPE;
		}else if(type_as_string == "fraction"){
			type = FRACTION_TYPE;
		}else if(type_as_string == "reference"){
			type = REFERENCE_TYPE;
		}else if(type_as_string == "stream"){
			type = STREAM_TYPE;
		}else{
			throw FetlangException("`"+type_as_string+"is not a valid Fetlang type");
		}

		// Interpret gender
		Gender gender;
		if(builtin_data.find("gender") == builtin_data.end()){
			throw FetlangException("Builtin doesn't give attribute `gender` in fetish");
		}
		std::string gender_as_string = builtin_data["gender"].get<std::string>();
		if(gender_as_string == "female"){
			gender = FEMALE_GENDER;
		}else if(gender_as_string == "male"){
			gender = MALE_GENDER;
		}else if(gender_as_string == "neutral"){
			gender = NEUTRAL_GENDER;
		}else if(gender_as_string == "nonperson"){
			gender = NONPERSON_GENDER;
		}else if(gender_as_string == "unassigned"){
			gender = UNASSIGNED_GENDER;
		}else if(gender_as_string == "n/a"){
			gender = NA_GENDER;
		}else{
			throw FetlangException("`"+gender_as_string+" is not a valid Fetlang gender");
		}


		// "And the rest!"
		if(builtin_data.find("name") == builtin_data.end()){
			throw FetlangException("Builtin doesn't give attribute `name` in fetish");
		}
		if(builtin_data.find("code") == builtin_data.end()){
			throw FetlangException("Builtin doesn't give attribute `code` in fetish");
		}
		std::string name_as_string = builtin_data["name"].get<std::string>();
		std::string code_as_string = builtin_data["code"].get<std::string>();

		BuiltinVariable var(name_as_string, type, code_as_string, gender);

		builtins.push_back(var);
	}

	// Load extra code (preloop, postloop)
	if(data.find("preloop_code") != data.end()){
		std::string temp = data["preloop_code"];
		preloop_code += temp;
	}
	if(data.find("postloop_code") != data.end()){
		std::string temp = data["postloop_code"];
		postloop_code += temp;
	}

}

std::vector<Fetish> FetlangManager::getFetishes() const{
	return fetishes;
}
bool FetlangManager::hasFetish(const std::string& fetish_name) const{
	for(const Fetish& fetish: fetishes){
		if(fetish.getName() == fetish_name){
			return true;
		}
	}
	return false;
}

void FetlangManager::loadFetish(const std::string& fetishname){
	// Don't reload
	if(hasFetish(fetishname)){
		return;
	}

	try{
		// Fine out where exactly the fetish is located and load the fetish.json
		// file
		for(std::string directory: fetish_directories){
			directory += "/"+fetishname;
			std::string filename = directory+"/fetish.json";
			if(std::ifstream(filename)){
				// Found it
				Fetish fetish(fetishname, directory);
				fetishes.push_back(fetish);

				// Load json file
				try{
					loadFetishFile(fetish, filename);
				}catch(const std::exception& e){
					throw FetlangException("Problem loading "+fetishname+"'s fetish file: "+e.what());
				}

				// Load headers and sources
				for(const std::string& filename:
					FileUtil::getFilesInDirectory(fetish.getIncludePath())){
					fetish.addInclude(filename);
				}
				for(const std::string& filename:
					FileUtil::getFilesInDirectory(fetish.getSourcePath())){
					fetish.addSource(filename);
				}
				
				fetishes.push_back(fetish);
				doLoading();
				return;
			}
		}
		throw FetlangException("No fetish file for `"+fetishname+"` exists");
	}catch(const FetlangException& e){
		e.display();
		exit(EXIT_FAILURE);
	}catch(const std::exception& e){
		std::cerr<<"An exception occurred: "<<e.what()<<"\n";
		exit(EXIT_FAILURE);
	}catch(...){
		std::cerr<<"An unknown exception occurred\n";
		exit(EXIT_FAILURE);
	}
}

void FetlangManager::doLoading()
{
	keyphrases.clear();
	keywords.clear();
	// Dynamic keyphrases
	for(const auto& kp : operators) keyphrases[kp.first] = OPERATOR_KEYPHRASE;
	for(const auto& kp : comparison_operators) keyphrases[kp.first] = COMPARISON_OPERATOR_KEYPHRASE;

	// Static keyphrases
	loadPronouns();
	const char* control_keyphrases[] = {"have", "times","time","make", "if", "while",
	"until", "bind", "just bind", "call safeword", "otherwise"};
	for(const auto& kp: pronouns){keyphrases[kp.first] = PRONOUN_KEYPHRASE;}
	for(const auto& kp: control_keyphrases){keyphrases[kp] = CONTROL_KEYPHRASE;}
	
		

	max_keyphrase_size = 0;
	for(const auto& keyphrase: keyphrases){
		// split keyphrase into words
		std::vector<std::string> words_of_keyphrase;
		std::istringstream temp(keyphrase.first);
		copy(std::istream_iterator<std::string>(temp),
			std::istream_iterator<std::string>(),
			back_inserter(words_of_keyphrase));

		// Check size
		if(static_cast<int>(words_of_keyphrase.size()) > max_keyphrase_size){
			max_keyphrase_size = words_of_keyphrase.size();
		}
		
		// And add those words
		for(const auto& word : words_of_keyphrase){
			keywords.insert(word);
		}
	}
}

void FetlangManager::initialize(){
	static bool initialized = false;
	if(initialized){
		throw FetlangException("Can't initialize FetlangManager twice");
	}
	initialized = true;

	fetish_directories.push_back(FileUtil::getExecutableParentPath()+"/../share/fetlang/fetishes/");
	fetish_directories.push_back("../fetishes/");
	loadFetish("core");
}

int FetlangManager::getMaxKeyphraseSize() const{
	return max_keyphrase_size;
}


// Create the singleton
FetlangManager& FetlangManager::getInstance(){
	static bool have_initialized = false;
	static FetlangManager manager;
	if(!have_initialized){
		manager.initialize();
		have_initialized = true;
	}
	return manager;
}
FetlangManager& manager = FetlangManager::getInstance();
