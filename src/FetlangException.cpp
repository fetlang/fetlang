#include "FetlangException.h"

FetlangException::~FetlangException(){}
void FetlangException::displayLineAndMessage() const{
	std::cerr << "Error: ";
	if(getLine() > 0)
	{
		std::cerr << "line " << getLine() << ": ";
	}
	std::cerr << what() << "\n";
}

void FetlangException::display() const{
	displayLineAndMessage();
}
