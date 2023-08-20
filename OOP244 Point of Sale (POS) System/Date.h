/* Citation and Sources...
Final Project Milestone 5
Module: Date
Filename: Date.h
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
#ifndef SDDS_DATE_H_
#define SDDS_DATE_H_
#include "Error.h"

namespace sdds {
	class Date {
		/***** PRIVATE MEMBER VARIABLES *****/
		int m_year;
		int m_month;
		int m_day;
		int m_hour;
		int m_minute;
		bool m_dateOnly;
		Error m_error;

		/***** PRIVATE MEMBER FUNCTIONS *****/
		// Overloaded comparison operators that compare two Date objects and return a boolean value.
		bool operator==(const Date& rhs) const;
		bool operator!=(const Date& rhs) const;
		bool operator<(const Date& rhs) const;
		bool operator>(const Date& rhs) const;
		bool operator<=(const Date& rhs) const;
		bool operator>=(const Date& rhs) const;
		// Checks and validates the date and time values.
		void validate();

	public:
		/***** CONSTRUCTORS *****/
		// Default constructor
		Date();
		// Constructor that takes year, month, and day as arguments
		Date(int year, int month, int day);
		// Constructor that takes year, month, day, hour, and minute as arguments
		Date(int year, int month, int day, int hour, int minute = 0);

		/***** PUBLIC MEMBER FUNCTIONS *****/
		// Sets the date-only flag (m_dateOnly) to the specified value
		Date& dateOnly(bool value);
		// Conversion operator that returns the opposite of the state of the error attribute
		operator bool() const;
		// Getter function that returns the Error object
		const Error& error() const;
		// Prints the date information to an output stream
		std::ostream& print(std::ostream& ostr) const;
		// Reads the date information from an input stream
		std::istream& rread(std::istream& istr);
	};

	/***** HELPER FUNCTIONS ******/
	// Overloaded stream insertion operator that inserts the date information into an output stream
	std::ostream& operator<<(std::ostream& ostr, const Date& rhs);
	// Overloaded stream extraction operator that reads the date information from an input stream
	std::istream& operator>>(std::istream& istr, Date& rhs);
}
#endif // !SDDS_DATE_H_