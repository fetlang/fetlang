#pragma once
#ifndef FETLANG_ASSERTIVENESS_ASSERT_H_
#define FETLANG_ASSERTIVENESS_ASSERT_H_

/**
 * Throw runtime_error if condition is not met
 *
 * If the condition is false, throw a runtime_error with the message `message`
 *
 * @param condition The condition to be evaluated
 * @param message The message given upon failure
 */
void fetlang_assert(int condition, const char* message);
#endif
