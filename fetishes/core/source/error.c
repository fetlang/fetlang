#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "error.h"

/* Allow for red, bold highlighting on *NIX systems */
#if defined(unix) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
#define BOLDRED(x) ("\x1B[1;31m" x "\x1B[0m")
#else
/* Non-*NIX system */
#warning NON NIX SYSTEMS NOT TESTED YET
#define BOLDRED(x) (x)
#endif

/* Allow for red, bold highlighting on Windows systems */
#ifdef __WIN32
#include <windows.h>
/* TODO: Do */
#define WINDOWS_SET_BOLDRED ;
#define WINDOWS_SET_NORMAL ;
#else
#define WINDOWS_SET_BOLDRED ;
#define WINDOWS_SET_NORMAL ;
#endif


void runtime_error(const char *msg, ...)
{
	va_list args;

	/* Error header */
	WINDOWS_SET_BOLDRED;
	fprintf(stderr, BOLDRED("runtime error: "));
	WINDOWS_SET_NORMAL;

	/* Print msg and args to stderr, printf style */
	va_start(args, msg);
	vfprintf(stderr, msg, args);
	va_end(args);

	/* New line and exit */
	fprintf(stderr, "\n");
	exit(EXIT_FAILURE);
}
