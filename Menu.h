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
#ifndef SDDS_MENU_H
#define SDDS_MENU_H
namespace sdds {
    class Menu {
        char* menuContent;
        int numOptions;

        
    public:
        Menu(const char* content);

        //rule of three
        ~Menu();
        Menu(const Menu& other) = delete;
        Menu& operator=(const Menu& other) = delete;

        //run method
        unsigned int run() const;
    };
    
}

#endif // !SDDS_UTILS_H