#include "catch.hpp"
#include "core/include/chain.h"
#include "FileUtil.h"
#include <cstring>
#include <map>
#include <string>
#include <utility>

TEST_CASE("Chain Test", "[chain][core]"){
	const char*const sample_text = "A human has fallen from\n\t the surface world\n";
	const char*const sample_text2 = "Mama's scary; Mama hates\t\nyou\n";
	const char*const sample_text3 = "Welcome home, dear friends, how long we've all been waiting\n";
	const char*const sample_text4 = "I am the mastermind; he's my apprentice.\nYou're only still alive because I made a promise\n";

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
		stream = fopen(filename.c_str(), "w+b");
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
		append_chain_to_stream(chain, stream);
		clear_chain(&chain);
		REQUIRE(chain.length == 0);
		append_stream_to_chain(&chain, stream);
		REQUIRE(chain.length == strlen(sample_text2));
		// and again
		chain.start->value.num = 65;
		append_chain_to_stream(chain, stream);
		clear_chain(&chain);
		REQUIRE(chain.length == 0);
		append_stream_to_chain(&chain, stream);
		REQUIRE(chain.length == 2*strlen(sample_text2));
		REQUIRE(chain.start->value.num == sample_text2[0]);
		// Now assign
		clear_chain(&chain);
		REQUIRE(chain.length == 0);
		append_cstr_to_chain(&chain, sample_text3);
		REQUIRE(chain.length == strlen(sample_text3));
		chain_to_stream(chain, stream);
		clear_chain(&chain);
		REQUIRE(chain.length == 0);
		append_stream_to_chain(&chain, stream);
		REQUIRE(chain.length == strlen(sample_text3));


		// Cleanup
		fclose(stream);
		clear_chain(&chain);
	}

	SECTION("Random int test via /dev/urandom"){
		FILE * fp = fopen("/dev/urandom", "r");
		Fraction frac = get_next_byte_of_stream(fp);
		REQUIRE(frac.den == 1);
		frac = get_next_byte_of_stream(fp);
		REQUIRE(frac.den == 1);
	}

	SECTION("Chain/fraction test"){
		/* Check converting fractions to chains */
		Chain chain;
		init_chain(&chain);
		char buffer[100] = {0};

		std::map<std::pair<FractionInt, FractionInt>, const std::string> test_map = {
		{{100,1}, "one hundred"},
		{{25,1}, "twenty five"},
		{{-1,1}, "negative one"},
		{{0,1}, "zero"},
		{{123456789,1}, "one hundred and twenty three million, four hundred and fifty six thousand, seven hundred and eighty nine"},
		{{123456089,1}, "one hundred and twenty three million, four hundred and fifty six thousand, and eighty nine"},
		{{-123456089,1}, "negative one hundred and twenty three million, four hundred and fifty six thousand, and eighty nine"},
		};

		
		for(const auto& m : test_map){
			append_fraction_to_chain(&chain, construct_fraction(m.first.first, m.first.second));
			chain_to_cstr(chain, buffer);
			REQUIRE(0 == strcmp(buffer, m.second.c_str()));
			clear_chain(&chain);
			memset(buffer, 0x00, sizeof(buffer));
		}

	}
	SECTION("Fraction/chain test"){
		/* Check converting user input to fraction chains*/
		Chain input_chain;
		init_chain(&input_chain);
		Chain output_chain;
		init_chain(&output_chain);
		char buffer[100] = {0};

		std::map<const std::string, const std::string> test_map = {
		{"100", "one hundred"},
		{"100/1", "one hundred"},
		{"100/2", "fifty"},
		{"101/2", "one hundred and one over two"},
		{"2/2", "one"},
		{"2000/2000", "one"},
		{"-1", "negative one"},
		{"-101/3", "negative one hundred and one over three"},
		{"-1000000", "negative one million"},
		{"-1000000000", "negative one billion"},
		{"-1000000001", "negative one billion, and one"},
		};

		
		for(const auto& m : test_map){
			CAPTURE(m.first);
			CAPTURE(m.second);
			clear_chain(&input_chain);
			clear_chain(&output_chain);

			append_cstr_to_chain(&input_chain, m.first.c_str());
			append_fraction_to_chain(&output_chain, chain_to_fraction(input_chain));

			chain_to_cstr(output_chain, buffer);
			CAPTURE(buffer);
			REQUIRE(0 == strcmp(buffer, m.second.c_str()));
			memset(buffer, 0x00, sizeof(buffer));
		}

	}

}
