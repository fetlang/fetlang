#include <fstream>
#include <string>
#include <sstream>
#ifdef __WIN32__
#include <windows.h>
#else
#include <unistd.h>
#endif
#include "Builder.h"
#include "Parser.h"
#include "Tokenizer.h"
#include "Transpiler.h"
#include "QuoteUtil.h"
#include "FileUtil.h"
#include "CompilationProcess.h"
// Where we store all the build directories
static const std::string BUILD_ROOT = "/tmp/fetlang_build/";

// Four directory combinations for fetishes: debug, optimized lto, lto only,
// optimized only

// The prefix for each combination. Or, in the case of a debug build, this is
// just the directory name
static const std::string FETISH_DIR_BASE = "/fetish_obj";
// Add this to FETISH_DIR_BASE for -O
static const std::string FETISH_OPT_SUFFIX = "_optimized";
// Use this to FETISH_DIR_BASE for --lto
static const std::string FETISH_LTO_SUFFIX = "_lto";

// Where the compiled .fet file goes
static const std::string STAGE_DIR = "/output/";

// Default output names
#ifndef __WIN32__
static const std::string DEFAULT_OUTPUT = "a.out";
#else
static const std::string DEFAULT_OUTPUT = "a.exe";
#endif
static const std::string DEFAULT_C_OUTPUT = "a.c";// for when invoked with -c

Builder::Builder(){
	// Just explicitly setting our defaults
	optimization = false;
	link_time_optimization = false;
	compilation = true;
	show_tokens = false;
	show_tree = false;
	source_path="";
	destination_path = DEFAULT_OUTPUT;
	build_path = BUILD_ROOT;
}

std::string Builder::transpile() const{
	// get source code
	std::string source = FileUtil::getFileContents(source_path);

	// Tokenize
	Tokenizer tokenizer(source);
	tokenizer.tokenize();
	std::vector<Token> tokens = tokenizer.getTokens();
	if(show_tokens){
		std::cout<<"Displaying tokens:\n";
		for(const Token& token: tokens){
			std::cout<<token<<"\n";
		}
	}

	// Parse
	Parser parser(tokens, tokenizer.getLineIndents());
	parser.formTree();
	if(show_tree){
		std::cout<<"Displaying tree:\n";
		parser.getTree().display();
	}

	// Transpile
	Transpiler transpiler(parser.getTree(), parser.getVariables());
	return transpiler.transpile();
}



void Builder::build(){
	std::string c_code = transpile();
	CompilationProcess comp_proc;

	// No compilation, just output C code
	if(!compilation){
		// Should end with ".c"
		if(destination_path == DEFAULT_OUTPUT){
			destination_path = DEFAULT_C_OUTPUT;
		}

		// Write the c code
		std::ofstream outfile(destination_path);
		if(!(outfile << c_code)){
			outfile.close();
			throw FetlangException("Could not write to "+destination_path);
		}
		outfile.close();

		// And done with that
		return;
	}

	// Okay, we do compiling
	// Let's compile fetishes first

	// Get the general fetish path
	std::string fetish_path = build_path + FETISH_DIR_BASE;
	if(optimization)
		fetish_path += FETISH_OPT_SUFFIX;
	if(link_time_optimization)
		fetish_path += FETISH_LTO_SUFFIX;
	fetish_path += "/";

	//  Let's make sure the build directories exist
	FileUtil::ensureDirectoryExists(fetish_path);
	FileUtil::ensureDirectoryExists(build_path+STAGE_DIR);

	// General include paths
	std::vector<std::string> include_paths;
	for(const Fetish& fetish : manager.getFetishes()){
		std::string inc_path = fetish.getIncludePath();
		if(std::find(include_paths.begin(), include_paths.end(), inc_path) == include_paths.end()){
			inc_path = FileUtil::getParentPath(inc_path);
			inc_path = FileUtil::getParentPath(inc_path) + "/";
			include_paths.push_back(inc_path);
		}
	}
	if(include_paths.empty()){throw FetlangException("Include paths should not be empty");}

	// And compile each fetish
	std::vector<std::string> all_objects;
	for(const Fetish& fetish: manager.getFetishes()){
		FileUtil::ensureDirectoryExists(fetish_path+"/"+fetish.getName());
		// Each source file gets compiled independently
		for(const std::string& source_file : fetish.getSources()){
			all_objects.push_back(fetish_path+"/"+fetish.getName()+"/"+source_file+".o");
			std::string source_path = fetish.getSourcePath()+source_file;

			if(!FileUtil::fileExists(all_objects.back())){
				comp_proc
					.clear()
					.setOptimization(optimization)
					.setLinkTimeOptimization(link_time_optimization)
					.addIncludeDirectories(include_paths)
					.addIncludeDirectory(fetish.getIncludePath())
					.addLibraries(fetish.getLibraries())
					.compile({source_path},all_objects.back());
			}
		}
	}

	// Write the generated C file
	std::string c_file_path = build_path+STAGE_DIR+"/stage.c";
	std::ofstream generated_c_file(c_file_path);
	generated_c_file<< c_code;
	generated_c_file.close();
	all_objects.push_back(c_file_path+".o");

	// Compile the generated C file
	comp_proc
		.clear()
		.addIncludeDirectories(include_paths)
		.setOptimization(optimization)
		.setLinkTimeOptimization(link_time_optimization)
		.compile({c_file_path}, all_objects.back());

	// And link to create the output
	comp_proc.clear()
		.setOptimization(optimization)
		.setLinkTimeOptimization(link_time_optimization)
		.setLanguage("c++")
		.link(all_objects, destination_path);

}

void Builder::clean() const{
	FileUtil::ensureDirectoryDoesNotExist(build_path);
	FileUtil::ensureDirectoryExists(build_path);
}

