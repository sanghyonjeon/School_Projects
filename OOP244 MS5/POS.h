/* Citation and Sources...
Final Project Milestone 5
Module: POS
Filename: POS.h
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
#ifndef SDDS_POS_H_
#define SDDS_POS_H_

namespace sdds {
	// Constants for Tax
	const double TAX = 0.13;

	// Constants for SKU
	const int MAX_SKU_LEN = 7;

	// Constants for Date
	const int MIN_YEAR = 2000;
	const int MAX_YEAR = 2030;
	const int MIN_MONTH = 1;
	const int MAX_MONTH = 12;
	const int MIN_DAY = 1;

	//Constants for Time
	const int MIN_HOUR = 0;
	const int MAX_HOUR = 23;
	const int MIN_MINUTE = 0;
	const int MAX_MINUTE = 59;

	// Constants for Stock
	const int MAX_STOCK_NUMBER = 99;
	const int MAX_NO_ITEMS = 200;

	// Constants for Name Length
	const int MAX_NAME_LEN = 20;
	const int MAX_FILENAME_LEN = 128;

	// Constants for Output Format
	const int POS_LIST = 1;
	const int POS_FORM = 2;

	// Constants for Menu Options
	const int MIN_MENU_OPTION = 0;
	const int MAX_MENU_OPTION = 5;

	// Constants for Item Error Messages
	const char ERROR_POS_SKU[] = "SKU too long";
	const char ERROR_POS_NAME[] = "Item name too long";
	const char ERROR_POS_PRICE[] = "Invalid price value";
	const char ERROR_POS_TAX[] = "Invalid tax status";
	const char ERROR_POS_QTY[] = "Invalid quantity value";
	const char ERROR_POS_STOCK[] = "Item out of stock";
	const char ERROR_POS_EMPTY[] = "Invalid Empty Item";

	// Constants for Validation Error Messages
	const char ERROR_INVALID_YEAR[] = "Invalid Year";
	const char ERROR_INVALID_MONTH[] = "Invalid Month";
	const char ERROR_INVALID_DAY[] = "Invalid Day";
	const char ERROR_INVALID_HOUR[] = "Invalid Hour";
	const char ERROR_INVALID_MINUTE[] = "Invlid Minute";

	// Constants for Date Error Messages
	const char ERROR_READ_YEAR[] = "Cannot read year entry";
	const char ERROR_READ_MONTH[] = "Cannot read month entry";
	const char ERROR_READ_DAY[] = "Cannot read day entry";
	const char ERROR_READ_HOUR[] = "Cannot read hour entry";
	const char ERROR_READ_MINUTE[] = "Cannot read minute entry";
}
#endif // !SDDS_POS_H_