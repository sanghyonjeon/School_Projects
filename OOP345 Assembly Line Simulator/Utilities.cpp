// Name: Sang Hyon Jeon
// Seneca Student ID: 113552194
// Seneca email: shjeon5@myseneca.ca
// Date of completion: August 5, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS
#include "Utilities.h"

using namespace std;

namespace sdds {
	char Utilities::m_delimiter{};

	void Utilities::setFieldWidth(size_t newWidth) {
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}

    string Utilities::extractToken(const string& str, size_t& next_pos, bool& more) {
		more = false;

		size_t pos{ str.find(m_delimiter, next_pos) };

		if (pos == next_pos) {
			throw string("Delimiter found at next_pos");
		}

		if (pos == string::npos) {
			pos = str.size();
		}
		else {
			more = true;
		}

		string token{ str.substr(next_pos, pos - next_pos) };
		token = trim(token);

		if (m_widthField < token.size()) {
			m_widthField = token.size();
		}

		next_pos = pos + 1;

		return token;
    }

	void Utilities::setDelimiter(char newDelimiter) {
		m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter() {
		return m_delimiter;
	}

    string Utilities::trim(const string& str) {
        string::size_type first{ str.find_first_not_of(' ') };
        string::size_type last{ str.find_last_not_of(' ') };

        return (first == string::npos) ? "" : str.substr(first, (last - first + 1));
    }
}