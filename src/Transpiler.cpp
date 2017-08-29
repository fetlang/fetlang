#include "Transpiler.h"
#include "FetlangManager.h"
#include "Fraction.h"
#include "FractionParser.h"
#include "QuoteUtil.h"
using namespace SyntaxTree;

static const std::string lho_temp_chain = "lho_temp_chain";
static const std::string rho_temp_chain = "rho_temp_chain";

// Replace text within a string
static void replaceText(std::string& str, const std::string& o, const
		std::string& n){
	std::string::size_type pos = 0u;
	while((pos = str.find(o, pos)) != std::string::npos){
		str.replace(pos, o.length(), n);
		pos += n.length();
	}
} 

std::string Transpiler::transpileBranch(Node& node){
	std::string code;

	// The only thing we expect on the "main" node is a keyphrase, not an
	// identifier, literal, or any other shit
	if(node.getToken().getCategory() != Token::KEYPHRASE_TOKEN){
		throw NodeException("Transpiler expected a keyphrase, but found `"+node.getToken().getValue()+"`", node);
	}

	// Now deal with any keyphrase that comes our way
	switch(node.getToken().getKeyphraseCategory()){
	case CONTROL_KEYPHRASE:
	{
		if(node.getToken().getValue() == "call safeword")
		{
			return "/* Safeword called */\nbreak;\n";
		}
		if(node.getToken().getValue() == "bind"){
			std::string pre_code="/* Bondage */\n";
			std::string post_code = "\n\n";

			// Perform some basic assertions
			if(node.getNumberOfChildren() < 1)
			{
				throw NodeException("Expected `bind` node to have at least one child", node);
			}
			if(node.getChild(0).getToken().getValue() != "to")
			{
				throw NodeException("Expected this node to be `to`", node.getChild(0));
			}
			if(node.getChild(0).getNumberOfChildren() != 2)
			{
				throw NodeException("Expected this `to` node to have exactly two children", node.getChild(0));
			}

			// Extract tokens, token types, and C representations
			Token lho = node.getChild(0).getChild(0).getToken();
			std::string lho_code = variables.get(lho.getValue()).getRawCode();
			Token rho = node.getChild(0).getChild(1).getToken();
			std::string rho_code;
			FetType lho_type = variables.get(lho.getValue()).getType();
			FetType rho_type;
			if(rho.getCategory() == Token::IDENTIFIER_TOKEN){
				rho_type = variables.get(rho.getValue()).getType();
				rho_code = variables.get(rho.getValue()).getCode();
				if(rho_type == STREAM_TYPE)
				{
					rho_code = rho_temp_chain;//"temp_chain_for_stream_for_bind"+std::to_string(rand());
					pre_code += "append_stream_to_chain(&"+rho_code+", "+variables.get(rho.getValue()).getCode()+");\n";
					post_code += "chain_to_stream("+rho_code+", "+variables.get(rho.getValue()).getCode()+");\n";
					post_code += "clear_chain(&"+rho_code+");\n";
				}
			}else if(rho.getCategory() == Token::CHAIN_LITERAL_TOKEN){
				rho_type = CHAIN_TYPE;
				rho_code = rho_temp_chain;
				pre_code += "append_cstr_to_chain(&"+rho_code+", ";
				pre_code += QuoteUtil::requote(rho.getValue())+");\n";
				post_code += "clear_chain(&"+rho_code+");\n";
			}else{
				throw TokenException("Expected this token to be identifier or chain literal", rho);
			}

			// Make sure things went correct
			if(lho_type != REFERENCE_TYPE || decayFetType(rho_type) != CHAIN_TYPE){
				throw NodeException("Incorrect lho/rho types for bind/to", node.getChild(0));
			}

			code = pre_code;
			code += lho_code+" = "+rho_code+".start;\n";
			code += "while("+lho_code+" != NULL){\n";

			// Transpile the middle stuff
			for(int i=1; i<node.getNumberOfChildren();i++){
				code += transpileBranch(node.getChild(i));
			}

			// And that's that!
			code += lho_code+"="+lho_code+"->next;";
			code += "}"+lho_code+"="+rho_code+".start;\n";
			code += post_code;


			break;
		// Eh, these are all basically the same thing 
		}else if(node.getToken().getValue() == "while" 
			|| node.getToken().getValue() == "until"
			|| node.getToken().getValue() == "if"
			|| node.getToken().getValue() == "otherwise")
		{

			if(node.getToken().getValue() == "while"){
				code+="while((";
			}else if(node.getToken().getValue() == "until"){
				code+="while(!(";
			}else if(node.getToken().getValue() == "if"){
				code+="if((";
			}else{
				code+="else";
			}

			if(node.getToken().getValue() != "otherwise"){	
				// Perform some basic assertions
				if(node.getNumberOfChildren() < 1)
				{
					throw NodeException("Expected this node to have at least one child", node);
				}
				if(node.getChild(0).getToken().getCategory() != Token::KEYPHRASE_TOKEN
					|| node.getChild(0).getToken().getKeyphraseCategory() != COMPARISON_OPERATOR_KEYPHRASE)
				{
					throw NodeException("Expected this node to be a comparison"
						" operator", node.getChild(0));
				}
				if(node.getChild(0).getNumberOfChildren() != 2)
				{
					throw NodeException("Expected this comparison operator node to"
						" have exactly two children", node.getChild(0));
				}

				ComparisonOperator op = manager.getComparisonOperator(node.getChild(0).getToken().getValue());
				Token lho = node.getChild(0).getChild(0).getToken();
				Token rho = node.getChild(0).getChild(1).getToken();

				// We've stated before: we can only have identifier tokens 
				if(lho.getCategory() != Token::IDENTIFIER_TOKEN){
					throw TokenException("Expected the LHO in a comparison operation to be an identifier token", lho);
				}
				if(rho.getCategory() != Token::IDENTIFIER_TOKEN){
					throw TokenException("Expected the RHO in a comparison operation to be an identifier token", rho);
				}
		
				FetType lho_type = variables.get(lho.getValue()).getType();
				FetType rho_type = variables.get(rho.getValue()).getType();

				std::string comparison_code = op.getCodeFor(lho_type, rho_type);
				std::string lho_code = variables.get(lho.getValue()).getCode();
				std::string rho_code = variables.get(rho.getValue()).getCode();
				replaceText(comparison_code, "LHO", lho_code);
				replaceText(comparison_code, "RHO", rho_code);

				code+=comparison_code + "))";
			}

			code+= "{\n";

			// Transpile the middle stuff
			int i=0;
			if(node.getToken().getValue() != "otherwise") i++;// Because of comparisons
			for(; i<node.getNumberOfChildren();i++){
				code += transpileBranch(node.getChild(i));
			}

			// And that's that!
			code += "}\n";


			break;
		}
		// FALL THROUGH
	}
	case OPERATOR_KEYPHRASE:
	{
		// Okay, it's an operator. That can only mean we're doing an operation (duh)
		// Perform assertions
		if(node.getNumberOfChildren() != 2){
			throw NodeException("Expected this node to have 2 children, but has "
				+std::to_string(node.getNumberOfChildren()),  node);
		}

		// Conveniences
		Operator op = manager.getOperator(node.getToken().getValue());
		Token lho = node.getChild(0).getToken();
		Token rho = node.getChild(1).getToken();

		// Initializations and cleanups for the operation
		std::string pre_code;
		std::string post_code;

		// Get types and codes
		FetType lho_type;
		std::string lho_code;
		FetType rho_type;
		std::string rho_code;
		// Get the rho type first so we can predict certain behavior along with
		// the lho
		if(rho.getCategory() == Token::IDENTIFIER_TOKEN){
			rho_type = variables.get(rho.getValue()).getType();
		}else if(rho.getCategory() == Token::FRACTION_LITERAL_TOKEN){
			rho_type = FRACTION_TYPE;
		}else if(rho.getCategory() == Token::CHAIN_LITERAL_TOKEN){
			rho_type = CHAIN_TYPE;
		}

		// Pretty sure lvalues can only be identifiers at this point
		if(lho.getCategory() == Token::IDENTIFIER_TOKEN){
			lho_type = variables.get(lho.getValue()).getType();
			// If operator is specifically asking for a stream, that's what it
			// gets. Otherwise we give it a chain
			if(lho_type == STREAM_TYPE && !op.hasCodeForExactly(STREAM_TYPE, rho_type)){
				// We have to convert the stream to a chain
				// Copy the stream to the temp chain
				// do the operation
				// Copy the temp chain to the stream
				lho_code = lho_temp_chain;
				pre_code += "/* Stream chain(lho) initialization */\n"
							"append_stream_to_chain(&"+lho_code+ ", "+
							variables.get(lho.getValue()).getCode()+");\n\n";
				post_code+= "/* Stream chain deconstruction */\n"
							"chain_to_stream("+lho_code+", "+variables.get(lho.getValue()).getCode()+");\n"
							"clear_chain(&"+lho_code+");\n\n";
			}else{
				lho_code = variables.get(lho.getValue()).getCode();
			}
		}else{
			throw TokenException("Transpiler encountered illegal operand", lho);
		}

		// Rvalues can be anything though
		if(rho.getCategory() == Token::IDENTIFIER_TOKEN){
			if(rho_type == STREAM_TYPE && !op.hasCodeForExactly(lho_type, STREAM_TYPE)){
				// We have to convert the stream to a chain
				rho_code = rho_temp_chain;
				pre_code += "/* Stream chain(rho) initialization */\n"
							"append_stream_to_chain(&"+rho_code+ ", "+
							variables.get(rho.getValue()).getCode()+");\n\n";
				post_code += "/* Stream chain(rho) deconstruction */\n"
							"clear_chain(&"+rho_code+");\n\n";
			}else{
				rho_code = variables.get(rho.getValue()).getCode();
			}
		}else if(rho.getCategory() == Token::FRACTION_LITERAL_TOKEN){
			// Convert
			Fraction fraction = FractionParser::stringToFraction(rho.getValue());
			rho_code = "construct_fraction("+std::to_string(fraction.getTop())+", "
						+std::to_string(fraction.getBottom())+")";
		}else if(rho.getCategory() == Token::CHAIN_LITERAL_TOKEN){
			// Chain literals have to be initialized and deinitialized 
			rho_code = rho_temp_chain;
			pre_code += "/* Chain literal initialization */\n"
						"append_cstr_to_chain(&"+rho_code+", "+QuoteUtil::requote(rho.getValue())+");\n\n";
			post_code += "/* Chain literal deconstruction */\n"
						"clear_chain(&"+rho_code+");\n\n";
		}else{
			throw TokenException("Transpiler encountered illegal operand", rho);
		}



		// Get the operation code
		if(!op.hasCodeFor(lho_type, rho_type)){
			throw NodeException("Operator can't work with operands of these "
				"types("+stringifyFetType(lho_type)+"/"+stringifyFetType(rho_type)+")",
					node);
		}
		std::string middle_code = op.getCodeFor(lho_type, rho_type)+";";
		replaceText(middle_code, "LHO", lho_code);
		replaceText(middle_code, "RHO", rho_code);

		// And add the code for the whole operation(including pre/post)
		code += pre_code+middle_code+"\n\n"+post_code;
		break;
	}
	default:
		throw NodeException("Transpiler doesn't know what to do with this node at this point in time", node);
	}

	return code;
}

