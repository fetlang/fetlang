#include "obedience/include/filemanip.h"
#include "core/include/error.h"

#include <string>
extern "C" int32_t rs_touch_file(const char* filename);

extern "C" void touch_file(Chain chain_as_filename){
	// Get filename as string
	std::string filename; 
	{
		Link * link = chain_as_filename.start;
		while(link != NULL)
		{
			filename+=link->value.num;
			link = link->next;
		}
		if(filename == "")
		{
			runtime_error("Can not have empty filename");
		}
	}

	// Touch it ;)
	if(rs_touch_file(filename.c_str()) < 0)
	{
		runtime_error("Could not touch file %s", filename.c_str());
	}

}




