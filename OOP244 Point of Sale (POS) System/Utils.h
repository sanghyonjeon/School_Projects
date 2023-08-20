/* Citation and Sources...
Final Project Milestone 5
Module: Utils
Filename: Utils.h
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
#ifndef SDDS_UTILS_H_
#define SDDS_UTILS_H_

namespace sdds {
	/***** DATE AND TIME UTILITY FUNCTIONS *****/
	// Gets the current system date and time, and returns them through the argument list.
	void getSystemDate(int& year, int& mon, int& day, int& hour, int& min, bool dateOnly);
	// Assigns a unique integer value to a date-time value, which can be used to compare two dates.
	int uniqueDateValue(int year, int mon, int day, int hour, int min);
	// Returns the number of days in a given month and year, considering leap years.
	int daysOfMonth(int year, int month);
}
#endif // !SDDS_UTILS_H_