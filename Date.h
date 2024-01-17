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
#ifndef SDDS_DATE_H
#define SDDS_DATE_H
#include "Status.h"


namespace sdds {
	int const MAXYEAR = 30;
	int const CURRENTYEAR = 23;
	class Date {
		
		int year;
		int month;
		int day;
		
	
		Status m_state;
		bool m_formatted;
		bool validate();
		int uniqueDateValue() const;

	public:
		Date();
		Date(int year, int month, int day);

		//operator overloads for comparison.
		bool operator==(const Date& other) const;
		bool operator!=(const Date& other) const;
		bool operator<(const Date& other) const;
		bool operator>(const Date& other) const;
		bool operator<=(const Date& other) const;
		bool operator>=(const Date& other) const;

		const Status& state() const; // State accessor
		Date& formatted(bool flag); // Formatted modifier
		operator bool() const; // Bool conversion overload

		std::ostream& write(std::ostream& os) const;
		std::istream& read(std::istream& is);

		friend std::ostream& operator<<(std::ostream& os, const Date& date);
		friend std::istream& operator>>(std::istream& is, Date& date);
	};

	
}

#endif 
