#include "assert.h"
#include "core/include/error.h"
void fetlang_assert(int condition, const char* message)
{
	// Keeping track of times called makes this a bit more useful
	static int times_called = 0;
	if(!condition)
	{
		runtime_error("assertion %d(zero indexed): %s", times_called, message);
	}
	
	times_called++;
}
