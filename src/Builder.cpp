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
static const char*const BUILD_FOLDER_RELATIVE = "/fetlang_build/";
// Relative to BUILD_FOLDER_RELATIVE
static const char*const RELEASE_FOLDER_RELATIVE = "/fet_obj_release/";
static const char*const DEBUG_FOLDER_RELATIVE = "/fet_obj_debug/";
static const char*const STAGE_FOLDER_RELATIVE = "/output/";
#ifndef __WIN32__
static const char*const DEFAULT_DESTINATION_PATH = "a.out";
#else
static const char*const DEFAULT_DESTINATION_PATH = "a.exe";
#endif

Builder::Builder(){
	// Just explicitly setting our defaults
	optimization = false;
	compilation = true;
	show_tokens = false;
	show_tree = false;
	source_path="";
	destination_path = DEFAULT_DESTINATION_PATH;
	compiler = "cc";

	// Now we have to find the temporary directory
	//TODO: Fix for all operating systems
	build_path = std::string("/tmp/")+BUILD_FOLDER_RELATIVE;
}

std::string Builder::transpile() const{
	// get source code
	std::ifstream fetfile(source_path);
	std::string source;
	std::stringstream buffer;
	if(fetfile.bad()){
		fetfile.close();
		throw FetlangException("Could not open file "+ source_path);
	}
	buffer << fetfile.rdbuf();
	source = buffer.str();
	fetfile.close();

	// Tokenize
	Tokenizer tokenizer;
	std::vector<Token> tokens = tokenizer.tokenize(source);
	if(show_tokens){
		std::cout<<"Displaying tokens:\n";
		for(const Token& token: tokens){
			std::cout<<token<<"\n";
		}
	}

	// Parse
	Parser parser(tokens);
	parser.formTree();
	if(show_tree){
		std::cout<<"Displaying tree:\n";
		parser.getTree().display();
	}

	// Transpile
	Transpiler transpiler(parser.getTree(), parser.getVariables());
	return transpiler.transpile();
}

// Make an argument string safe for consumption
static std::string sanitize(const std::string& argument){
	return QuoteUtil::quote(argument);
}
	
int Builder::compile(const std::vector<std::string>& args){
	std::string command = compiler;
	command += " -std=c99 ";
	if(optimization){
		command += " -O2 -s ";
	}
	#if defined(__linux__) || defined(linux)
	// Linux has a separate math library
	command += " -lm ";
	#endif
	for(const std::string& arg : args)
	{
		command += " "+sanitize(arg);
	}
	//command+=" > /dev/null";
	FILE* compiler_process = popen(command.c_str(), "r");
	return pclose(compiler_process);
}


void Builder::build(){
	std::string c_code = transpile();

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
		for(const std::string& source_file : fetish.getSources()){
			FileUtil::ensureDirectoryExists(fetish_path+"/"+fetish.getName());
			all_objects.push_back(fetish_path+"/"+fetish.getName()+"/"+source_file+".o");
			compile({
				"-c", fetish.getSourcePath()+source_file,
				"-I"+include_path,
				"-I"+fetish.getIncludePath(),
				"-o", all_objects.back()
			});
		}
	}

	// Write the generated C file
	std::string c_file_path = build_path+STAGE_FOLDER_RELATIVE+"/stage.c";
	std::ofstream generatedCFile(c_file_path);
	generatedCFile << c_code;
	generatedCFile.close();
	all_objects.push_back(c_file_path+".o");

	// Compile the generated C file
	std::vector<std::string> c_args = {"-c", c_file_path, "-o", all_objects.back()};
	c_args.push_back("-I"+include_path+"/");
	compile(c_args);

	// And link to create the output
	c_args.clear();
	for(const std::string& object: all_objects){
		c_args.push_back(object);
	}
	c_args.push_back("-o");
	c_args.push_back(destination_path);
	compile(c_args);

}

