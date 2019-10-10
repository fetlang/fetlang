#pragma once
#include <string>
#include <vector>

namespace FileUtil{
	// Return list of files in a directory
	// throw an exception if directory doesn't exist
	// Non-recursive
	std::vector<std::string> getFilesInDirectory(const std::string& directory);
	// Same but with directories
	std::vector<std::string> getDirectoriesInDirectory(const std::string& directory);

	// Get file contents as ASCII
	// Throw exception if it DNE
	std::string getFileContents(const std::string& path);
	// Or set the file contents as ASCII (no carriage return bullshit)
	void setFileContents(const std::string& path, const std::string& contents);

	// Return file extension. input: "bla.cpp", return: "cpp"
	std::string extractFileExtension(const std::string& filename);

	// Recursively create a directory if it does not exist. If this isn't
	// possible, throw an exception
	void ensureDirectoryExists(const std::string& path);

	// Similar to above, but create a file instead if it doesn't exist
	void ensureFileExists(const std::string& path);

	// Check if file exists
	bool fileExists(const std::string& path);

	// Recursively destroy directory, but throw exception if it doesn't exist
	void destroyDirectory(const std::string& path);

	// Destroy a file, throw an exception if it doesn't exist
	void destroyFile(const std::string& path);

	// Same as the previous two, but destruction
	// Recursively destroy directory if it exists
	void ensureDirectoryDoesNotExist(const std::string& path);

	// And same but with file. Not recursive though, because that doesn't make
	// sense in this context
	void ensureFileDoesNotExist(const std::string& path);

	// Get the path of the parent element
	std::string getParentPath(std::string path);

	// Get the parent path of the executable
	std::string getExecutableParentPath();


}
