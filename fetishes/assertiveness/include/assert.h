#pragma once
#ifndef FETLANG_ASSERT
#define FETLANG_ASSERT
/* Throw runtime_error if condition is not met */
void fetlang_assert(int condition, const char* message);
#endif
