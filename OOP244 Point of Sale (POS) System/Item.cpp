/* Citation and Sources...
Final Project Milestone 5
Module: Item
Filename: Item.cpp
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
#include "Item.h"
#include <cstring>
#include <iomanip>

using namespace std;

namespace sdds {
	/***** CONSTRUCTOR *****/
	// Default constructor
	Item::Item() {
		m_sku[0] = '\0';
		m_itemName = nullptr;
		m_price = 0.0;
		m_taxed = false;
		m_quantity = 0;
		m_displayType = 0;
	}


	/***** RULE OF THREE *****/
	// Copy constructor
	Item::Item(const Item& src) {
		// Creates a new Item object as a copy of an existing one (src)
		*this = src;
	}

	// Copy assignment operator
	Item& Item::operator=(const Item& src) {
		// Check for self-assignment
		if (this != &src) {
			// Copy SKU, ensuring proper null termination
			strncpy(m_sku, src.m_sku, MAX_SKU_LEN + 1);
			// Free memory of the current object's itemName
			delete[] m_itemName;

			// If the source object has a valid itemName, allocate memory and copy it
			if (src.m_itemName) {
				m_itemName = new char[strlen(src.m_itemName) + 1];
				strcpy(m_itemName, src.m_itemName);
			}
			else {
				// If the source object's itemName is not valid, set it to nullptr
				m_itemName = nullptr;
			}

			// Copy the rest of the member variables from the source object
			m_price = src.m_price;
			m_taxed = src.m_taxed;
			m_quantity = src.m_quantity;
			m_displayType = src.m_displayType;
			m_error = src.m_error;
		}

		// Return *this to allow for chained assignment
		return *this;
	}

	// Destructor
	Item::~Item() {
		delete[] m_itemName;
	}


	/***** MEMBER OPERATOR OVERLOADS *****/
	// Compares Item to a C-string SKU, returns true if they match
	bool Item::operator==(const char* sku) const {
		return strcmp(m_sku, sku) == 0;
	}

	// Compares two Items by name, returns true if current Item's name is greater
	bool Item::operator>(const Item& other) const {
		return strcmp(m_itemName, other.m_itemName) > 0;
	}

	// Adds specified quantity to Item, caps it at MAX_STOCK_NUMBER, and returns new quantity
	int Item::operator+=(int quantity) {
		m_quantity += quantity;

		if (m_quantity > MAX_STOCK_NUMBER) {
			m_quantity = MAX_STOCK_NUMBER;
			m_error = ERROR_POS_QTY;
		}

		return m_quantity;
	}

	// Reduces Item's quantity by specified value, prevents negative values, and returns new quantity
	int Item::operator-=(int quantity) {
		m_quantity -= quantity;

		if (m_quantity < 0) {
			m_quantity = 0;
			m_error = ERROR_POS_STOCK;
		}

		return m_quantity;
	}

	// Returns opposite of error attribute status
	Item::operator bool() const {
		return !m_error;
	}


	/***** GETTER FUNCTIONS *****/
	// Returns the cost of the Item, including tax if the item is taxable.
	double Item::cost() const {
		return m_price * (1 + m_taxed * TAX);
	}

	// Returns the quantity of the Item.
	int Item::quantity() const {
		return m_quantity;
	}

	// Returns the name of the Item.
	const char* Item::name() const {
		return m_itemName;
	}

	// Returns the SKU of the Item.
	const char* Item::sku() const {
		return m_sku;
	}


	/***** OTHER PUBLIC MEMBER FUNCTIONS *****/
	// Sets the display mode (POS_LIST or POS_FORM) and returns the reference of the object
	Item& Item::displayType(int type) {
		m_displayType = type;

		return *this;
	}

	// Clears the error status and returns the reference of the object
	Item& Item::clear() {
		m_error.clear();

		return *this;
	}

	// Reads item attributes from an input stream and returns the istream reference
	std::istream& Item::read(std::istream& is) {
		char sku[MAX_SKU_LEN + 2];
		char name[MAX_NAME_LEN + 2];
		double price;
		char taxed;
		int quantity;

		int skuLength;
		int nameLength;

		m_error.clear();

		// Read SKU
		cout << "Sku";
		do {
			cout << "\n> ";
			is.getline(sku, MAX_SKU_LEN + 2);
			skuLength = strlen(sku);
			if (skuLength > MAX_SKU_LEN) {
				cout << ERROR_POS_SKU;
			}
		} while (skuLength > MAX_SKU_LEN);

		// Read Name
		cout << "Name";
		do {
			cout << "\n> ";
			is.getline(name, MAX_NAME_LEN + 2);
			nameLength = strlen(name);
			if (strlen(name) > MAX_NAME_LEN) {
				cout << ERROR_POS_NAME;
				is.clear();
				is.ignore(10000, '\n');

			}
		} while (nameLength > MAX_NAME_LEN);

		// Read Price
		cout << "Price";
		do {
			cout << "\n> ";
			is >> price;
			if (!is || price < 0) {
				cout << ERROR_POS_PRICE;
				is.clear();
				is.ignore(10000, '\n');
			}
		} while (!is || price < 0);

		// Ignore the delimiter
		is.ignore();

		// Read Taxed
		cout << "Taxed?\n(Y)es/(N)o: ";
		do {
			is >> taxed;
			if (taxed != 'y' && taxed != 'Y' && taxed != 'n' && taxed != 'N') {
				cout << "Only 'y' and 'n' are acceptable: ";
				is.clear();
				is.ignore(10000, '\n');
			}
		} while (taxed != 'y' && taxed != 'Y' && taxed != 'n' && taxed != 'N');

		// Ignore the delimiter
		is.ignore();

		// Read Quantity
		cout << "Quantity";
		do {
			cout << "\n> ";
			is >> quantity;
			if (!is || quantity < 1 || quantity > 99) {
				cout << ERROR_POS_QTY;
				is.clear();
				is.ignore(10000, '\n');
			}
		} while (!is || quantity < 1 || quantity > 99);

		// Ignore the delimiter
		is.ignore();

		// Assign values to data members
		strncpy(m_sku, sku, MAX_SKU_LEN);
		m_itemName = new char[MAX_NAME_LEN + 1];
		strncpy(m_itemName, name, MAX_NAME_LEN);
		m_price = price;
		m_taxed = (taxed == 'y' || taxed == 'Y');
		m_quantity = quantity;

		return is;
	}

	// Writes the Item to an output stream based on display mode and returns the ostream reference
	std::ostream& Item::write(std::ostream& os) const {
		char itemNameSubstring[MAX_NAME_LEN + 1];
		strncpy(itemNameSubstring, m_itemName, MAX_NAME_LEN);
		itemNameSubstring[20] = '\0';

		if (!m_error) {
			if (m_displayType == POS_LIST) {
				os << setfill(' ') << setw(7) << left << m_sku;
				os << '|' << setw(MAX_NAME_LEN) << left << itemNameSubstring;
				os << '|' << setw(7) << right << fixed << setprecision(2) << m_price;
				os << '|' << setw(3) << left << (m_taxed ? " X" : " ") << '|';
				os << setw(4) << right << quantity() << '|';
				os << setw(9) << right << cost() * quantity() << '|';
			}
			else if (m_displayType == POS_FORM) {
				os << setfill(' ') << "=============v" << endl;
				os << setw(13) << left << "Name:" << m_itemName << endl;
				os << setw(13) << left << "Sku:" << m_sku << endl;
				os << setw(13) << left << "Price:" << fixed << setprecision(2) << m_price << endl;

				if (m_taxed) {
					os << setw(13) << left << "Price + tax:" << fixed << setprecision(2) << cost() << endl;
				}
				else {
					os << setw(13) << left << "Price + tax:" << "N/A" << endl;
				}

				os << setw(13) << left << "Stock Qty:" << quantity() << endl;
			}
		}
		else {
			os << m_error;
		}
		return os;
	}

	// Loads item attributes from an ifstream and returns the ifstream reference
	std::ifstream& Item::load(std::ifstream& ifs) {
		m_error.clear();

		if (ifs) {
			char sku[MAX_SKU_LEN + 2]{};
			char name[MAX_NAME_LEN + 2]{};
			double price{};
			int qty{};
			bool tax{};

			ifs.get(sku, MAX_SKU_LEN + 2, ',');
			ifs.ignore(1000, ',');
			ifs.get(name, MAX_NAME_LEN + 2, ',');
			ifs.ignore(1000, ',');
			ifs >> price;
			ifs.ignore();
			ifs >> tax;
			ifs.ignore();
			ifs >> qty;

			if (ifs) {
				// Validate SKU
				if (strlen(sku) > MAX_SKU_LEN) {
					m_error = ERROR_POS_SKU;
				}
				// Validate Name
				else if (strlen(name) > MAX_NAME_LEN) {
					m_error = ERROR_POS_NAME;
				}
				// Validate Price
				else if (price < 0) {
					m_error = ERROR_POS_PRICE;
				}
				// Validate Quantity
				else if (qty < 1 || qty > 99) {
					m_error = ERROR_POS_QTY;
				}
				// If no validation errors, assign attributes
				else {
					strncpy(m_sku, sku, MAX_SKU_LEN);
					delete[] m_itemName;
					m_itemName = new char[MAX_NAME_LEN + 1];
					strncpy(m_itemName, name, MAX_NAME_LEN);
					m_price = price;
					m_taxed = tax;
					m_quantity = qty;
				}
			}
		}

		return ifs;
	}

	// Saves item attributes to an ofstream in a comma-separated format and returns the ofstream reference
	std::ofstream& Item::save(std::ofstream& ofs) const {
		if (!m_error) {
			ofs << itemType() << ',';
			ofs << m_sku << ',';
			ofs << m_itemName << ',';
			ofs << fixed << setprecision(2) << m_price << ',';
			ofs << (m_taxed ? "1" : "0") << ',';
			ofs << quantity();
		}
		else {
			ofs << m_error << endl;
		}

		return ofs;
	}

	// Prints bill information of the Item and returns the ostream reference
	std::ostream& Item::bprint(std::ostream& os) const {
		char itemNameSubstring[MAX_NAME_LEN + 1];
		strncpy(itemNameSubstring, m_itemName, MAX_NAME_LEN);
		itemNameSubstring[20] = '\0';

		os << setfill(' ') << "| " << setw(MAX_NAME_LEN) << left << itemNameSubstring
			<< "| " << setw(9) << right << fixed << setprecision(2) << cost() << " "
			<< "| " << setw(4) << (m_taxed ? "T  " : " ") << "|" << endl;

		return os;
	}


	/***** HELPER FUNCTION *****/
	// Adds the product of cost and quantity of the Item to the lhs operand and returns the updated value.
	double& operator+=(double& lhs, const Item& rhs) {
		lhs += rhs.cost() * rhs.quantity();

		return lhs;
	}
}