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
#ifndef SDDS_AIDMAN_H
#define SDDS_AIDMAN_H
#include "Menu.h"
#include "Utils.h"
#include "iProduct.h"
#include "Perishable.h"
#include "Item.h"

namespace sdds {

	const int sdds_max_num_items = 100;
	const int MAXCHAR = 9999;


	class AidMan {
		char* filename; 
		Menu mainMenu;   
		iProduct* items[sdds_max_num_items];  // Array of iProduct Pointers
		int numItems;  // Number of iProduct Items

		// Private method
		unsigned int menu() const;  // Function to display the main menu and get user selection.

	public:
		// Constructor
		AidMan(const char* filename);
		AidMan();


		// Destructor
		~AidMan();


		// Rule of Three: Disable copy constructor and assignment operator
		AidMan(const AidMan& other) = delete;
		AidMan& operator=(const AidMan& other) = delete;

		// Public method to run the application
		void run();

		bool load();

		void save();

		void deallocate();

		int list(const char* sub_desc);

		int search(int sku) const;

		void remove(int index);

		void shipItems();
	};
}

#endif // !SDDS_UTILS_H