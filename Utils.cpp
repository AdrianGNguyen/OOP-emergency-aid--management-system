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
#include <ctime>
#include <iomanip>
#include "Utils.h"

using namespace std;
namespace sdds {
	Utils ut;
	void Utils::testMode(bool testmode) {
		m_testMode = testmode;
	}
	void Utils::getSystemDate(int* year, int* mon, int* day) {
		if (m_testMode) {
			if (day) *day = sdds_testDay;
			if (mon) *mon = sdds_testMon;
			if (year) *year = sdds_testYear;
		}
		else {
			if (day) *day = 23;
			if (mon) *mon = 10;
			if (year) *year = 2023;
			/*	time_t t = std::time(NULL);
				tm lt = *localtime(&t);
				if (day) *day = lt.tm_mday;
				if (mon) *mon = lt.tm_mon + 1;
				if (year) *year = lt.tm_year + 1900;*/
		}
	}
	int Utils::daysOfMon(int month, int year)const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int mon = (month >= 1 && month <= 12 ? month : 13) - 1;
		return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	void Utils::alocpy(char*& destination, const char* source) {
		// Delete the destination dynamic array and set it to null
		delete[] destination;
		destination = nullptr;

		if (source) {
			// Allocate memory in the destination to the size of the source
			destination = new char[std::strlen(source) + 1];

			// Copy the source into it
			std::strcpy(destination, source);
		}
	}

	//int Utils::getint(const char* prompt = nullptr)
	//If the prompt is not null, it will display it. Then it performs a foolproof entry of an integer.
	//If the user enters an invalid integer it will display "Invalid Integer, retry: " and will not let the user leave the function until a valid integer is entered.

	int Utils::getint(const char* prompt) {

		int input;
		char buffer;
		bool flag = false;

		// displayed before the entry as a prompt
		if (prompt) cout << prompt;

		do {
			// If the user enters an invalid integer, display the ERROR message and clear buffer
			cin >> input;

			if (!cin) {
				cout << "Invalid Integer, retry: ";
				cin.clear();
				cin.ignore(BUFFER_SIZE, '\n');
			}
			else {
				// If the user enters any character after a valid integer, display the ERROR message and clear buffer
				cin.get(buffer);

				if (buffer != '\n') {
					cout << "Enter only an integer, try again: ";
					cin.clear();
					cin.ignore(BUFFER_SIZE, '\n');
				}
				else flag = true;
			}
		} while (!flag);

		return input;
	}
	int Utils::getint(int min, int max, const char* prompt, const char* errMes) {
		if (prompt) {
			cout << prompt;
		}

		int input = getint(prompt);

		while (input < min || input > max) {
			if (errMes) {
				cout << errMes << ", retry: ";
			}
			else {
				cout << "Value out of range [" << min << "<=val<=" << max << "]: ";
			}

			input = getint(prompt);
		}

		return input;

	}

	double Utils::getdouble(const char* prompt) {

		double input;
		char buffer;
		bool flag = false;

		// displayed before the entry as a prompt
		if (prompt) cout << prompt;

		do {
			// If the user enters an invalid integer, display the ERROR message and clear buffer
			cin >> input;

			if (!cin) {
				cout << "Invalid number, retry: ";
				cin.clear();
				cin.ignore(BUFFER_SIZE, '\n');
			}
			else {
				// If the user enters any character after a valid integer, display the ERROR message and clear buffer
				cin.get(buffer);

				if (buffer != '\n') {
					cout << "Enter only an integer, try again: ";
					cin.clear();
					cin.ignore(BUFFER_SIZE, '\n');
				}
				else flag = true;
			}
		} while (!flag);

		return input;
	}
	double Utils::getdouble(double min, double max, const char* prompt, const char* errMes) {
		if (prompt) {
			cout << prompt;
		}

		double input = getdouble(prompt);

		while (input < min || input > max) {
			if (errMes) {
				cout << errMes << ", retry: ";
			}
			else {
				std::cout << "Value out of range [" << std::fixed << std::setprecision(2) << min
					<< "<=val<=" << max << "]: ";
			}

			input = getdouble(prompt);
		}

		return input;

	}

}