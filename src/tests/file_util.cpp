#include "../thirdparty/catch.hpp"
#include "../FileUtil.h"
using namespace FileUtil;

TEST_CASE("extractFileExtension test", "[FileUtil]"){
	REQUIRE(extractFileExtension("hello.exe") == "exe");
	REQUIRE(extractFileExtension(".exe") == "exe");
	REQUIRE(extractFileExtension("exe") == "");
	REQUIRE(extractFileExtension("") == "");
	REQUIRE(extractFileExtension(".exe.") == "");
	REQUIRE(extractFileExtension(".") == "");
	REQUIRE(extractFileExtension("...") == "");
}

TEST_CASE("FileUtil function-integration test"){
	const std::string path = "BumblesMoonSpeciallyNow_test";
	const std::string contents_export =
	"Ooh I'm black and I'm proud\r\n"
	"I'm black, they can't keep me down\t\r\n";
	const std::string contents_import =
	"Ooh I'm black and I'm proud\n"
	"I'm black, they can't keep me down\t\n";

	REQUIRE_NOTHROW(ensureDirectoryDoesNotExist(path));
	REQUIRE_THROWS(getFilesInDirectory(path));

	// Create it
	REQUIRE_NOTHROW(ensureDirectoryExists(path));
	REQUIRE_THROWS(getFileContents(path));
	REQUIRE(getFilesInDirectory(path).empty());

	// Create a file
	REQUIRE_THROWS(getFileContents(path+"/boop"));
	REQUIRE_NOTHROW(ensureFileDoesNotExist(path+"/boop"));
	REQUIRE_FALSE(fileExists(path+"/boop"));
	REQUIRE_NOTHROW(setFileContents(path+"/boop", contents_export));
	REQUIRE(fileExists(path+"/boop"));
	REQUIRE(getParentPath(path+"/boop") == path);
	REQUIRE(getFilesInDirectory(path).size() == 1);
	REQUIRE(getFilesInDirectory(path)[0] == "boop");
	REQUIRE(getFileContents(path+"/boop") == contents_import);
	REQUIRE(contents_import != contents_export);

	// Destroy it
	ensureFileDoesNotExist(path+"/boop");
	REQUIRE_THROWS(destroyFile(path+"/boop"));

	// Destroy the rest of the directory
	REQUIRE_NOTHROW(destroyDirectory(path));
	REQUIRE_THROWS(destroyDirectory(path));
	REQUIRE_THROWS(destroyFile(path+"/boop"));

	// This is hard to test, since we basically need it to test it
	REQUIRE(getExecutableParentPath() == getExecutableParentPath());
	REQUIRE(getExecutableParentPath() != "");

	// Make sure we don't accidently open a directory as a file somehow
	REQUIRE_THROWS(getFileContents("."));

}

