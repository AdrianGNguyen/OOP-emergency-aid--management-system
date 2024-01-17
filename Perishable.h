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
#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H

#include "Item.h"
#include "Date.h"
#include <iostream>

namespace sdds {

    class Perishable : public Item {
        Date m_expiryDate;
        char* m_handlingInstructions;

    public:
        // Default Constructor
        Perishable();

        // Copy Constructor
        Perishable(const Perishable& other);

        // Copy Assignment Operator
        Perishable& operator=(const Perishable& other);

        // Destructor
        ~Perishable();

        // Bool conversion

        // Expiry Date Query Change HERE!!!!!
        //int expiry() const;
        const Date& expiry() const;

        // readSku Override
        int readSku(std::istream& istr);

        // Save Override
        std::ofstream& save(std::ofstream& ofstr) const;

        // Load Override
        std::ifstream& load(std::ifstream& ifstr);

        // Display Override
        std::ostream& display(std::ostream& ostr) const;

        // read Override
        std::istream& read(std::istream& istr);

    private:
        // Private Helper Method to Set Handling Instructions
        void setHandlingInstructions(const char* instructions);
    };

    std::ostream& operator<<(std::ostream& os, const Perishable& perish);
    std::istream& operator>>(std::istream& is, Perishable& perish);
}

#endif // SDDS_PERISHABLE_H