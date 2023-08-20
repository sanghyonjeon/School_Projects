/* Citation and Sources...
Final Project Milestone 5
Module: Date
Filename: Date.cpp
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
#include "Date.h"
#include "Utils.h"
#include "POS.h"

using namespace std;

namespace sdds {
	/***** PRIVATE MEMBER FUNCTIONS *****/
	// Overloaded comparison operators that compare two Date objects and return a boolean value.
	bool Date::operator==(const Date& rhs) const {
		return uniqueDateValue(m_year, m_month, m_day, m_hour, m_minute) == uniqueDateValue(rhs.m_year, rhs.m_month, rhs.m_day, rhs.m_hour, rhs.m_minute);
	}

	bool Date::operator!=(const Date& rhs) const {
		return uniqueDateValue(m_year, m_month, m_day, m_hour, m_minute) != uniqueDateValue(rhs.m_year, rhs.m_month, rhs.m_day, rhs.m_hour, rhs.m_minute);
	}

	bool Date::operator<(const Date& rhs) const {
		return uniqueDateValue(m_year, m_month, m_day, m_hour, m_minute) < uniqueDateValue(rhs.m_year, rhs.m_month, rhs.m_day, rhs.m_hour, rhs.m_minute);
	}

	bool Date::operator>(const Date& rhs) const {
		return uniqueDateValue(m_year, m_month, m_day, m_hour, m_minute) > uniqueDateValue(rhs.m_year, rhs.m_month, rhs.m_day, rhs.m_hour, rhs.m_minute);
	}

	bool Date::operator<=(const Date& rhs) const {
		return uniqueDateValue(m_year, m_month, m_day, m_hour, m_minute) <= uniqueDateValue(rhs.m_year, rhs.m_month, rhs.m_day, rhs.m_hour, rhs.m_minute);
	}

	bool Date::operator>=(const Date& rhs) const {
		return uniqueDateValue(m_year, m_month, m_day, m_hour, m_minute) >= uniqueDateValue(rhs.m_year, rhs.m_month, rhs.m_day, rhs.m_hour, rhs.m_minute);
	}

	// Checks and validates the date and time values.
	void Date::validate() {
		if (m_year < MIN_YEAR || m_year > MAX_YEAR) {
			m_error = ERROR_INVALID_YEAR;
		}
		else if (m_month < MIN_MONTH || m_month > MAX_MONTH) {
			m_error = ERROR_INVALID_MONTH;
		}
		else if (m_day < MIN_DAY || m_day > daysOfMonth(m_year, m_month)) {
			m_error = ERROR_INVALID_DAY;
		}
		else if (!m_dateOnly && (m_hour < MIN_HOUR || m_hour > MAX_HOUR)) {
			m_error = ERROR_INVALID_HOUR;
		}
		else if (!m_dateOnly && (m_minute < MIN_MINUTE || m_minute > MAX_MINUTE)) {
			m_error = ERROR_INVALID_MINUTE;
		}
	}


	/***** CONSTRUCTORS *****/
	// Default constructor
	Date::Date() {
		int year, month, day, hour, minute;
		getSystemDate(year, month, day, hour, minute, false);
		*this = Date(year, month, day, hour, minute);
		dateOnly(false);
	}

	// Constructor that takes year, month, and day as arguments
	Date::Date(int year, int month, int day) {
		*this = Date(year, month, day, 0, 0);
		dateOnly(true);
	}

	// Constructor that takes year, month, day, hour, and minute as arguments
	Date::Date(int year, int month, int day, int hour, int minute) {
		m_year = year;
		m_month = month;
		m_day = day;
		m_hour = hour;
		m_minute = minute;
		if (m_hour == 0 && m_minute == 0) {
			dateOnly(true);
		}
		else {
			dateOnly(false);
		}
		

		// Validate the date and time values
		validate();
	}


	/***** PUBLIC MEMBER FUNCTIONS *****/
	// Sets the date-only flag (m_dateOnly) to the specified value
	Date& Date::dateOnly(bool value) {
		m_dateOnly = value;

		if (m_dateOnly) {
			m_hour = 0;
			m_minute = 0;
		}

		return *this;
	}

	// Conversion operator that returns the opposite of the state of the error attribute
	Date::operator bool() const {
		return !m_error;
	}

	// Getter function that returns the Error object
	const Error& Date::error() const {
		return m_error;
	}

	// Prints the date information to an output stream
	std::ostream& Date::print(std::ostream& ostr) const {
		ostr << setfill('0') << right << m_year << '/';
		ostr << setw(2) << m_month << '/';
		ostr << setw(2) << m_day;

		if (!m_dateOnly) {
			ostr << ", ";
			ostr << setw(2) << m_hour << ':';
			ostr << setw(2) << m_minute;
		}

		return ostr;
	}

	// Reads the date information from an input stream
	std::istream& Date::rread(std::istream& istr) {
		Error error;

		// Read the year from the input stream
		istr >> m_year;
		if (!istr) {
			error = ERROR_READ_YEAR;
		}
		istr.ignore();

		// Read the month from the input stream
		istr >> m_month;
		if (!error && !istr) {
			error = ERROR_READ_MONTH;
		}
		istr.ignore();

		// Read the day from the input stream
		istr >> m_day;
		if (!error && !istr) {
			error = ERROR_READ_DAY;
		}

		// If not a date-only object and there is more data in the input stream
		if (!m_dateOnly && istr.peek() != '\n' && istr.peek() != EOF) {
			istr.ignore();

			// Read the hour from the input stream
			istr >> m_hour;
			if (!error && !istr) {
				error = ERROR_READ_HOUR;
			}
			istr.ignore();

			// Read the minute from the input stream
			istr >> m_minute;
			if (!error && !istr) {
				error = ERROR_READ_MINUTE;
			}
		}
		else {
			// Set the object as a date-only status
			dateOnly(true);
		}

		// Validate the date and time values if input stream was successfully read
		if (istr) {
			validate();
		}

		return istr;
	}


	/***** HELPER FUNCTIONS ******/
	// Overloaded stream insertion operator that inserts the date information into an output stream
	std::ostream& operator<<(std::ostream& ostr, const Date& rhs) {
		// Check if the Date object is valid (no errors)
		if (rhs) {
			// If valid, print the date information to the output stream
			rhs.print(ostr);
		}
		else {
			// If not valid, print the error message, followed by the date information in parentheses
			ostr << rhs.error() << "(";
			rhs.print(ostr);
			ostr << ")";
		}

		return ostr;
	}

	// Overloaded stream extraction operator that reads the date information from an input stream
	std::istream& operator>>(std::istream& istr, Date& rhs) {
		return rhs.rread(istr);
	}
}