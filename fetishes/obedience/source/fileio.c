#include "core/include/chain.h"
#include "core/include/error.h"
#include "obedience/include/fileio.h"
#include <stdlib.h>
#include <string.h>

void write_chain_to_file(Chain chain, Chain filename_as_chain)
{
	// Convert chain to char*
	const int max_filename_size = filename_as_chain.length;
	char * filename = (char*)malloc(sizeof(char*) * (max_filename_size + 1));
	if(filename == NULL)
	{
		runtime_error("Couldn't allocate memory for filename buffer in write_chain_to_file");
	}
	memset(filename, 0x00, max_filename_size);
	const int size = chain_to_cstr(filename_as_chain, filename);
	if(size > max_filename_size)
	{
		runtime_error("Size is ridiculous is write_chain_to_file");
	}

	// Open the file for writing
	FILE* fp = fopen(filename, "wb");
	if(fp == NULL)
	{
		runtime_error("Could not open file %s for writing", filename);
	}

	// Write
	Link * it = chain.start;
	while(it != NULL)
	{
		fputc((char)(it->value.num/it->value.den), fp);
		it = it->next;
	}

	fclose(fp);
}

void read_file_to_chain(Chain * chain, Chain filename_as_chain)
{
	// Convert chain to char*
	const int max_filename_size = filename_as_chain.length;
	char * filename = (char*)malloc(sizeof(char*) * (max_filename_size + 1));
	if(filename == NULL)
	{
		runtime_error("Couldn't allocate memory for filename buffer in read_chain_to_file");
	}
	memset(filename, 0x00, max_filename_size);
	const int size = chain_to_cstr(filename_as_chain, filename);
	if(size > max_filename_size)
	{
		runtime_error("Size is ridiculous is read_file_to_chain");
	}

	// Open the file for reading
	FILE* fp = fopen(filename, "rb");
	if(fp == NULL)
	{
		runtime_error("Could not open file %s for reading", filename);
	}

	// Read
	while(1)
	{
		char c = (char)fgetc(fp);
		if(c == EOF) break;
		append_flink_to_chain(chain, construct_fraction(c, 1));
	}

	fclose(fp);
	return;
}

FILE* open_file_as_stream(Chain filename, const char* mode)
{
	int max_size = sizeof(char)*(filename.length+1);
	char* buffer = (char*)malloc(max_size);
	if(filename.length == 0 || buffer == NULL)
	{
		runtime_error("Could not allocate buffer for file");
	}

	int actual_size = chain_to_cstr(filename, buffer);
	if(actual_size > filename.length || actual_size <= 0)
	{
		runtime_error("Something's terribly wrong in open_file_as_stream");
	}

	FILE* fp = fopen(buffer, mode);
	if(fp == NULL){
		perror("perror result: ");
		runtime_error("Could not open file %s", buffer);
	}
	return fp;
}
