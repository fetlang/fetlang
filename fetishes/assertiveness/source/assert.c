#include "assert.h"
#include "core/include/error.h"
void fetlang_assert(int condition, const char* message)
{
	if(!condition)
	{
		runtime_error("%s", message);
	}
}
