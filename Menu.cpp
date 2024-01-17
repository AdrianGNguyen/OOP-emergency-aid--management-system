/*************************************************************************************

*

* Student Name : Gia Huy Nguyen

* Student ID  : 134821222

* Course/Section: OOP244/NBB 2237

*

* I have done all the coding by myself and only copied the code that my professor

* provided to complete my workshops and assignments.

*

**************************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Menu.h"
#include "Utils.h"

namespace sdds {
	Menu::Menu(const char* content) {
		if (content == nullptr || strlen(content) == 0) {
			//std::cerr << "Invalid Menu!" << std::endl;
			menuContent = nullptr;
			numOptions = 0;
		}
		else {
			// Check number of options
			int numTabs = 0;
			for (size_t i = 0; i < strlen(content); i++) {
				if (content[i] == '\t') {
					numTabs++;
				}
			}

			if (numTabs >= 15) {
				//std::cerr << "Invalid Menu! Number of options exceeds the limit." << std::endl;
				menuContent = nullptr;
				numOptions = 0;
			}
			else {
				menuContent = new char[0];
				ut.alocpy(menuContent, content);
				numOptions = numTabs + 1;
			}
		}
	}

	Menu::~Menu() {
		delete[] menuContent;
	}

	unsigned int Menu::run() const {
		int input;
		if (menuContent == nullptr) {
			std::cerr << "Invalid Menu!" << std::endl;
			return 0;
		}

		//temporary list holder
		char menuCopy[10000] = "\0";
		strcpy(menuCopy, menuContent);


		char* token = strtok(menuCopy, "\t");
		int optionNumber = 1;

		while (token != nullptr) {
			std::cout << optionNumber << "- " << token << std::endl;
			token = strtok(nullptr, "\t");
			optionNumber++;
		}

		std::cout << "---------------------------------" << std::endl;
		std::cout << "0- Exit" << std::endl;

		char choice[10] = "\0";
		while (true) {
			
			std::cout << "> ";
			input = ut.getint(0, numOptions, choice);
			break;
		}
		return input;
	}
}
