#include "CompilationProcess.h"
#include "FetlangException.h"
#include "QuoteUtil.h"
#include "FileUtil.h"
#include <stdio.h>

CompilationProcess::CompilationProcess(){clear();}


CompilationProcess& CompilationProcess::clear(){
	language = "";
	compiler = "";
	optimization = false;
	link_time_optimization = false;
	extra_arguments.clear();
	include_directories.clear();
	libraries.clear();
	return *this;
}

CompilationProcess& CompilationProcess::setCompiler(const std::string& new_compiler){
	this->compiler = new_compiler;
	// Infer language
	if(this->language == ""){
		if(compiler == "cc") setLanguage("c");
		if(compiler == "gcc") setLanguage( "c");
		if(compiler == "clang") setLanguage( "c");
		if(compiler == "clang++") setLanguage( "c++");
		if(compiler == "c++") setLanguage( "c++");
		if(compiler == "g++") setLanguage( "c++");
		if(compiler == "rustc") setLanguage( "rust");
	}

	return *this;
}
CompilationProcess& CompilationProcess::setLanguage(const std::string& lang){
	if(lang == "")
	{
		throw FetlangException("Can't set language as blank");
	}
	this->language = lang;
	if(this->compiler == ""){
		if(language == "c") setCompiler("cc");
		if(language == "c++") setCompiler("c++");
		if(language == "rust") setCompiler("rustc");
	}
	return *this;
}

CompilationProcess& CompilationProcess::setOptimization(bool optimize){
	this->optimization = optimize;
	return *this;
}

CompilationProcess& CompilationProcess::setLinkTimeOptimization(bool optimize){
	this->link_time_optimization = optimize;
	return *this;
}

CompilationProcess& CompilationProcess::addArgument(const std::string& argument){
	this->extra_arguments.push_back(argument);
	return *this;
}
CompilationProcess& CompilationProcess::addArguments(const std::vector<std::string>& arguments){
	this->extra_arguments.insert(this->extra_arguments.end(), arguments.begin(), arguments.end());
	return *this;
}

CompilationProcess& CompilationProcess::addIncludeDirectory(const std::string& dir){
	this->include_directories.push_back(dir);
	return *this;
}
CompilationProcess& CompilationProcess::addIncludeDirectories(const std::vector<std::string>& dirs){
	this->include_directories.insert(this->include_directories.end(), dirs.begin(), dirs.end());
	return *this;
}

CompilationProcess& CompilationProcess::addLibrary(const std::string& lib){
	this->libraries.push_back(lib);
	return *this;
}
CompilationProcess& CompilationProcess::addLibraries(const std::vector<std::string>& libs){
	this->libraries.insert(this->libraries.end(), libs.begin(), libs.end());
	return *this;
}

void CompilationProcess::compile(const std::vector<std::string>& files, const std::string& out){
	runCompiler(files, out, false);
}
void CompilationProcess::link(const std::vector<std::string>& files, const std::string& out){
	runCompiler(files, out, true);
}
void CompilationProcess::runCompiler(const std::vector<std::string>& files, const std::string& out, int link_objects){
	if(files.empty()){
		throw FetlangException("No files in compilation process");
	}

	if (compiler == "" || language == "")
	{
		std::string extension = FileUtil::extractFileExtension(files[0]);
		if(extension == "c"){
			setLanguage("c");
		}else if(extension == "c++"){
			setLanguage("c++");
		}else if(extension == "cpp"){
			setLanguage("c++");
		}else if(extension == "cc"){
			setLanguage("c++");
		}else if(extension == "rs"){
			setLanguage("rust");
		}else if(extension == "text" || extension == "txt" || extension == "o"
			|| extension == "out" || extension == "a"){
			return;
		}

		if (language == ""){
			throw FetlangException("Can't infer language based on extension: '"
				+extension+"' from fetish source file '"+files[0]+"'");
		}
	}

	// This is the process we're calling
	std::string command = compiler;

	// Using GNU extensions for C, because
	if(language == "c"){
		command += " -std=gnu99";
	}else if(language == "c++"){
		command += " -std=c++11";
	}

	if(!link_objects){
		if(language != "rust"){
			command += " -c";
		}else{
			command += " --emit link";
		}
	}

	// Optimize if needed
	if(optimization){
		command += " -O";
	}

	// Optimizations specific to GCC-compatible compilers
	if(language == "c" || language == "c++") {
		if(optimization) command += "2";
		if(link_time_optimization){
			command += " -flto";
		}
	}

	// Extra
	for(const auto& arg: extra_arguments){
		command += " "+QuoteUtil::quote(arg);
	}

	// add includes
	if(language != "rust"){
		for(const auto& dir : include_directories){
			command += " "+QuoteUtil::quote("-I"+dir);
		}
	}

	// add sources
	for(const auto& src : files){
		command += " "+QuoteUtil::quote(src);
	}

	// Output
	command += " -o "+QuoteUtil::quote(out);

	// Libraries
	if(link_objects){
		for(const auto& lib: libraries){
			command += " "+QuoteUtil::quote("-l"+lib);
		}
		// If we're on linux and not linking, just assume we need the math library
		#ifdef __linux__
			command += " -lm -ldl";
		#endif
			command += " -lresolv -lpthread";
	}

	// Silence rustc output
	if(language == "rust")
	{
		command += " 2>&1 | grep -v -E '^[[:space:]]*$|^note';if [[ $? != 1 ]]; then (echo \"rustc failed\" 1>&2 && exit 42);fi";

	}

	// Do the do
	FILE* process = popen(command.c_str(), "w");
	if(process == NULL || process <= static_cast<FILE*>(0)){
		throw FetlangException("Issue with popen in compilation process");
	}
	if(pclose(process)){
		throw FetlangException("Compilation process failed (errno "
			+std::to_string(errno)+"): " + command);
	}

}

