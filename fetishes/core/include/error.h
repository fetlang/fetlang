#ifndef ORGY_ERROR_H_
#define ORGY_ERROR_H_
/**
 * Show error message and exit
 *
 * Shows an error in the style of fprintf in red text, then exit with
 * EXIT_FAILURE
 *
 * @param msg The fprintf-style format string
 * @param ... Any values referenced by the format string
 */
void runtime_error(const char *msg, ...);
#endif
