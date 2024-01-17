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
#include "iProduct.h"

namespace sdds {

    // Insertion operator overload
    std::ostream& operator<<(std::ostream& os, const iProduct& product) {
        return product.display(os);
    }

    // Extraction operator overload
    std::istream& operator>>(std::istream& is, iProduct& product) {
        return product.read(is);
    }

}