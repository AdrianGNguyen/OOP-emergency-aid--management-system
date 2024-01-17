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
#include <sstream>
#include <cstring>
#include <iomanip>
#include "Perishable.h"


namespace sdds {

	// Default Constructor
	Perishable::Perishable() : Item() {
		m_handlingInstructions = nullptr;

	}

	// Copy Constructor
	Perishable::Perishable(const Perishable& other) : Item(other), m_expiryDate(other.m_expiryDate) {
		m_handlingInstructions = new char[0];
		setHandlingInstructions(other.m_handlingInstructions);
	}

	// Copy Assignment Operator
	Perishable& Perishable::operator=(const Perishable& other) {
		if (this != &other) {
			Item::operator=(other);
			m_expiryDate = other.m_expiryDate;
			setHandlingInstructions(other.m_handlingInstructions);
		}
		return *this;
	}

	// Destructor
	Perishable::~Perishable() {
		delete[] m_handlingInstructions;
	}

	//Return reference to expiry date

	const Date& Perishable::expiry() const {
		return m_expiryDate;
	}

	// readSku Override
	int Perishable::readSku(std::istream& istr) {
		std::cout << "SKU: ";

		while (true) {
			m_sku = ut.getint(10000, 39999);
			break;
		}
		return m_sku;
	}

	// Save Override
	std::ofstream& Perishable::save(std::ofstream& ofstr) const {
		if (*this) {
			Item::save(ofstr);
			ofstr << '\t';
			// Temporarily set the date to unformatted
			const_cast<Date&>(m_expiryDate).formatted(false);
			ofstr << (m_handlingInstructions ? m_handlingInstructions : "") << '\t' << m_expiryDate;

			// Reset the date back to formatted
			const_cast<Date&>(m_expiryDate).formatted(true);

		}
		return ofstr;
	}

	// Load Override
	std::ifstream& Perishable::load(std::ifstream& ifstr) {
		if (Item::load(ifstr)) {
			char tempInstructions[1001] = { 0 };
			ifstr.getline(tempInstructions, 1001, '\t');
			setHandlingInstructions(tempInstructions);
			ifstr >> m_expiryDate;
			ifstr.ignore();
			if (!ifstr) {
				Item::m_state = "Input file stream read (perishable) failed!";
			}
		}
		return ifstr;
	}

	// Display Override
	std::ostream& Perishable::display(std::ostream& ostr) const {
		if (!*this) {
			ostr << Item::m_state;
		}
		else {
			if (Item::m_linearFlag) {
				Item::display(ostr);
				ostr << (m_handlingInstructions && m_handlingInstructions[0] ? '*' : ' ');

				ostr << expiry();
			}
			else {
				ostr << "Perishable ";
				Item::display(ostr);
				ostr << "Expiry date: ";
				ostr << m_expiryDate;

				ostr << "\n";
				if (m_handlingInstructions && m_handlingInstructions[0]) {
					ostr << "Handling Instructions: " << m_handlingInstructions << "\n";
				}
			}
		}
		return ostr;
	}

	// read Override
	std::istream& Perishable::read(std::istream& istr) {
		Item::read(istr);

		delete[] m_handlingInstructions;
		m_handlingInstructions = nullptr;

		std::cout << "Expiry date (YYMMDD): ";
		istr >> m_expiryDate;

		std::cout << "Handling Instructions, ENTER to skip: ";


		istr.clear();            // clears state to allow further extraction
		istr.ignore(2000, '\n'); // clears the input buffer


		if (istr.peek() != '\n') {
			char tempInstructions[1001];
			istr.getline(tempInstructions, 1001);
			setHandlingInstructions(tempInstructions);
		}

		if (!istr) {
			Item::m_state = "Perishable console entry failed!";
		}

		return istr;
	}

	// Private Helper Method to Set Handling Instructions
	void Perishable::setHandlingInstructions(const char* instructions) {
		delete[] m_handlingInstructions;
		if (instructions && instructions[0]) {
			m_handlingInstructions = new char[strlen(instructions) + 1];
			strcpy(m_handlingInstructions, instructions);
		}
		else {
			m_handlingInstructions = nullptr;
		}
	}


	std::ostream& operator<<(std::ostream& os, const Perishable& perish) {
		return perish.display(os);
	}

	std::istream& operator>>(std::istream& is, Perishable& perish) {
		return perish.read(is);
	}
}