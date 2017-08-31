#include "catch.hpp"
#include "core/include/chain.h"
#include "obedience/include/fileio.h"
#include "FileUtil.h"
#include <cstring>

TEST_CASE("Fileio Test", "[stream][file][obedience]"){
	const char*const sample_text = "A human has fallen from\n\t the surface world\n";
	const char*const sample_text2 = "Mama's scary; Mama hates\t\nyou\n";
	const char*const sample_text3 = "Welcome home, dear friends, how long we've all been waiting\n";
	const char*const sample_text4 = "I am the mastermind; he's my apprentice.\nYou're only still alive because I made a promise\n";
	SECTION("FILE IO")
	{
		std::string filename = "/tmp/boop2.txt";
		FileUtil::setFileContents(filename, sample_text4);
		REQUIRE(FileUtil::getFileContents(filename) == sample_text4);

		Chain filename_as_chain;
		init_chain(&filename_as_chain);
		append_cstr_to_chain(&filename_as_chain, filename.c_str());

		Chain chain;
		init_chain(&chain);
		REQUIRE(chain.length == 0);

		FILE* stream = open_file_as_stream(filename_as_chain, "r+b");
		append_stream_to_chain(&chain, stream);
		REQUIRE(chain.length == strlen(sample_text4));
		clear_chain(&chain);
		append_cstr_to_chain(&chain, sample_text);
		append_chain_to_stream(chain, stream);
		clear_chain(&chain);
		append_stream_to_chain(&chain, stream);
		REQUIRE(chain.length== strlen(sample_text)+strlen(sample_text4));

		fclose(stream);
		clear_chain(&chain);
		clear_chain(&filename_as_chain);

	}

}
