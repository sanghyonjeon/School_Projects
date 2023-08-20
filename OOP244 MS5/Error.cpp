/* Citation and Sources...
Final Project Milestone 5
Module: Error
Filename: Error.cpp
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
#include "Error.h"
#include <cstring>

using namespace std;

namespace sdds {
	/***** CONSTRUCTORS *****/
	// Default constructor
	Error::Error() {
		// The Error class by default is in a "No Error" state.
		m_message = nullptr;
	}

	// Constructor that takes an error message as an argument
	Error::Error(const char* message) {
		// Allocate memory for the message and copy it, if valid
		if (message != nullptr && message[0] != '\0') {
			m_message = new char[strlen(message) + 1];
			strcpy(m_message, message);
		}
		else {
			// Set the message to "No Error" state, if not valid
			m_message = nullptr;
		}
	}


	/***** RULE OF THREE *****/
	// Copy constructor
	Error::Error(const Error& src) {
		// Allocate memory and copy the source error message, if valid
		if (src.m_message != nullptr && src.m_message[0] != '\0') {
			m_message = new char[strlen(src.m_message) + 1];
			strcpy(m_message, src.m_message);
		}
		else {
			// Set the message to "No Error" state, if not valid
			m_message = nullptr;
		}
	}

	// Copy assignment operator
	Error& Error::operator=(const Error& src) {
		// Check for self-assignment
		if (this != &src) {
			// Deallocate memory previously used by m_message
			delete[] m_message;

			// Allocate memory and copy the source error message, if valid
			if (src.m_message != nullptr) {
				m_message = new char[strlen(src.m_message) + 1];
				strcpy(m_message, src.m_message);
			}
			else {
				// Set the message to "No Error" state, if not valid
				m_message = nullptr;
			}
		}

		return *this;
	}

	// Destructor
	Error::~Error() {
		delete[] m_message;
	}


	/***** OTHER PUBLIC MEMBER FUNCTIONS *****/
	// Assignment operator that takes a message as an argument
	Error& Error::operator=(const char* message) {
		// Deallocate memory previously used by m_message
		delete[] m_message;

		// Allocate memory for the message and copy it, if valid
		if (message != nullptr && message[0] != '\0') {
			m_message = new char[strlen(message) + 1];
			strcpy(m_message, message);
		}
		else {
			// Set the message to "No Error" state, if not valid
			m_message = nullptr;
		}

		return *this;
	}

	// Conversion operator that returns a boolean value
	Error::operator bool() const {
		// Return true if the m_message is not null and not an empty string, false otherwise
		return m_message != nullptr;
	}

	// Clears the error message and returns the error object
	Error& Error::clear() {
		// Deallocate memory used by m_message
		delete[] m_message;
		m_message = nullptr;

		return *this;
	}

	// Getter function that returns the error message
	const char* Error::getMessage() const {
		return m_message;
	}


	/***** HELPER FUNCTION ******/
	// Overloaded stream insertion operator that inserts the error message into an output stream
	std::ostream& operator<<(std::ostream& ostr, const Error& rhs) {
		// Check if the error object is in an erroneous state
		if (rhs) {
			// Insert the error message into the output stream
			ostr << rhs.getMessage();
		}

		return ostr;
	}
}