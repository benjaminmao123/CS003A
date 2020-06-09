#include "Error.h"

namespace Error
{
	ErrorState errorState = ErrorState::NONE;

	std::string GetErrorMessage()
	{
		std::string message;

		switch (errorState)
		{
		case ErrorState::NONE:
			message = "NONE";
			break;
		case ErrorState::INVALID_INPUT:
			message = "INVALID INPUT";
			break;
		case ErrorState::EXPECT_OPERAND:
			message = "EXPECTED OPERAND";
			break;
		case ErrorState::EXPECT_OPERATOR:
			message = "EXPECTED OPERATOR";
			break;
		case ErrorState::EXPECT_PARENTHESIS:
			message = "EXPECTED PARENTHESIS";
			break;
		case ErrorState::EXPECT_ARGUMENT_SEPARATOR:
			message = "EXPECTED ARGUMENT SEPARATOR";
			break;
		case ErrorState::EXPECTED_ARGUMENT:
			message = "EXPECTED ARGUMENT";
			break;
		default:
			break;
		}

		return message;
	}
}