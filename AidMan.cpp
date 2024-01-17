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
#include <cstring>
#include <iomanip>
#include "AidMan.h"

using namespace std;
namespace sdds {
	AidMan::AidMan(const char* filename) : filename(nullptr), mainMenu("List Items\tAdd Item\tRemove Item\tUpdate Quantity\tSort\tShip Items\tNew/Open Aid Database") {
		// Copy the filename if it is not nullptr
		if (filename != nullptr) {
			this->filename = new char[strlen(filename) + 1];
			strcpy(this->filename, filename);
		}
	}

	AidMan::AidMan() : filename(nullptr), mainMenu("List Items\tAdd Item\tRemove Item\tUpdate Quantity\tSort\tShip Items\tNew/Open Aid Database") {}

	// Destructor
	AidMan::~AidMan() {
		// Save data before deallocating
		deallocate();
	}

	// Private method to display the main menu and get user selection
	unsigned int AidMan::menu() const {
		int year, month, day;
		ut.getSystemDate(&year, &month, &day);
		// Display title and filename

		std::cout << "Aid Management System" << std::endl;
		std::cout << "Date: " << year << "/" << month << "/0" << day << std::endl;
		std::cout << "Data file: " << (filename != nullptr ? filename : "No file") << std::endl;
		std::cout << "---------------------------------" << std::endl;

		// Run the main menu and return user selection
		return mainMenu.run();
	}

