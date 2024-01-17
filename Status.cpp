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
#include "Status.h"

using namespace std;
namespace sdds {
	Status::Status(const char* desc, int code) {
		if (desc) {
			//delete[]description;
			description = new char[std::strlen(desc) + 1];
			std::strcpy(description, desc);
		}
		else {
			description = new char[0];
			clear();
		}
		statusCode = code;
	}

	Status::Status(const Status& other) {
		statusCode = other.statusCode;
		description = nullptr;
		if (other.description) {
			description = new char[std::strlen(other.description) + 1];
			std::strcpy(description, other.description);
		}
	}

	Status::~Status() {
		delete[]description;
	}

	//Deallocate description and setting a safe state
	Status& Status::clear() {
		delete[]description;
		description = nullptr;
		statusCode = 0;
		return *this;
	}

	//Asignment operator overload
	Status& Status::operator=(const char* desc) {
		if (desc) {
			delete[]description;
			description = new char[std::strlen(desc) + 1];
			std::strcpy(description, desc);
		}
		else {
			clear();
		}
		return *this;
	}

	Status& Status::operator=(int c) {
		if (c)
			statusCode = c;
		else
			statusCode = 0;
		return *this;
	}

	Status::operator int() const {
		return statusCode;
	}

	Status::operator const char* () const {
		return description ? description : "";
	}

	Status::operator bool() const {
		return description == nullptr;
	}

	std::ostream& operator<<(std::ostream& os, const Status& status) {
		if (!status) {
			if (status.statusCode != 0)
				os << "ERR#" << status.statusCode << ": ";

			os << status.description;

		}
		return os;
	}
}
