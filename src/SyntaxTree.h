#pragma once
#include <vector>
#include "FetlangManager.h"
#include "Token.h"
/* This represents an abstract syntax tree
   
   The initial node should always be a SyntaxTree::RootNode*/

namespace SyntaxTree{
	class Node {
		Token token;
		std::vector<Node> children;
	protected:
		// Prevent construction without data
		Node(){};
	public:
		// Set the data
		Node(Token);
		
		virtual ~Node(){};

		virtual Token& getToken();
		
		int getNumberOfChildren() const;
		Node& getChild(int);
		Node& addChild(const Node&);
		Token& getChildsToken(int);

		// Make a pretty graph of everything, like the unix/dos 'tree' command
		// Inherently recursive
		void display(int level = 0) const;

	};

	// Separate class for rootnode, because we don't want to do something
	// Like access a token that doesn't exist, or giving a monkey a shower
	class RootNode : public Node{
	public:
		RootNode(){};
		inline Token& getToken(){throw FetlangException("Can't get token of root node");}

	};
	
}

class NodeException: public FetlangException{
private:
	SyntaxTree::Node node;
public:
	NodeException(const std::string& msg, SyntaxTree::Node& node_arg):
		FetlangException(node_arg.getToken().getLine(), msg), node(node_arg){}
	SyntaxTree::Node getNode() const{return node;}

	void display() const override;
};
