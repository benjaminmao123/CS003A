#pragma once

#include <string>

enum class ErrorState
{
	NONE,
	INVALID_OPERAND,
	INVALID_PARENTHESIS,
	INVALID_OPERATOR,
	INVALID_INPUT,
	INVALID_ARGUMENT_SEPARATOR
};

namespace Error
{
	extern ErrorState errorState;

	std::string GetErrorMessage();
}