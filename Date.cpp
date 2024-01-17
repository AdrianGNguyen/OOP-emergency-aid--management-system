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
#include <iomanip>
#include <cstring> 
#include "Date.h"
#include "Utils.h"

using namespace std;
namespace sdds{
	bool Date::validate() {
		if (day == 0 && month == 0) {
			cout << "Invalid date value";
			return false;
		}

		// Check if year is within the valid range
		if (year < CURRENTYEAR || year > MAXYEAR) {
			m_state = "Invalid year in date";
			m_state = 1;
			return false;
		}

		// Check if month is within the valid range
		if (month < 1 || month > 12) {
			m_state = "Invalid month in date";
			m_state = 2;
			return false;
		}

		// Use Utils::daysOfMon to determine the maximum number of days in the current month and year
		int maxDaysInMonth = ut.daysOfMon(month, year);

		// Check if the day is within the valid range
		if (day < 1 || day > maxDaysInMonth) {
			m_state = "Invalid day in date";
			m_state = 3;
			return false;
		}

		// Clear the state if everything is valid
		m_state.clear();
		return true;
	}

	//uniquie ddate value
	int Date::uniqueDateValue() const {
		return year * 372 + month * 31 + day;
	}

	Date::Date() {
		// Use Utils to get the year, month, and day based on test mode
		int tyear, tmonth, tday;
		ut.getSystemDate(&tyear, &tmonth, &tday);

		// Set the date members based on the retrieved values
		year = tyear ;
		month = tmonth;
		day = tday;
		m_formatted = true;
	}

	Date::Date(int tyear, int tmonth, int tday) {
		// Validate the input and set the date members
		year = tyear;
		month = tmonth;
		day = tday;
		m_formatted = true;
	}

	bool Date::operator==(const Date& other) const {
		return uniqueDateValue() == other.uniqueDateValue();
	}

	bool Date::operator!=(const Date& other) const {
		return uniqueDateValue() != other.uniqueDateValue();
	}

	bool Date::operator<(const Date& other) const {
		return uniqueDateValue() < other.uniqueDateValue();
	}

	bool Date::operator>(const Date& other) const {
		return uniqueDateValue() > other.uniqueDateValue();
	}

	bool Date::operator<=(const Date& other) const {
		return uniqueDateValue() <= other.uniqueDateValue();
	}

	bool Date::operator>=(const Date& other) const {
		return uniqueDateValue() >= other.uniqueDateValue();
	}



	const Status& Date::state() const {
		return m_state;
	}

	Date& Date::formatted(bool flag) {
		m_formatted = flag;
		return *this; // Return a reference to the current object
	}

	Date::operator bool() const {
		return m_state;
	}

	std::ostream& Date::write(std::ostream& os) const {
		int tempYear;
		if (year > 100) {
			tempYear = year % 100;
		}
		else {
			tempYear = year;
		}
		if (m_formatted) {
			os << "20" << tempYear << "/";
			os << std::setw(2) << std::setfill('0') << month << "/";
			os << std::setw(2) << std::setfill('0') << day;
		}
		else {
			os << std::setw(2) << std::setfill('0') << year % 100;
			os << std::setw(2) << std::setfill('0') << month;
			os << std::setw(2) << std::setfill('0') << day;
		}
		return os;
	}

	// New read method
	std::istream& Date::read(std::istream& is) {
		int inputValue;
		is >> inputValue;

		if (inputValue < 100000) {
			if (inputValue > 100) {
				year = CURRENTYEAR;
				month = inputValue / 100;
				day = (inputValue / 100) % 100;
			}
			else if(inputValue == 0){
				year = CURRENTYEAR;
				month = 0;
				day = 0;
			}
			else {
				year = CURRENTYEAR;
				month = 13;
				day = 0;
			}
		}
		else {
			year = inputValue / 10000;
			month = (inputValue / 100) % 100;
			day = inputValue % 100;
		}

		if (!validate()) {
			is.setstate(std::ios::failbit);
		}

		return is;
	}

	// ... Your existing code ...

	// Helper insertion operator overload
	std::ostream& operator<<(std::ostream& os, const Date& date) {
		return date.write(os);
	}

	// Helper extraction operator overload
	std::istream& operator>>(std::istream& is, Date& date) {
		return date.read(is);
	}

}