#include "catch.hpp"
#include "core/include/chain.h"
#include "FileUtil.h"
#include <cstring>
TEST_CASE("Chain Test", "[chain]"){
	const char*const sample_text = "A human has fallen from\n\t the surface world\n";
	const char*const sample_text2 = "Mama's scary; Mama hates\t\nyou\n";
	const char*const sample_text3 = "Welcome home, dear friends, how long we've all been waiting\n";

	SECTION("Chain/Cstring test"){
		Chain chain;
		init_chain(&chain);
		REQUIRE(chain.length == 0);
		append_cstr_to_chain(&chain, sample_text);
		REQUIRE(chain.length == strlen(sample_text));
		
		char * buffer = new char[chain.length];
		chain_to_cstr(chain, buffer);
		REQUIRE(0 == strcmp(buffer, sample_text));

		clear_chain(&chain);
		delete[] buffer;
	}

	SECTION("Chain/stream test"){
		std::string filename = "/tmp/bla.txt";
		FILE* stream = NULL;
		Chain chain;
		init_chain(&chain);
		REQUIRE(chain.length == 0);

		// Open the stream
		FileUtil::ensureFileDoesNotExist(filename);
		stream = fopen("/tmp/bla.txt", "w+b");
		REQUIRE_FALSE(stream == NULL);

		// Make sure stream is empty
		REQUIRE(chain.length == 0);
		append_stream_to_chain(&chain, stream);
		if(chain.length){
			CAPTURE(chain.start->value.num);
			CAPTURE(chain.start->value.den);
			REQUIRE(chain.length == 0);
		}

		// Write to it
		append_cstr_to_chain(&chain, sample_text2);
		REQUIRE(chain.length == strlen(sample_text2));
		chain_to_stream(chain, stream);
		clear_chain(&chain);
		REQUIRE(chain.length == 0);
		append_stream_to_chain(&chain, stream);
		REQUIRE(chain.length == strlen(sample_text2));

		// Cleanup
		fclose(stream);
		clear_chain(&chain);
	}

	SECTION("Std stream test"){
		Chain chain;
		FILE* stream = stderr;
		init_chain(&chain);
		append_stream_to_chain(&chain, stream);
		REQUIRE(chain.length == 0);


		append_cstr_to_chain(&chain, sample_text3);
		REQUIRE(chain.length == strlen(sample_text3));

		//chain_to_stream(chain, stream);
	
		clear_chain(&chain);
	}
}