std::string Transpiler::transpile(){
	std::string code = "/* Generated by Fetlang */\n#include <stdio.h>\n";
	// Include headers
	for(const Fetish& fetish: manager.getFetishes()){
		for(const std::string& header_path : fetish.getIncludes()){
			code+="#include "+QuoteUtil::quote(fetish.getName()+"/include/"+header_path)+"\n";
		}
	}

	// Head code
	code += std::string("int main(int argc, char* argv[]){\n")+
	"Chain "+lho_temp_chain+";init_chain(&"+lho_temp_chain+");\n"
	"Chain "+rho_temp_chain+";init_chain(&"+rho_temp_chain+");\n";

	// Declare Variables
	code += "/* Initializing variables */\n";
	for(const Variable& var:variables.getAll()){
		if(!var.needsConstructing())continue;
		switch(var.getType()){
		case FRACTION_TYPE:
		{
			code += "Fraction "+var.getCode()+";\n";
			code += var.getCode() + ".num = 0;\n";
			code += var.getCode() + ".den = 1;\n";
			break;
		}
		case CHAIN_TYPE:
		{
			code += "Chain "+var.getCode()+";\n";
			code += "init_chain(&"+var.getCode()+");\n";
			break;
		}
		case STREAM_TYPE:
		{
			code += "FILE* "+var.getCode()+" = NULL;\n";
			break;
		}
		case REFERENCE_TYPE:
		{
			code += "Link* "+var.getRawCode()+" = NULL;\n";
			break;
		}
		default:
			throw FetlangException("Transpiler unsure what to do with variable type given");
			break;
		}
	}
	code += "\n";
	code += manager.getPreloopCode();
	code += "do{\n";

	// User's code
	for(int i=0; i < tree.getNumberOfChildren();i++){
		code+=transpileBranch(tree.getChild(i));
	}

	// End "main 'loop'"
	code += "}while(0);\n";
	code += manager.getPostloopCode();

	// Free memory
	code += "/* Deconstructing variables */\n";
	for(const Variable& var:variables.getAll()){
		if(!var.needsConstructing())continue;
		if(var.getType() == CHAIN_TYPE){
			code += "clear_chain(&"+var.getCode()+");\n";
		}else if(var.getType() == STREAM_TYPE){
			code += "fclose("+var.getRawCode()+");\n";
		}
	}
	code += "\n";

	// Tail code
	code+= "clear_chain(&"+lho_temp_chain+");\n";
	code+= "clear_chain(&"+rho_temp_chain+");\n";
	code+= "/* Finished */\nreturn 0;\n}\n";

	return code;
}
