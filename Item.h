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
#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include "Status.h"
#include "iProduct.h"
//#include "Perishable.h"

namespace sdds {

    int const MAXNUMITEMS = 9999;
    int const MINSKU = 40000;
    int const MAXSKU = 99999;

    class Item : public iProduct {
    private:
        double m_price;
        int m_quantityHave;
        int m_neededQuantity;
        char* m_description;
        

    protected:
        bool m_linearFlag;
        Status m_state;
        int m_sku;

    public:
        Item();
        ~Item();
        Item(const Item& other);
        Item& operator=(const Item& other);

        // iProduct overrides
        int qtyNeeded() const;
        int qty() const;
        operator double() const;
        operator bool() const;
        int operator-=(int qty);
        int operator+=(int qty);
        void linear(bool isLinear);
        bool isLinear();
        bool operator==(int sku) const;
        bool operator==(const char* description) const;

        // Save, Load, and ReadSku methods
        std::ofstream& save(std::ofstream& ofstr) const;
        std::ifstream& load(std::ifstream& ifstr);
        int readSku(std::istream& istr);

        // Insertion and extraction operators
        std::ostream& display(std::ostream& os) const;
        std::istream& read(std::istream& is);

        // Other member functions
        void clear();

    private:
        void copy(const Item& other);
    };

    std::ostream& operator<<(std::ostream& os, const Item& item);
    std::istream& operator>>(std::istream& is, Item& item);

} // namespace sdds

#endif // ITEM_H