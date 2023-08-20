/* Citation and Sources...
Final Project Milestone 5
Module: PosApp
Filename: PosApp.cpp
Version: 1.0
Author: Sang Hyon Jeon
Revision History
-----------------------------------------------------------
Date        Reason
2023/04/16  Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <cstring>
#include "PosApp.h"
#include "Utils.h"
#include "Bill.h"

using namespace std;

namespace sdds {
	/***** PRIVATE FUNCTIONS FOR MENU OPTIONS *****/
	// Prints a title for an action.
	void PosApp::printActionTitle(const char* title) const {
		cout << ">>>> ";
		cout << left << setw(72) << setfill('.') << title;
		cout << endl;
	}

	// Loads all the records of the data file into the Iptr array (m_items).
	void PosApp::loadRecs() {
		printActionTitle("Loading Items");

		// Open the file for reading.
		ifstream input(m_filename);

		// If the file doesn't exist, create it and close.
		if (!input) {
			ofstream output(m_filename);
			output.close();
		}

		// Clear the current items in the PosApp class.
		for (int i = 0; i < m_noOfItems; i++) {
			delete m_items[i];
			m_items[i] = nullptr;
		}
		m_noOfItems = 0;

		// Read and load item records from the file.
		char itemType;
		bool isReading = true;

		while (input && m_noOfItems < MAX_NO_ITEMS && isReading) {
			input >> itemType;

			if (!input) {
				isReading = false;
			}
			else {
				// Create a new Perishable or NonPerishable item based on the itemType.
				if (itemType == 'P') {
					m_items[m_noOfItems] = new Perishable();
				}
				else if (itemType == 'N') {
					m_items[m_noOfItems] = new NonPerishable();
				}

				// Read the item details and add it to the m_items array.
				if (m_items[m_noOfItems]) {
					input.ignore();
					input >> *m_items[m_noOfItems];
					m_noOfItems++;
				}
			}
		}

		// Close the file.
		input.close();
	}

	// Saves all the items pointed by Iptr array (m_items) in the data file.
	void PosApp::saveRecs() {
		printActionTitle("Saving Data");

		// Open the file for writing.
		ofstream output(m_filename);

		// Loop through the m_items array and save each item to the file.
		for (int i = 0; i < m_noOfItems; i++) {
			output << *m_items[i] << endl;
		}

		// Close the file.
		output.close();
	}

	// Allows the user to select an Item by entering the row number.
	int PosApp::selectItem() {
		int value;
		int minValue = 1;
		int maxValue = m_noOfItems;

		bool isInteger = false;
		int rowNumber = -1;

		printActionTitle("Item Selection by row number");
		cout << "Press <ENTER> to start...." << endl;
		cin.ignore(1000, '\n');

		// Display the list of items without showing the total asset.
		listItems(false);

		cout << "Enter the row number: ";
		cin >> value;

		// Keep looping until the user enters a valid row number.
		do {
			if (cin) {
				isInteger = true;
			}

			if (!isInteger) {
				invalidInput();
				cin >> value;
			}
			else {
				rowNumber = getInt(minValue, maxValue, value);
				if (rowNumber == -1) {
					cout << "Enter the row number: ";
					cin >> value;
				}
			}
		} while (!isInteger || rowNumber == -1);

		// Return the validated user's row number choice.
		return rowNumber;
	}

	// Receives the SKU and returns the address of the item if matching SKU is found.
	Item* PosApp::search(const char* sku) {
		Item* foundItem = nullptr;

		// Loop through all items in the array.
		for (int i = 0; i < m_noOfItems && !foundItem; i++) {
			// If the current item's SKU matches the given SKU, store its address.
			if (strcmp(m_items[i]->sku(), sku) == 0) {
				foundItem = m_items[i];
			}
		}

		// Return the address of the found item or nullptr if not found.
		return foundItem;
	}


	/***** MENU OPTIONS *****/
	// Displays the menu and returns the user's choice.
	int PosApp::menu() {
		int value;
		int minValue = MIN_MENU_OPTION;
		int maxValue = MAX_MENU_OPTION;

		bool isInteger = false;
		int validInt = -1;

		// Display the menu options.
		cout << "The Sene-Store" << endl;
		cout << "1- List items" << endl;
		cout << "2- Add item" << endl;
		cout << "3- Remove item" << endl;
		cout << "4- Stock item" << endl;
		cout << "5- POS" << endl;
		cout << "0- exit program" << endl;
		cout << "> ";
		cin >> value;

		// Keep asking for input until a valid option is selected.
		do {
			if (cin) {
				isInteger = true;
			}

			if (!isInteger) {
				invalidInput();
				cin >> value;
			}
			else {
				validInt = getInt(minValue, maxValue, value);
				if (validInt == -1) {
					cout << "> ";
					cin >> value;
				}
			}
		} while (!isInteger || validInt == -1);

		// Return the user's selected menu option.
		return validInt;
	}

	// Sorts all the items in Iptr array (m_items), and prints each item information.
	void PosApp::listItems(bool showTotalAsset) {
		printActionTitle("Listing Items");

		// Sort all the Items in m_items array based on their name in ascending order using selection sort
		for (int i = 0; i < m_noOfItems - 1; i++) {
			int minIndex = i;
			for (int j = i + 1; j < m_noOfItems; j++) {
				if (compareItemsByName(m_items[j], m_items[minIndex])) {
					minIndex = j;
				}
			}
			if (minIndex != i) {
				Item* temp = m_items[i];
				m_items[i] = m_items[minIndex];
				m_items[minIndex] = temp;
			}
		}

		// Print the Title/Header of the list
		cout << " Row | SKU    | Item Name          | Price |TX |Qty |   Total | Expiry Date |\n";
		cout << "-----|--------|--------------------|-------|---|----|---------|-------------|\n";

		// Loop through the items up to m_noOfItems and display the row and the Items in POS_LIST format
		double totalAsset = 0.0;
		for (int i = 0; i < m_noOfItems; ++i) {
			if (m_items[i] != nullptr) {
				cout << setw(4) << setfill(' ') << right << i + 1 << " | ";
				m_items[i]->displayType(POS_LIST);
				m_items[i]->write(cout);
				cout << endl;
				totalAsset += m_items[i]->cost() * m_items[i]->quantity();
			}
		}

		cout << "-----^--------^--------------------^-------^---^----^---------^-------------^" << endl;

		// Print the footer and the total asset only if showTotalAsset is true
		if (showTotalAsset) {
			cout << setw(49) << setfill(' ') << right << "Total Asset: $  | " << setw(13) << right << fixed << setprecision(2) << totalAsset << "|" << endl;
			cout << "-----------------------------------------------^--------------^" << endl << endl;
		}
	}

	// Adds a new item to the inventory.
	void PosApp::addItem() {
		printActionTitle("Adding Item to the store");

		// Check if there is space for a new item
		if (m_noOfItems < MAX_NO_ITEMS) {
			char perishable;
			cout << "Is the Item perishable? (Y)es/(N)o: ";
			cin >> perishable;

			// Create a new item based on user input (perishable or non-perishable)
			Item* newItem = nullptr;
			if (tolower(perishable) == 'y') {
				newItem = new Perishable();
			}
			else {
				newItem = new NonPerishable();
			}

			// Loop until a valid item is entered
			bool isValid = false;
			do {
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> *newItem;

				if (!(*newItem)) {
					newItem->write(cout);
					cout << ", try again..." << endl;
				}
				else {
					isValid = true;
				}
			} while (!isValid);

			// Add the new item to the array and increment the item count
			m_items[m_noOfItems] = newItem;
			m_noOfItems++;

			printActionTitle("DONE!");
		}
		else {
			cout << "Inventory Full!" << endl;
		}

		return;
	}

	// Removes an item selected by the user.
	void PosApp::removeItem() {
		int rowNumber;

		printActionTitle("Remove Item");

		// Get the row number of the item to be removed
		rowNumber = selectItem();

		// Check if a valid row number is returned
		if (rowNumber > 0) {
			// Convert row number to index in the m_items array
			int index = rowNumber - 1;

			// Show the item about to be removed in POS_FROM format
			cout << "Removing...." << endl;
			m_items[index]->displayType(POS_FORM);
			m_items[index]->write(cout);

			// Deallocate and remove the item from the m_items array
			delete m_items[index];
			for (int i = index; i < m_noOfItems - 1; i++) {
				m_items[i] = m_items[i + 1];
			}
			m_items[m_noOfItems - 1] = nullptr;
			m_noOfItems--;

			printActionTitle("DONE!");
		}
	}

	// Adds the number of items to be added to the quantity of the Item.
	void PosApp::stockItem() {
		int rowNumber;
		int value;

		bool isInteger = false;
		int quantityToAdd = -1;

		printActionTitle("Select an item to stock");

		// Get the row number of the item to be stocked
		rowNumber = selectItem();

		if (rowNumber > 0) {
			// Convert row number to index in the m_items array
			int index = rowNumber - 1;

			int minValue = 1;
			int maxValue = MAX_STOCK_NUMBER - m_items[index]->quantity();

			// Display the selected item
			cout << "Selected Item:" << endl;
			m_items[index]->displayType(POS_FORM);
			m_items[index]->write(cout); 

			// Get an integer (fool-proof) between 1 and current number of items minus the MAX_STOCK_NUMBER
			cout << "Enter quantity to add: ";
			cin >> value;

			// Loop until a valid quantity is entered
			do {
				if (cin) {
					isInteger = true;
				}

				if (!isInteger) {
					invalidInput();
					cin >> value;
				}
				else {
					quantityToAdd = getInt(minValue, maxValue, value);
					if (quantityToAdd == -1) {
						cout << "Enter quantity to add: ";
						cin >> value;
					}
				}
			} while (!isInteger || quantityToAdd == -1);

			// Add the quantity to the item
			*m_items[index] += quantityToAdd;

			printActionTitle("DONE!");
		}
	}
	
	// Adds the searched item to the bill, and prints the total price of the bill so far.
	void PosApp::POS() {
		Bill bill;
		char sku[MAX_SKU_LEN + 1];
		bool isSKUEmpty = false;

		printActionTitle("Starting Point of Sale");

		cin.clear();
		cin.ignore(1000, '\n');

		// Keep asking for SKU until the user enters an empty SKU
		while (!isSKUEmpty) {
			cout << "Enter SKU or <ENTER> only to end sale..." << endl;
			cout << "> ";
			cin.getline(sku, MAX_SKU_LEN + 1);

			// Check if input is valid
			if (!cin) {
				cout << "SKU too long" << endl;
				cin.clear();
				cin.ignore(10000, '\n');
			}
			else {
				isSKUEmpty = (sku[0] == '\0');

				// If not empty, search for the item
				if (!isSKUEmpty) {
					Item* foundItem = search(sku);

					if (foundItem) {
						if (foundItem->quantity() > 0) {
							(*foundItem) -= 1;

							foundItem->displayType(POS_FORM);
							foundItem->write(cout);
							cout << endl << ">>>>> Added to bill" << endl;

							bill.add(foundItem);

							cout << ">>>>> Total: " << fixed << setprecision(2) << bill.total() << endl;
						}
						else {
							cout << ERROR_POS_STOCK << endl;
						}
					}
					else {
						cout << "!!!!! Item Not Found !!!!!" << endl;
					}
				}
			}
		}

		// Print the bill
		cout.fill(' ');
		bill.print(cout);
	}


	/***** OTHER PRIVATE MEMBER FUNCTION *****/
	// Clears the input buffer and shows Invalid Integer message
	void PosApp::invalidInput() {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid Integer, try again: ";
	}

	// If input integer is within given range, it returns the integer. Otherwise, returns -1.
	int PosApp::getInt(int minValue, int maxValue, int value) {
		int choice;

		if (value < minValue || value > maxValue) {
			// Input is outside the allowed range
			cout << "[" << minValue << "<=value<=" << maxValue << "], retry: ";
			choice = -1;
		}
		else {
			choice = value;
		}

		return choice;
	}

	// Returns true if the first Item's name is alphabetically lower than the second Item's name.
	bool PosApp::compareItemsByName(const Item* a, const Item* b) {
		return strcmp(a->name(), b->name()) < 0;
	}


	/***** CONSTRUCTOR AND DESTRUCTOR *****/
	// Constructor that takes the filename.
	PosApp::PosApp(const char* filename) : m_noOfItems(0) {
		strncpy(m_filename, filename, MAX_FILENAME_LEN);

		// Initialize m_items array with nullptr
		for (int i = 0; i < MAX_NO_ITEMS; ++i) {
			m_items[i] = nullptr;
		}
	}

	// Destructor.
	PosApp::~PosApp() {
		for (int i = 0; i < m_noOfItems; ++i) {
			delete m_items[i];
		}
	}


	/***** PUBLIC MEMBER FUNCTION *****/
	// Implements the program logic, including loading records, displaying menu, 
	// executing actions, saving records, and displaying goodbye message.
	void PosApp::run() {
		int choice;

		loadRecs();

		do {
			choice = menu();

			switch (choice) {
			case 1:
				listItems();
				break;
			case 2:
				addItem();
				break;
			case 3:
				removeItem();
				break;
			case 4:
				stockItem();
				break;
			case 5:
				POS();
				break;
			}
		} while (choice != 0);

		saveRecs();

		cout << "Goodbye!" << endl;
	}




	
}