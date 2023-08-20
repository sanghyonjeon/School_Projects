/* Citation and Sources...
Final Project Milestone 5
Module: Item
Filename: Item.h
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
#ifndef SDDS_ITEM_H_
#define SDDS_ITEM_H_
#include "POS.h"
#include "Error.h"
#include "PosIO.h"

namespace sdds {
	class Item : public PosIO {
		/***** PRIVATE MEMBER VARIABLES *****/
		char m_sku[MAX_SKU_LEN + 1];
		char* m_itemName;
		double m_price;
		bool m_taxed;
		int m_quantity;

	protected:
		/***** PROTECTED MEMBER VARIABLE/ATTRIBUTE *****/
		int m_displayType;
		Error m_error;

	public:
		/***** CONSTRUCTOR *****/
		// Default constructor
		Item();

		/***** RULE OF THREE *****/
		// Copy constructor
		Item(const Item& src);
		// Copy assignment operator
		Item& operator=(const Item& src);
		// Destructor
		~Item();

		/***** MEMBER OPERATOR OVERLOADS *****/
		// Compares Item to a C-string SKU, returns true if they match
		bool operator==(const char* sku) const;
		// Compares two Items by name, returns true if current Item's name is greater
		bool operator>(const Item& other) const;
		// Adds specified quantity to Item, caps it at MAX_STOCK_NUMBER, and returns new quantity
		int operator+=(int quantity);
		// Reduces Item's quantity by specified value, prevents negative values, and returns new quantity
		int operator-=(int quantity);
		// Returns opposite of error attribute status
		operator bool() const;

		/***** GETTER FUNCTIONS *****/
		// Returns the cost of the Item, including tax if the item is taxable.
		double cost() const;
		// Returns the quantity of the Item.
		int quantity() const;
		// Returns the name of the Item.
		const char* name() const;
		// Returns the SKU of the Item.
		const char* sku() const;

		/***** OTHER PUBLIC MEMBER FUNCTIONS *****/
		// This pure virtual function returns the item type as a character.
		virtual char itemType() const = 0;
		// Sets the display mode (POS_LIST or POS_FORM) and returns the reference of the object
		Item& displayType(int type);
		// Clears the error status and returns the reference of the object
		Item& clear();
		// Reads item attributes from an input stream and returns the istream reference
		std::istream& read(std::istream& is);
		// Writes the Item to an output stream based on display mode and returns the ostream reference
		std::ostream& write(std::ostream& os) const;
		// Loads item attributes from an ifstream and returns the ifstream reference
		std::ifstream& load(std::ifstream& ifs);
		// Saves item attributes to an ofstream in a comma-separated format and returns the ofstream reference
		std::ofstream& save(std::ofstream& ofs) const;
		// Prints bill information of the Item and returns the ostream reference
		std::ostream& bprint(std::ostream& os) const;
	};

	/***** HELPER FUNCTION *****/
	// Adds the product of cost and quantity of the Item to the lhs operand and returns the updated value.
	double& operator+=(double& lhs, const Item& rhs);
}
#endif // !SDDS_ITEM_H_