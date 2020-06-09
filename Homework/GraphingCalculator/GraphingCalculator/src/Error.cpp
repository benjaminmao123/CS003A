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
		case ErrorState::INVALID_OPERAND:
			message = "INVALID OPERAND";
			break;
		case ErrorState::INVALID_OPERATOR:
			message = "INVALID OPERATOR";
			break;
		case ErrorState::INVALID_PARENTHESIS:
			message = "INVALID PARENTHESIS";
			break;
		case ErrorState::INVALID_ARGUMENT_SEPARATOR:
			message = "INVALID ARGUMENT SEPARATOR";
		default:
			break;
		}

		return message;
	}
}