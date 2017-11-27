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
static const char*const BUILD_FOLDER_RELATIVE = "/fetlang_build/";
// Relative to BUILD_FOLDER_RELATIVE
static const char*const RELEASE_FOLDER_RELATIVE = "/fetish_obj_release/";
static const char*const DEBUG_FOLDER_RELATIVE = "/fetish_obj_debug/";
static const char*const STAGE_FOLDER_RELATIVE = "/output/";
#ifndef __WIN32__
static const char*const DEFAULT_DESTINATION_PATH = "a.out";
#else
static const char*const DEFAULT_DESTINATION_PATH = "a.exe";
#endif

Builder::Builder(){
	// Just explicitly setting our defaults
	optimization = false;
	link_time_optimization = false;
	compilation = true;
	show_tokens = false;
	show_tree = false;
	source_path="";
	destination_path = DEFAULT_DESTINATION_PATH;

	// Now we have to find the temporary directory
	//TODO: Fix for all operating systems
	build_path = std::string("/tmp/")+BUILD_FOLDER_RELATIVE;
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
		if(destination_path == DEFAULT_DESTINATION_PATH){
			destination_path = "a.c";
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
	std::string fetish_path;
	if(optimization)
		fetish_path = build_path + RELEASE_FOLDER_RELATIVE;
	else
		fetish_path = build_path + DEBUG_FOLDER_RELATIVE;

	//  Let's make sure the build directories exist
	FileUtil::ensureDirectoryExists(fetish_path);
	FileUtil::ensureDirectoryExists(build_path+STAGE_FOLDER_RELATIVE);

	// General include path
	std::string include_path = manager.getFetishes()[0].getIncludePath();
	include_path = FileUtil::getParentPath(include_path);
	include_path = FileUtil::getParentPath(include_path);

	// And compile each fetish
	std::vector<std::string> all_objects;
	for(const Fetish& fetish: manager.getFetishes()){
		FileUtil::ensureDirectoryExists(fetish_path+"/"+fetish.getName());
		// Each source file gets compiled independently
		for(const std::string& source_file : fetish.getSources()){
			all_objects.push_back(fetish_path+"/"+fetish.getName()+"/"+source_file+".o");
			std::string source_path = fetish.getSourcePath()+source_file;

			if(!FileUtil::fileExists(all_objects.back())){
				comp_proc.
					clear()
					.setOptimization(optimization)
					.addIncludeDirectories({include_path, fetish.getIncludePath()})
					.addLibraries(fetish.getLibraries())
					.compile({source_path},all_objects.back());
			}
		}
	}

	// Write the generated C file
	std::string c_file_path = build_path+STAGE_FOLDER_RELATIVE+"/stage.c";
	std::ofstream generated_c_file(c_file_path);
	generated_c_file<< c_code;
	generated_c_file.close();
	all_objects.push_back(c_file_path+".o");

	// Compile the generated C file
	comp_proc
		.clear()
		.addIncludeDirectory(include_path+"/")
		.setOptimization(optimization)
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

