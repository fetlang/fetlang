#ifndef FETLANG_OBEDIENCE_FILEIO_H_
#define FETLANG_OBEDIENCE_FILEIO_H_
#include "core/include/chain.h"
#include "core/include/fraction.h"
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

/**
 * Open file as a stream
 *
 * Use a filename encoded in a chain to return a stream pointing to a file of
 * that name, with a particular mode.
 *
 * @param filename A chain holding the filename of the file we're opening
 * @param mode The fopen mode
 * @return The file as a stream
 */
FILE* open_file_as_stream(Chain filename, const char* mode);
#ifdef __cplusplus
}
#endif
#endif
