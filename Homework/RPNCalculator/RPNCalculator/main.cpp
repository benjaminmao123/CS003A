/*
 * Author: Benjamin Mao
 * Project: RPN
 * Purpose: Entry point to the
 *      Calculator class.
 *
 * Notes: None.
 */

#include <iostream>

#include "ShuntingYard.h"

void Test();

int main()
{
    Test();

	return 0;
}

void Test()
{
	char menuInput = '\0';
	std::string input;
	ShuntingYard sy;

	while (menuInput != 'x')
	{
		std::cout << "[E]xpression E[x]it: ";
		std::cin >> menuInput;
		menuInput = tolower(menuInput);

		switch (menuInput)
		{
		case 'e':
			std::cin.ignore(1000, '\n');
			std::cout << "Enter an infix string: ";
			std::getline(std::cin, input);

			sy.SetInput(input);

			if (!sy.ParseExpression())
				std::cout << "Error: Enter a correct expression." << std::endl;
			else
				std::cout << sy;
		default:
			break;
		}

		std::cout << std::endl;
	}
}
