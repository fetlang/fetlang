#ifndef ORGY_CHAIN_H_
#define ORGY_CHAIN_H_
#include "fraction.h"
#include <stdio.h>

/* Chains (strings) are represented as doubly linked lists */
typedef struct Link {
	Fraction value;
	struct Link *prev;	/* Starts at NULL */
	struct Link *next;	/* Ends at NULL */
} Link;
typedef struct OrgyChainStructure {
	ChainLengthInt length;
	Link *start;
	Link *end;
} Chain;

/* Set defaults for chain, length to 0 and start to NULL */
void init_chain(Chain * chain);

/* Delete all links in chain and set start to NULL */
void clear_chain(Chain * chain);

/* Append a cstring to a chain */
void append_cstr_to_chain(Chain * chain, const char *text);

/* Literally append fraction as is to chain */
void append_flink_to_chain(Chain * chain, Fraction fraction);

/* Convert and append fraction to chain */
void append_fraction_to_chain(Chain * chain, Fraction fraction);

/* Append another chain to chain(hard copy) */
void append_chain_to_chain(Chain * chain1, Chain chain2);

/* Read each char from stream as fraction */
void append_stream_to_chain(Chain * chain, FILE * stream);

/* Print each fraction to stream as char */
void chain_to_stream(Chain chain, FILE * stream);

/* Convert chain to c_string */
int chain_to_cstr(Chain chain, char * buffer);

/* File IO */
void write_chain_to_file(Chain chain, Chain filename);
void read_file_to_chain(Chain * chain, Chain filename);

/* Compare chain: 0 if they are the same, 1 if not */
int compare_chains(Chain a, Chain b);

/* Parse chain to construct fraction */
Fraction chain_to_fraction(Chain chain);
#endif
