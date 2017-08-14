#include <iostream>
#include <string>
#include "FetlangManager.h"
#include "Token.h"
#include "SyntaxTree.h"
#include "Builder.h"
#include "thirdparty/args.hxx"


// Display error's what message, and the line number if it's valid
void showError(const FetlangException& e)
{
	std::cerr << "Error: ";
	if(e.getLine() > 0)
	{
		std::cerr<<"line "<<e.getLine()<<": ";
	}
	std::cerr << e.what()<<"\n";
}

int main(int argc, const char* argv[]){
	args::ArgumentParser parser("Fetlang transpiler", "");
	args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});
	args::Flag optimize(parser, "optimize", "Optimize binary", {'O'});
	args::Flag show_tokens(parser, "show tokens", "Show tokens", {'t'});
	args::Flag show_tree(parser, "show tree", "Show abstract syntax tree", {'T'});
	args::Flag no_compile(parser, "no compile", "Export as C file(don't compile)", {'c'});
	args::Flag scrub(parser, "scrub", "Clean /tmp/ fetlang folder", {'s'});
	args::Group required(parser, "", args::Group::Validators::AtLeastOne);
	args::Positional<std::string> input_file(required, "input file", "The source file");
	args::ValueFlag<std::string> output_file(parser, "output file", "The output file", {'o'});

	try
	{
		parser.ParseCLI(argc, argv);
	}
	// Display help menu
	catch(args::Help)
	{
		std::cout << parser;
		return 0;
	}
	// Some args related error

	catch (args::ParseError e)
	{
		std::cerr << e.what() << std::endl;
		std::cerr << parser;
		return 1;
	}
	// Some args related error
	catch (args::ValidationError e)
	{

		if(!input_file)
		{
			std::cerr<< "No input file" << std::endl;
			return 1;
		}
		std::cerr << e.what() << std::endl;
		std::cerr << parser;
		return 1;
	}

	// Now we can build
	try{
		Builder bob;
		if(no_compile) bob.setCompilation(false);
		if(show_tokens) bob.showTokens();
		if(show_tree) bob.showTree();
		if(optimize) bob.setOptimization();
		if(output_file) bob.setDestination(args::get(output_file));
		bob.setSource(args::get(input_file));
		bob.build();
	}catch(const TokenException& e){
		showError(e);
		std::cout<<"\t"<<e.getToken()<<"\n";
		return 1;
	}catch(const NodeException& e){
		showError(e);
		e.getNode().display();
		return 1;
	}catch(const FetlangException& e){
		showError(e);
		return 1;
	}catch(const std::exception& e){
		std::cout<<"Generic Exception: "<<e.what()<<"\n";
		return 1;
	}catch(...){
		std::cout<<"An unknown exception occured\n";
		return 1;
	}
	return 0;

}
	
