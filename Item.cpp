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
#include "Item.h"
#include <iomanip>
#include <cstring>

namespace sdds {

	Item::Item() : m_price(0.0), m_quantityHave(0), m_neededQuantity(0), m_description(nullptr), m_linearFlag(false), m_state(), m_sku(0) {}

	Item::~Item() {
		clear();
	}

	Item::Item(const Item& other) : Item() {
		*this = other;
	}

	Item& Item::operator=(const Item& other) {
		if (this != &other) {
			clear();
			copy(other);
		}
		return *this;
	}

	int Item::qtyNeeded() const {
		return m_neededQuantity;
	}

	int Item::qty() const {
		return m_quantityHave;
	}

	Item::operator double() const {
		return m_price;
	}

	Item::operator bool() const {
		return m_description != nullptr && m_state;
	}

	int Item::operator-=(int qty) {
		m_quantityHave -= qty;
		return *this;
	}

	int Item::operator+=(int qty) {
		m_quantityHave += qty;
		return *this;
	}

	void Item::linear(bool isLinear) {
		m_linearFlag = isLinear;
	}

	bool Item::isLinear() {
		return m_linearFlag;
	}

	bool Item::operator==(int sku) const {
		return m_sku == sku;
	}

	bool Item::operator==(const char* description) const {
		return (m_description && description) ? (std::strstr(m_description, description) != nullptr) : false;
	}

	std::ostream& Item::display(std::ostream& os) const {
		if (!m_state) {
			os << m_state;
		}
		else if (m_linearFlag) {
			os << std::setw(5) << std::setfill('0') << m_sku << " | "
				<< std::setw(35) << std::setfill(' ') << std::left << (m_description ? std::string(m_description).substr(0, 35) : "") << " | "
				<< std::setw(4) << std::right << m_quantityHave << " | " << std::setw(4) << m_neededQuantity << " | "
				<< std::fixed << std::setprecision(2) << std::setw(7) << m_price << " |";

		}
		else {
			os << "AMA Item:" << std::endl;
			os << std::setw(5) << std::setfill('0') << m_sku << ": " << (m_description ? m_description : "") << std::endl;
			os << "Quantity Needed: " << m_neededQuantity << std::endl;
			os << "Quantity Available: " << m_quantityHave << std::endl;
			os << "Unit Price: $" << std::fixed << std::setprecision(2) << m_price << std::endl;
			os << "Needed Purchase Fund: $" << std::fixed << std::setprecision(2) << (m_neededQuantity - m_quantityHave) * m_price << std::endl;
		}
		return os;
	}

	int Item::readSku(std::istream& istr) {
		std::cout << "SKU: ";

		while (true) {
			m_sku = ut.getint(MINSKU, MAXSKU);
			break;
		}
		return m_sku;
	}

	std::istream& Item::read(std::istream& is) {
		clear();
		std::cout << "AMA Item:" << std::endl;
		std::cout << "SKU: " << m_sku << std::endl;


		std::cout << "Description: ";
		char temp[MAXNUMITEMS];
		is.getline(temp, MAXNUMITEMS, '\n');
		m_description = new char[strlen(temp) + 1];
		strcpy(m_description, temp);

		std::cout << "Quantity Needed: ";
		m_neededQuantity = ut.getint(1, MAXNUMITEMS);

		std::cout << "Quantity On Hand: ";
		m_quantityHave = ut.getint(0, m_neededQuantity);

		std::cout << "Unit Price: $";

		m_price = ut.getdouble(0.00, MAXNUMITEMS);

		if (!is) {
			m_state = "Invalid input";
			clear();
		}

		return is;
	}

	void Item::clear() {
		delete[] m_description;
		m_description = nullptr;
		m_state.clear();
	}

	void Item::copy(const Item& other) {
		m_price = other.m_price;
		m_quantityHave = other.m_quantityHave;
		m_neededQuantity = other.m_neededQuantity;

		if (other.m_description) {
			m_description = new char[strlen(other.m_description) + 1];
			strcpy(m_description, other.m_description);
		}
		else {
			delete[] m_description;
			m_description = nullptr;
		}

		m_linearFlag = other.m_linearFlag;
		m_state = other.m_state;
		m_sku = other.m_sku;
	}

	std::ofstream& Item::save(std::ofstream& ofstr) const {
		if (m_state) {
			ofstr << m_sku << '\t'
				<< m_description << '\t'
				<< m_quantityHave << '\t'
				<< m_neededQuantity << '\t'
				<< std::fixed << std::setprecision(2) << m_price;
		}
		return ofstr;
	}

	std::ifstream& Item::load(std::ifstream& ifstr) {
		clear();

		ifstr >> m_sku;
		if (!ifstr) {
			m_state = "Input file stream read failed!";
			return ifstr;
		}

		char temp[MAXNUMITEMS];
		ifstr.ignore();
		ifstr.getline(temp, MAXNUMITEMS, '\t');
		m_description = new char[strlen(temp) + 1];
		strcpy(m_description, temp);

		ifstr >> m_quantityHave >> m_neededQuantity >> m_price;
		if (!ifstr) {
			m_state = "Input file stream read failed!";
			return ifstr;
		}
		ifstr.ignore(1);
		return ifstr;
	}



	std::ostream& operator<<(std::ostream& os, const Item& item) {
		return item.display(os);
	}

	std::istream& operator>>(std::istream& is, Item& item) {
		return item.read(is);
	}

} // namespace sdds