	// Public method to run the application
	void AidMan::run() {
		char* string = nullptr; //temporary string
		unsigned int selection;
		char description[MAXCHAR];
		int countR; //count returned
		int index;
		int choice;
		int quantity;

		do {
			int rowNum; //row input for list item
			//char c;
			selection = menu();  // Display menu and get user selection

			// Insert logic to change selection to 7 if no database is open
			if (selection != 0 && filename == nullptr && selection != 7) {
				selection = 7;
			}
			// For now, just print the task name
			switch (selection) {
			case 1:


				std::cout << "\n****List Items****\n";
				list(string);
				std::cout << "Enter row number to display details or <ENTER> to continue:\n> ";


				if (std::cin.peek() == '\n') {
					cin.ignore(1);

				}
				else if (cin >> rowNum) {
					for (int i = 0; i < numItems; i++) {
						if ((i + 1) == rowNum) {
							items[i]->linear(false);
							items[i]->display(std::cout);
							cout << endl;
						}

					}
				}

				cout << endl;
				break;


			case 2:


				if (numItems > sdds_max_num_items) {
					cout << "Database full!" << endl;
				}
				else {
					int input;
					std::cout << "\n****Add Item****\n";
					cout << "1- Perishable" << endl << "2- Non-Perishable" << endl << "-----------------" << endl << "0- Exit" << endl << "> ";
					cin >> input;
					if (input == 1) {
						items[numItems] = new Perishable();

					}
					else if (input == 2) {
						items[numItems] = new Item();

					}
					else {
						cout << "Aborted\n";
						break;
					}

					int tempSKU = 0; //placeholder for the search
					int valid;
					tempSKU = items[numItems]->readSku(std::cin);
					valid = search(tempSKU);
					if (valid != -1) {
						cout << "Sku: " << tempSKU << " is already in the system, try updating quantity instead.\n";
					}
					else {
						cin >> *items[numItems];
						numItems++;
					}
					cout << endl;
				}
				break;


			case 3:



				cout << "\n****Remove Item****\n";

				description[0] = { '\0' };
				int sku;


				cout << "Item description: ";
				//std::cin.ignore();  
				cin.getline(description, MAXCHAR);

				// List items containing the description
				countR = list(description);

				if (countR > 0) {
					cout << "Enter SKU: ";
					cin >> sku;

					// Search for the SKU
					index = search(sku);

					if (index != -1) {

						cout << "Following item will be removed: \n";
						// Display the item
						items[index]->linear(false);
						items[index]->display(std::cout);
						cout << "\nAre you sure?" << endl;
						cout << "1- Yes!" << endl;
						cout << "0- Exit" << endl;
						cout << "> ";


						cin >> choice;

						if (choice == 1) {
							remove(index);
							cout << "Item removed!\n\n";
						}
						else {
							cout << "Aborted!" << endl;
						}
					}
					else {
						cout << "SKU not found!" << endl;
					}
				}

				break;



			case 4:

				std::cout << "\n****Update Quantity****\n";
				description[0] = { '\0' };
				cout << "Item description: ";

				cin.getline(description, MAXCHAR);
				countR = list(description);

				if (countR > 0) {
					cout << "Enter SKU: ";
					cin >> sku;

					// Search for the SKU
					index = search(sku);
					cout << "1- Add" << endl << "2- Reduce" << endl << "0- Exit" << endl << "> ";

					cin >> choice;

					if (choice == 1) {
						if (items[index]->qtyNeeded() == items[index]->qty()) {
							cout << "Quantity Needed already fulfilled!\n\n";
						}
						else {
							cout << "Quantity to add: ";
							quantity = ut.getint(1, items[index]->qtyNeeded());
							*items[index] += quantity;
							cout << quantity << " items added!\n\n";
						}
					}
					if (choice == 2) {
						if (items[index]->qty() == 0) {
							cout << "Quaintity on hand is zero!\n\n";
						}
						else {
							cout << "Quantity to reduce: ";
							quantity = ut.getint(1, items[index]->qtyNeeded());
							*items[index] -= quantity;
							cout << quantity << " items removed!\n\n";
						}
					}
					if (choice == 0) {
						cout << "Aborted!\n\n";
					}

				}



				break;


			case 5:
				std::cout << "\n****Sort****\n";
				for (int i = 0; i < numItems - 1; ++i) {
					for (int j = 0; j < numItems - i - 1; ++j) {
						// Calculate the difference between quantity needed and quantity on hand
						int diff1 = items[j]->qtyNeeded() - items[j]->qty();
						int diff2 = items[j + 1]->qtyNeeded() - items[j + 1]->qty();

						// Swap if the difference is in descending order
						if (diff1 < diff2) {
							iProduct* temp = items[j];
							items[j] = items[j + 1];
							items[j + 1] = temp;
						}
					}
				}
				cout << "Sort completed!\n\n";
				break;

			case 6:
				std::cout << "\n****Ship Items****\n";
				shipItems();
				break;
			case 7:
				std::cout << "\n****New/Open Aid Database****\n";
				// Load data from file

				std::cout << "Enter file name: ";
				char newFilename[100];
				//std::cin.ignore();  // Clear the newline character from the buffer
				std::cin.getline(newFilename, 100);
				delete[] filename;
				filename = new char[strlen(newFilename) + 1];
				strcpy(filename, newFilename);
				load();

				break;
			default:
				save();
				// Do nothing for invalid selection
				break;
			}


		} while (selection != 0);

		// User selected 0, exit the program
		std::cout << "Exiting Program!\n";
	}


	// MS51

	// Private method to save data records to a file
	void AidMan::save() {
		if (filename != nullptr) {
			std::ofstream file(filename);
			if (file.is_open()) {
				for (int i = 0; i < numItems; ++i) {
					//ile << endl;
					items[i]->save(file);
					file << endl;
					//cout << endl;
				}
			}
		}
	}

	// Private method to deallocate memory
	void AidMan::deallocate() {
		for (int i = 0; i < numItems; ++i) {
			delete items[i];
			items[i] = nullptr;
		}
		numItems = 0;
		delete[] filename;
		filename = nullptr;
	}

