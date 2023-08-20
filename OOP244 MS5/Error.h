/* Citation and Sources...
Final Project Milestone 5
Module: Error
Filename: Error.h
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
#ifndef SDDS_ERROR_H_
#define SDDS_ERROR_H_
#include <iostream>

namespace sdds {
	class Error {
		/***** PRIVATE MEMBER VARIABLE *****/
		char* m_message;

	public:
		/***** CONSTRUCTORS *****/
		// Default constructor
		Error();
		// Constructor that takes an error message as an argument
		Error(const char* message);

		/***** RULE OF THREE *****/
		// Copy constructor
		Error(const Error& src);
		// Copy assignment operator
		Error& operator=(const Error& src);
		// Destructor
		~Error();

		/***** OTHER PUBLIC MEMBER FUNCTIONS *****/
		// Assignment operator that takes a message as an argument
		Error& operator=(const char* message);
		// Conversion operator that returns a boolean value,
		// indicating if the error object is in an erroneous state
		operator bool() const;
		// Clears the error message and returns the error object
		Error& clear();
		// Getter function that returns the error message
		const char* getMessage() const;
	};

	/***** HELPER FUNCTION ******/
	// Overloaded stream insertion operator that inserts the error message into an output stream
	std::ostream& operator<<(std::ostream& ostr, const Error& rhs);
}
#endif // !SDDS_ERROR_H_