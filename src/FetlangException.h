#pragma once
#include <stdexcept>
#include <iostream>

class FetlangException: public std::runtime_error {
private:
	int line;
	// Make base class constructor private
	// Cause we know if we don't Dagan will try to access it
	using std::runtime_error::runtime_error;
protected:
	inline void setLine(int l){ line = l;}

	// Used by the display() method and its overrides
	void displayLineAndMessage() const;

public:
	FetlangException(const std::string& message) : runtime_error(message) {line = -1;}
	FetlangException(int line_no, const std::string& message) : runtime_error(message) {line = line_no;}
	virtual ~FetlangException();
	inline int getLine() const{return line;}

	// Each exception displays in a unique way
	virtual void display() const;
};
