#pragma once
#include "FetlangManager.h"

/*
 * This class handles compilation, linkage, and other such nonsense
 * AS WELL AS the lexing/parsing/transpiling
 *
 * Basically, load up the source file, and bam you get your executable
 */

class Builder{
	// Debug options: display tokens or syntax tree
	// Off by default
	bool show_tokens;
	bool show_tree;

	// Do we enable compiler optimization?
	// If this is set to true, we use the `-O2` and `-s` flags
	// (only use `-s` if applicable, or suppress warning)
	//
	// Off by default
	bool optimization;
	bool link_time_optimization;

	// Do we actually compile? or do we just produce a .c file?
	// On by default
	bool compilation;
	
	// Where is the original (fetlang) source file?
	std::string source_path;
	// And where are we putting this? (defaults to ./a.out)
	std::string destination_path;

	// Where everything, including the compiled fetishes and stage folder goes
	// Directory layout is like so:
	//
	// fetlang_build
	//	fet_debug
	//		core
	//			core_file_1.o
	//			core_File2.o
	//	fet_release
	//		core
	//			core_file_1.o
	//			core_file_2.o
	//	output
	//		a.c
	//		a.o
	//
	// (Or something like that, anyway)
	std::string build_path;

	// Use the tokenizer, parser, and transpiler to generate C code
	// from the Fetlang code in source_path
	std::string transpile() const;
	
	int compile(const std::vector<std::string>& args = {}, bool link = false);
public:
	// Set defaults
	Builder();

	// Enable or disable optimization
	inline void setOptimization(bool o = true){optimization = o;}
	inline void setLinkTimeOptimization(bool o = true){link_time_optimization = o;}

	// ...or compilation
	inline void setCompilation(bool c = true){compilation = c;}

	// Source and destination
	inline void setSource(const std::string& s){source_path = s;}
	inline void setDestination(const std::string& d){destination_path = d;}

	// Remove everything in fet_Debug and fet_release
	void clean() const;

	// Debug
	inline void showTokens(bool s = true){show_tokens = s;}
	inline void showTree(bool s = true){show_tree = s;}

	// Do the do
	void build();


};