	bool AidMan::load() {
		//deallocate(); // Deallocate existing resources before loading new data
		int i = 0;
		if (filename != nullptr) {
			std::ifstream file(filename);
			if (file.is_open()) {
				while (file) {


					if (file.fail()) {
						file.clear();
						break;
					}


					if (file.peek() == '1' || file.peek() == '2') {
						items[i] = new Perishable();

					}
					else if (file.peek() == '4' || file.peek() == '5') {
						items[i] = new Item();

					}
					else {
						//end of file
						break;
					}
					items[i]->load(file);
					// Read the rest of the line to move to the next record
					//file.ignore(2000, '\n');
					i++;
				}

				std::cout << i << " records loaded!\n\n";
				numItems = i;
				file.close();
				return true;
			}
			else {
				std::cout << "Failed to open " << filename << " for reading!" << std::endl;
				std::cout << "Would you like to create a new data file?" << std::endl;
				std::cout << "1- Yes!" << std::endl;
				std::cout << "0- Exit" << std::endl;
				int choice;
				std::cin >> choice;

				if (choice == 1) {
					std::ofstream newFile(filename);
					newFile.close();
					return true;
				}
				else {
					return false;
				}
			}
		}
		return false;
	}

	int AidMan::list(const char* sub_desc) {
		int count = 0;
		if (sub_desc != nullptr)
		{
			for (int i = 0; i < numItems; ++i) {
				if (*items[i] == sub_desc) {

					++count;
				}
			}
			if (count == 0) {
				cout << "No matches found!\n\n";
				return count;
			}
		}

		cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
		cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;


		for (int i = 0; i < numItems; ++i) {
			// Check if sub_desc is nullptr or if the item's description contains sub_desc

			if (sub_desc == nullptr) {
				cout << setw(4) << setfill(' ') << i + 1 << " | ";
				items[i]->linear(true);
				items[i]->display(std::cout);
				++count;
				cout << endl;
			}
			else {
				if (*items[i] == sub_desc) {
					cout << setw(4) << setfill(' ') << i + 1 << " | ";
					items[i]->linear(true);
					items[i]->display(std::cout);
					++count;
					cout << endl;
				}
			}
		}
		cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;


		if (count == 0) {
			cout << "The list is empty!" << endl;
		}

		//cout << endl;
		return count;
	}

	// Search function
	int AidMan::search(int sku) const {
		for (int i = 0; i < numItems; ++i) {
			if (*items[i] == sku) {
				return i; // SKU found, return index
			}
		}
		return -1; // SKU not found
	}

	// AidMan.cpp
	void AidMan::remove(int index) {
		if (index >= 0 && index < numItems) {
			delete items[index];

			// Shift items to the left
			for (int i = index; i < numItems - 1; ++i) {
				items[i] = items[i + 1];
			}

			// Update the count
			--numItems;


		}
	}

	// Ship function
	void AidMan::shipItems() {
		std::ofstream shippingFile("shippingOrder.txt");
		int j = 1;
		if (shippingFile.is_open()) {
			int year, month, day;
			ut.getSystemDate(&year, &month, &day);

			shippingFile << "Shipping Order, Date: " << year << "/" << month << "/0" << day << std::endl;
			shippingFile << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << std::endl;
			shippingFile << "-----+-------+-------------------------------------+------+------+---------+-----------" << std::endl;

			int shippedItemsCount = 0;

			for (int i = 0; i < numItems; ++i) {
				if (items[i]->qty() == items[i]->qtyNeeded()) {
					
					shippingFile << setw(4) << setfill(' ') << j << " | ";
					++j;
					// Print the item in the linear format into the file
					items[i]->linear(true);
					items[i]->display(shippingFile);
					shippingFile << std::endl;

					// Remove the item from the iProduct Pointers array
					remove(i);
				
					++shippedItemsCount;
					--i; // Adjust the loop counter after removing an item
				}
			}

			shippingFile << "-----+-------+-------------------------------------+------+------+---------+-----------" << std::endl;
			shippingFile.close();

			std::cout << "Shipping Order for " << shippedItemsCount << " times saved!\n\n";
		}
		else {
			std::cout << "Failed to open shippingOrder.txt for writing!\n";
		}
	}
}