#pragma once
#include <vector>
#include <string>
/*
	Represents a single command compilation or linkage.

	E.g: cc -c -I../include source1.c -o bla.o

	This class method-chains

	So you can do:
		object.clear().setCompiler(...).addArguments(...).compile()
*/

class CompilationProcess{
	// Literal compiler command used
	std::string compiler;

	std::string language;

	// Do we optimize?
	bool optimization;
	bool link_time_optimization;

	// Extra args
	std::vector<std::string> extra_arguments;
	
	std::vector<std::string> include_directories;
	std::vector<std::string> libraries;

	void runCompiler(const std::vector<std::string>& files, const std::string& out, int link_objects);
public:
	CompilationProcess();
	CompilationProcess& clear();

	// runCompiler without linking
	void compile(const std::vector<std::string>& sources, const std::string& out) ;

	// runCompiler with linking
	void link(const std::vector<std::string>& objects, const std::string& out) ;

	// Optimize
	CompilationProcess& setOptimization(bool do_optimize=true);
	CompilationProcess& setLinkTimeOptimization(bool do_optimize=true);

	// Change actual compiler use
	CompilationProcess& setCompiler(const std::string&);
	// These infer each other if one is not set
	CompilationProcess& setLanguage(const std::string&);

	// Add any sort of argument(misc)
	CompilationProcess&  addArgument(const std::string&);
	CompilationProcess& addArguments(const std::vector<std::string>&);

	// Specifically add include directory
	CompilationProcess& addIncludeDirectory(const std::string&);
	CompilationProcess& addIncludeDirectories(const std::vector<std::string>&);
	// Or libs(don't add 'm' if not on Linux)
	CompilationProcess& addLibrary(const std::string&);
	CompilationProcess& addLibraries(const std::vector<std::string>&);
};
