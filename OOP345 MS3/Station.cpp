// Name: Sang Hyon Jeon
// Seneca Student ID: 113552194
// Seneca email: shjeon5@myseneca.ca
// Date of completion: August 5, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include "Utilities.h"
#include "Station.h"

using namespace std;

namespace sdds {
	size_t Station::m_widthField{};
	int Station::id_generator{};

    Station::Station(const string& src) {
        Utilities util;
        size_t next_pos{};
        bool more{};

        m_id = ++id_generator;

        m_itemName = util.extractToken(src, next_pos, more);
        
        if (more) {
            m_serialNumber = stoi(util.extractToken(src, next_pos, more));
        }

        if (more) {
            m_currentStock = stoi(util.extractToken(src, next_pos, more));
        }

        m_widthField = max(m_widthField, util.getFieldWidth());

        if (more) {
            m_description = util.extractToken(src, next_pos, more);
        }
    }

    const string& Station::getItemName() const {
        return m_itemName;
    }

    size_t Station::getNextSerialNumber() {
        return m_serialNumber++;
    }

    size_t Station::getQuantity() const {
        return m_currentStock;
    }

    void Station::display(ostream& os, bool full) const {
        os << setw(3) << setfill('0') << right << m_id << setfill(' ') << " | "
            << setw(m_widthField) << left << m_itemName << " | "
            << setw(6) << setfill('0') << right << m_serialNumber << setfill(' ') << " | ";

        if (full) {
            os << setw(4) << right << m_currentStock <<" | "
                << m_description;
        }

        os << endl;
    }

    void Station::updateQuantity() {
        if (m_currentStock > 0) {
            --m_currentStock;
        }
    }
}