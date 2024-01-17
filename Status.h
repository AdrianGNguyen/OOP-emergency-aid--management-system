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
#ifndef SDDS_STATUS_H
#define SDDS_STATUS_H
#include "Utils.h"

namespace sdds {
	class Status {
		char* description;
		int statusCode;
	public:
		Status(const char* desc = nullptr, int code = 0);
		Status(const Status& other);
		~Status();
		Status& clear();
		Status& operator=(const char* desc);
		Status& operator=(int c);
		operator int() const;
		operator const char* () const;
		operator bool() const;
		friend std::ostream& operator<<(std::ostream& os, const Status& status);
	};

}

#endif

