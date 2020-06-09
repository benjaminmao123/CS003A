#pragma once

#include <string>

enum class ErrorState
{
	NONE,
	EXPECT_OPERAND,
	EXPECT_PARENTHESIS,
	EXPECT_OPERATOR,
	INVALID_INPUT,
	EXPECT_ARGUMENT_SEPARATOR,
	EXPECTED_ARGUMENT
};

namespace Error
{
	extern ErrorState errorState;

	std::string GetErrorMessage();
}