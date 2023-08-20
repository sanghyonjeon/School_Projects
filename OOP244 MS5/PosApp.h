/* Citation and Sources...
Final Project Milestone 5
Module: PosApp
Filename: PosApp.h
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
#ifndef POSAPP_H
#define POSAPP_H

#include <iostream>
#include <fstream>
#include "Perishable.h"
#include "NonPerishable.h"
#include "POS.h"

namespace sdds {
    class PosApp {
        /***** PRIVATE MEMBER VARIABLES *****/
        char m_filename[MAX_FILENAME_LEN];
        Item* m_items[MAX_NO_ITEMS]; // Iptr
        int m_noOfItems; // nptr

        /***** PRIVATE FUNCTIONS FOR MENU OPTIONS *****/
        // Prints a title for an action.
        void printActionTitle(const char* title) const;
        // Loads all the records of the data file into the Iptr array (m_items).
        void loadRecs();
        // Saves all the items pointed by Iptr array (m_items) in the data file.
        void saveRecs();
        // Allows the user to select an Item by entering the row number.
        int selectItem();
        // Receives the SKU and returns the address of the item if matching SKU is found.
        Item* search(const char* sku);

        /***** MENU OPTIONS *****/
        // Displays the menu and returns the user's choice.
        int menu();
        // Sorts all the items in Iptr array (m_items), and prints each item information.
        void listItems(bool showTotalAsset = true);
        // Adds a new item to the inventory.
        void addItem();
        // Removes an item selected by the user.
        void removeItem();
        // Adds the number of items to be added to the quantity of the Item.
        void stockItem();
        // Adds the searched item to the bill, and prints the total price of the bill so far.
        void POS();

        /***** OTHER PRIVATE MEMBER FUNCTION *****/
        // Clears the input buffer and shows Invalid Integer message
        void invalidInput();
        // If input integer is within given range, it returns the integer. Otherwise, returns -1.
        int getInt(int minValue, int maxValue, int value);

        
        // Returns true if the first Item's name is alphabetically lower than the second Item's name.
        bool compareItemsByName(const Item* a, const Item* b);

    public:
        /***** CONSTRUCTOR AND DESTRUCTOR *****/
        // Constructor that takes the filename.
        PosApp(const char* filename);
        // Destructor.
        ~PosApp();

        /***** PREVENT COPY CONSTRUCTOR & ASSIGNMENT OPERATOR *****/
        // Prevented copy constructor.
        PosApp(const PosApp& src) = delete;
        // Prevented assignment operator.
        PosApp& operator=(const PosApp& src) = delete;

        /***** PUBLIC MEMBER FUNCTION *****/
        // Implements the program logic, including loading records, displaying menu, 
        // executing actions, saving records, and displaying goodbye message.
        void run();
    };    
}
#endif // !SDDS_POSAPP_H_