#ifndef FETLANG_CORE_CHAIN_H_
#define FETLANG_CORE_CHAIN_H_
#include "core/include/fraction.h"
#include <stdio.h>
#ifdef __cplusplus
extern "C"{
#endif

/* Chains (strings) are represented as doubly linked lists */
typedef struct Link {
	Fraction value;
	struct Link *prev;	/* Starts at NULL */
	struct Link *next;	/* Ends at NULL */
} Link;
typedef struct Chain {
	ChainLengthInt length;
	Link *start;
	Link *end;
} Chain;

/**
 * Construct chain
 *
 * Set defaults for chain: length to 0 and start to NULL
 *
 * @param chain The chain being constructed
 */
void init_chain(Chain * chain);

/**
 * Clear chain
 *
 * Free all links in chain and set start to NULL
 *
 * @param chain The chain being cleared
 */
void clear_chain(Chain * chain);

/**
 * Append a cstring to a chain
 *
 * Append each character of the cstring as a Link to the chain.
 *
 * @param chain The chain being modified
 * @param text The string being added to the chain
 */
void append_cstr_to_chain(Chain * chain, const char *text);

/**
 * Append fraction as single Link to chain
 *
 * @param chain The chain being modified
 * @param fraction The fraction being added to the chain
 */
void append_flink_to_chain(Chain * chain, Fraction fraction);

/**
 * Append fraction as string to chain
 *
 * Fraction is first converted into a string format. For example, 25/1 would be
 * converted to "twenty five" and then appended to the chain
 *
 * @param chain The chain being modified
 * @param fraction The fraction being added to the chain
 */
void append_fraction_to_chain(Chain * chain, Fraction fraction);

/**
 * Append the contents in one chain to another
 *
 * @param chain1 The chain being modified
 * @param chain2 The chain being appended to chain1
 */
void append_chain_to_chain(Chain * chain1, Chain chain2);

/**
 * Append the contents of a stream to a chain
 *
 * Each char is read from the stream and copied to the chain as a fraction/Link.
 *
 * @param chain The chain being modified
 * @param stream The stream whose contents are read
 */
void append_stream_to_chain(Chain * chain, FILE * stream);

/**
 * Erase stream contents
 *
 * @param stream The stream being cleared
 */
void clear_stream(FILE * stream);

/**
 * Append chain to stream
 *
 * Print each fraction of chain to the stream to be appended as a char 
 *
 * @param chain The chain being read
 * @param stream The stream being appended to
 */
void append_chain_to_stream(Chain chain, FILE * stream);

/**
 * Assign chain to stream
 *
 * Clear the stream, then call append_chain_to_stream
 *
 * @param chain The chain being read
 * @param stream The stream being copied to
 */
void chain_to_stream(Chain chain, FILE * stream);

/**
 * Convert chain to cstring
 *
 * Print each fraction of chain to the cstring buffer to be appended as a char 
 * This function is not safe. If buffer is too small to hold the contents of
 * chain, a segfault will occur
 *
 * @param chain The chain being read
 * @param buffer The cstring being appended to
 * @return The length of the buffer.
 */
int chain_to_cstr(Chain chain, char * buffer);

/**
 * Set file contents to chain's contents
 *
 * Open a file and set its contents to that of the chain's. As with other
 * functions, each fraction is converted to a char. An error will be thrown
 * upon any problem opening the file
 *
 * @param chain The chain being read
 * @param filename A chain holding the filename of the file we're opening
 */
void write_chain_to_file(Chain chain, Chain filename);

/**
 * Set chain contents to file's contents
 *
 * Open a file and read its contents to the chain's, replacing any previous
 * values(an assign, not append). As with other functions, each char is
 * converted to a fraction. An error will be thrown upon any problem opening
 * the file
 *
 * @param chain The chain being overwritten
 * @param filename A chain holding the filename of the file we're opening
 */
void read_file_to_chain(Chain * chain, Chain filename);

/**
 * Compare chains
 *
 * Check if chains are equivalent. Will return 0 if they are, and another value
 * if they are not.
 *
 * @param a The first chain
 * @param b The second chain
 * @return The comparison value
 */
int compare_chains(Chain a, Chain b);

/* Parse chain to construct fraction */
/**
 * Convert chain to fraction
 *
 * Parse chain to convert to a fraction value. Return 0/1 if chain is invalid.
 *
 * @param chain The chain being parsed
 * @return The fraction value of the chain
 */
Fraction chain_to_fraction(Chain chain);

Fraction get_next_byte_of_stream(FILE * file);

#ifdef __cplusplus
}
#endif
#endif
