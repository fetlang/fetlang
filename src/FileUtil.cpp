#include "FileUtil.h"
#include "FetlangException.h"
#include "thirdparty/whereami.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>

namespace FileUtil {

std::vector<std::string> getFilesInDirectory(const std::string& directory_name){
	std::vector<std::string> filenames;
	fs::path directory(directory_name);

	fs::directory_iterator end_iterator;

	if(!fs::exists(directory)){
		throw FetlangException(directory_name + " does not exist");
	}
	if(!fs::is_directory(directory)){
		throw FetlangException(directory_name + " is not a directory");
	}

	for(fs::directory_iterator it(directory); it!=end_iterator; it++){
		if(fs::is_regular_file(it->path())){
			filenames.push_back(it->path().filename().string());
		}
	}
	std::sort(filenames.begin(), filenames.end());
	return filenames;
}

std::vector<std::string> getDirectoriesInDirectory(const std::string& directory_name){
	std::vector<std::string> filenames;
	fs::path directory(directory_name);

	fs::directory_iterator end_iterator;

	if(!fs::exists(directory)){
		throw FetlangException(directory_name + " does not exist");
	}
	if(!fs::is_directory(directory)){
		throw FetlangException(directory_name + " is not a directory");
	}

	for(fs::directory_iterator it(directory); it!=end_iterator; it++){
		if(fs::is_directory(it->path())){
			filenames.push_back(it->path().filename().string());
		}
	}
	return filenames;
}

std::string extractFileExtension(const std::string& filename){
	for(int i=filename.size()-1; i>=0; i--){
		if(filename[i] == '.'){
			return filename.substr(i+1);
		}
	}
	return "";
}

std::string getFileContents(const std::string& filename){
	if(!fileExists(filename)){
		throw FetlangException("No such file "+filename);
	}
	std::ifstream fp(filename);
	std::string contents;
	std::stringstream buffer;
	if(fp.fail()){
		throw FetlangException("Could not open file "+filename);
	}
	buffer << fp.rdbuf();
	contents = buffer.str();
	fp.close();
	std::string new_contents = "";
	for(const char& i : contents){
		if(i!='\r')new_contents+=i;
	}
	return new_contents;
}

void setFileContents(const std::string& path, const std::string& contents){
	const fs::path fp = path;
	if(fs::exists(fp)){
		if(!fs::is_regular_file(fp)){
			throw FetlangException("Entity "+path+" exists, but is not a regular file. Refusing to overwrite.");
		}
	}
	std::ofstream fp2(path);
	if(fp2.bad()){
		throw FetlangException("Could not create file at "+path);
	}
	fp2 << contents;
	fp2.close();
}

void ensureDirectoryExists(const std::string& path){
	const fs::path directory = path;
	if(fs::exists(directory)){
		if(fs::is_directory(directory)){
			// all good
			return;
		}
		throw FetlangException("Entity "+path+" exists, but is not a directory. Refusing to overwrite.");
	}else{
		if(!fs::create_directories(directory)){
			throw FetlangException("Could not create directory at "+path);
		}
	}
}

void ensureFileExists(const std::string& path){
	const fs::path fp = path;
	if(fs::exists(fp)){
		if(!fs::is_regular_file(fp)){
			throw FetlangException("Entity "+path+" exists, but is not a regular file. Refusing to overwrite.");
		}
	}else{
		std::ofstream fp2(path);
		if(fp2.bad()){
			throw FetlangException("Could not create file at "+path);
		}
		fp2.close();
	}
}

bool fileExists(const std::string& path){
	const fs::path fp = path;
	if(fs::exists(fp)){
		if(!fs::is_regular_file(fp)){
			throw FetlangException("Entity "+path+" exists, but is not a regular file");
		}
		return true;
	}
	return false;
}

void ensureFileDoesNotExist(const std::string& path){
	const fs::path fp = path;
	if(fs::exists(fp)){
		// Destroy it >:(
		if(!fs::is_regular_file(fp)){
			throw FetlangException("Can't destroy file "+path+" because it is a non-file entity");
		}
		fs::remove(fp);
	}

	// Work is done for you
}
	

void destroyFile(const std::string& path){
	if(!fs::exists(fs::path(path))){
		throw FetlangException("Can't destroy file "+path+" because it doesn't exist");
	}
	ensureFileDoesNotExist(path);
}

void ensureDirectoryDoesNotExist(const std::string& path){
	fs::path dir = path;
	if(fs::exists(dir)){
		// Destroy it >:(
		if(!fs::is_directory(dir)){
			throw FetlangException("Can't destroy directory "+path+" because it is a non-directory entity");
		}
		fs::remove_all(dir);
	}

	// Work is done for you
}
	

void destroyDirectory(const std::string& path){
	if(!fs::exists(fs::path(path))){
		throw FetlangException("Can't destroy directory "+path+" because it doesn't exist");
	}
	ensureDirectoryDoesNotExist(path);
}

std::string getParentPath(std::string path){
	if(path == ""){
		throw FetlangException("Can't get parent path of empty string");
	}
	while(path.back() == '/'){
		if(path != "/"){
			path.pop_back();
		}
	}

	const fs::path fp = path;
	if(!fs::exists(fp)){
		throw FetlangException("Can't get parent directory of path that doesn't exist"+path);
	}
	return fp.parent_path().string();
	
}

std::string getExecutableParentPath(){
	constexpr int buffer_size = 256;
	char buffer[buffer_size];
	int size;
	wai_getExecutablePath(buffer, buffer_size, &size);
	return std::string(buffer, size);
}
}
