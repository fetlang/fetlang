#pragma once
// Represents the four types in Fetlang
enum FetType {
// Internal use only - used when type is unknown
	UNKNOWN_TYPE,//Decays to jack shit

// Chains are lists of fractions, that often represent strings
	CHAIN_TYPE,

// Fractions are a number, with a denominator and numerator
	FRACTION_TYPE,

// Streams are a chain interface to file descriptors
	STREAM_TYPE,// Decays to chain

// References are a reference to a particular fraction, often one in a chain
	// as to iterate through said chain
	REFERENCE_TYPE,// Decays to fraction
};

// The two latter type decay into the more basic types
inline FetType decayFetType(FetType t){
	if(t == REFERENCE_TYPE)
		return FRACTION_TYPE;
	if(t == STREAM_TYPE)
		return CHAIN_TYPE;
	
	return t;
}

inline std::string stringifyFetType(FetType t){
	switch(t){
	case UNKNOWN_TYPE: 
		return "UNKNOWN_TYPE";
	case CHAIN_TYPE:
		return "CHAIN_TYPE";
	case FRACTION_TYPE:
		return "FRACTION_TYPE";
	case STREAM_TYPE:
		return "STREAM_TYPE";
	case REFERENCE_TYPE:
		return "IN_BONDAGE_TYPE";
	}

	return "{{type could not be determined - 100% a bug}}";
}


	
