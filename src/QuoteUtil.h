#pragma once
#include <string>
#include "FetlangException.h"
// Namespace with functions to deal with quoting and unquoting strings
// That's pretty much it
namespace QuoteUtil{
	// Escape all non-trivial characters and place quotes around string
	std::string quote(const std::string&);
	
	// Remove quotes and unescape escaped characters
	// Throw QuoteUtilException if not surrounded by quotes
	// -or- if there is a bad escape sequence
	std::string unquote(const std::string&);

	// Call unquote then quote
	std::string requote(const std::string& s);

}
