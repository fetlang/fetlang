#ifndef FETLANG_FILEIO_H_
#define FETLANG_FILEIO_H_
#include "core/include/chain.h"
#ifdef __cplusplus
extern "C"{
#endif
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

// Experimental
FILE* open_file_as_stream(Chain filename, const char* mode);
#ifdef __cplusplus
}
#endif
#endif
