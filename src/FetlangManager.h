#pragma once
#include <map>
#include <set>
#include <string>
#include <vector>
#include "FetType.h"
#include "FetlangException.h"
#include "KeyphraseCategory.h"
#include "Gender.h"
#include "Pronoun.h"
#include "Operator.h"
#include "Variable.h"

// Represents a fetish/package loaded
class Fetish{
	std::string name;
	// The absolute root file path of the fetish
	std::string root_path;
	// Filenames (not paths) of the headers
	std::vector<std::string> includes;
	// And of the sources
	std::vector<std::string> sources;
	// Dependencies!
	// Any libs we depend on
	std::vector<std::string> libraries;
public:
	Fetish(const std::string& name_arg, const std::string& path_arg):
		name(name_arg), root_path(path_arg){}

	inline std::string getName() const {return name;}

	// Get header and source paths
	inline std::string getIncludePath() const{return root_path+"/include/";}
	inline std::string getSourcePath() const{return root_path+"/source/";}
	inline std::string getRootPath() const{return root_path;}

	// Regular getters
	inline std::vector<std::string> getIncludes() const{return includes;}
	inline std::vector<std::string> getSources() const{return sources;}
	inline std::vector<std::string> getLibraries() const{return libraries;}

	// used by the FetlangManager
	inline void addInclude(const std::string&
		filename){includes.push_back(filename);}
	inline void addSource(const std::string&
		filename){sources.push_back(filename);}
	inline void addLibrary(const std::string&
		lib){libraries.push_back(lib);}
};

// Singleton class for managing fetishes and keyphrases and other
// such configurations and such
//
// Contains methods for dealing with the collection of data that is
// the Fetlang operators, pronouns, and other keyphrase
//
// Contains as well the aforementioned data collection
// Must be initialized before the Tokenizer class is used
// in order to read from JSON files
class FetlangManager{
private:
	// Directories where we look for fetishes
	std::vector<std::string> fetish_directories;

	// Fetishes we've loaded
	std::vector<Fetish> fetishes;

	// Builtin variables we've loaded (from the fetishes)
	std::vector<BuiltinVariable> builtins;

	// All keyphrases with assigned category
	std::map<std::string, KeyphraseCategory> keyphrases; 

	// Just all keywords - used for the tokenizer class when trying to merge
	// keyphrases together
	std::set<std::string> keywords;

	// Used by the lexer to figure out where to replace pronouns
	// with variables
	std::map<std::string, Pronoun> pronouns;

	// These are more used by the parser, and transpiler
	// For actually figuring what the language is doing
	std::map<std::string, Operator> operators; 
	std::map<std::string, ComparisonOperator> comparison_operators;

	// Code inserted into the final .c file
	// Before main do-while loop
	std::string preloop_code;
	// After main do-while loop
	std::string postloop_code;

	// Add operators etc
	void loadFetishFile(Fetish&, const std::string&);

	// Keep track of what the longest keyphrase is
	int max_keyphrase_size;
	
	// Load pronouns (these don't change)
	void loadPronouns();

	// Private constructor
	FetlangManager(){};

	// This MUST be called before proper use
	void initialize();

	// This fills out all the properties of this class
	// Called every time a fetish is loaded (inc. core)
	void doLoading();
public:
	// Create the singleton and initialize() it
	static FetlangManager& getInstance();

	// Loads a fetish by name, eg "core"
	void loadFetish(const std::string&);

	// Get the list of fetishes
	std::vector<Fetish> getFetishes() const;
	// Or check if a specific fetish exists
	bool hasFetish(const std::string&) const;

	// Get the list of builtins
	inline std::vector<BuiltinVariable> getBuiltins() const{return builtins;}

	// Check if string is part of a string in keyphrases
	bool isPartOfKeyphrase(const std::string&) const;

	// Check if string is in keyphrases
	bool isKeyphrase(const std::string&) const;

	// Add an external directory location
	void addFetishDirectory(const std::string&);
	inline std::vector<std::string> getFetishDirectories() const{return fetish_directories;}

	// Return as keyphrase category enum
	KeyphraseCategory getKeyphraseCategory(const std::string&) const;

	// Return as proper objects
	Operator getOperator(const std::string&) const;
	ComparisonOperator getComparisonOperator(const std::string&) const;
	Pronoun getPronoun(const std::string&) const;

	int getMaxKeyphraseSize() const;

	// Return code
	inline std::string getPreloopCode() const{return preloop_code;}
	inline std::string getPostloopCode() const{return postloop_code;}

};

// THE fetlang manager object
extern FetlangManager& manager;
