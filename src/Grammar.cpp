#include "Grammar.h"


bool Grammar::allowsLeft(OperandType left) const{
	return allowed_leftward_operands.find(left) !=
		allowed_leftward_operands.end();
}

bool Grammar::allowsRight(OperandType right) const{
	return allowed_rightward_operands.find(right) !=
		allowed_rightward_operands.end();
}

void Grammar::addAllowedLeftwardOperands(const std::vector<OperandType>& operand_types){
	for(const auto& operand_type : operand_types){
		allowed_leftward_operands.insert(operand_type);
	}
}

void Grammar::addAllowedRightwardOperands(const std::vector<OperandType>& operand_types){
	for(const auto& operand_type : operand_types){
		allowed_rightward_operands.insert(operand_type);
	}
}

void Grammar::setReversed(bool reverse){
	this->is_reversed = reverse;
}

