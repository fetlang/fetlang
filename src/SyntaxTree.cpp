#include "SyntaxTree.h"
using namespace SyntaxTree;

Node::Node(Token token) {
	this->token = token;
}

Token& Node::getToken() {
	return this->token;
}

int Node::getNumberOfChildren() const{
	return children.size();
}

Node& Node::getChild(int child_id) {
	if(child_id >= getNumberOfChildren()){
		throw FetlangException("Child id "+std::to_string(child_id)+" is out of bounds");
	}

	return children[child_id];
}

Node& Node::addChild(const Node& node){
	children.push_back(node);
	return children.back();
}

Token& Node::getChildsToken(int child_id){
	return getChild(child_id).getToken();
}

void Node::display(int level) const{
	//display data
	for(int i=0; i<level; i++){
		std::cout<<"\t";
	}
	if(level == 0){
		if(token.isNullToken()){
			std::cout<<"{Root}"<<"\n";
		}else{
			std::cout<<"Root:"<<token<<"\n";
		}
	}else{
		std::cout<<token<<"\n";
	}


	//next
	for(const auto& child: children){
		child.display(level+1);
	}
}

void NodeException::display() const{
	displayLineAndMessage();
	node.display();
}
