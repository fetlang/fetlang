#include "assert.h"
#include "core/error.h"
void fetlang_assert(int condition)
{
	if(!condition)
	{
		runtime_error("assertion failed");
	}
}
