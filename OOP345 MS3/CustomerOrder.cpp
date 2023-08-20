// Name: Sang Hyon Jeon
// Seneca Student ID: 113552194
// Seneca email: shjeon5@myseneca.ca
// Date of completion: August 5, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"

using namespace std;

namespace sdds {
	size_t CustomerOrder::m_widthField{};

    CustomerOrder::CustomerOrder(const string& str) {
        Utilities utility{};
        bool more{};
        size_t next_pos{};

        m_name = utility.extractToken(str, next_pos, more);

        if (more) {
            m_product = utility.extractToken(str, next_pos, more);
        }

        vector<string> tempItems;

        while (more) {
            tempItems.push_back(utility.extractToken(str, next_pos, more));
        }

        m_cntItem = tempItems.size();

        m_lstItem = new Item * [m_cntItem];

        for (size_t i = 0; i < m_cntItem; ++i) {
            m_lstItem[i] = new Item(tempItems[i]);
        }

        if (m_widthField < utility.getFieldWidth()) {
            m_widthField = utility.getFieldWidth();
        }
    }

    CustomerOrder::CustomerOrder(const CustomerOrder& src) {
        throw "Copy construction not allowed.";
    }

    CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept {
        *this = move(src);
    }

    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
        if (this != &src) {
            for (size_t i = 0; i < m_cntItem; ++i) {
                delete m_lstItem[i];
            }
            delete[] m_lstItem;

            m_name = src.m_name;
            m_product = src.m_product;
            m_cntItem = src.m_cntItem;
            m_lstItem = src.m_lstItem;

            src.m_name = "";
            src.m_product = "";
            src.m_cntItem = 0;
            src.m_lstItem = nullptr;
        }

        return *this;
    }

    CustomerOrder::~CustomerOrder() {
        for (size_t i = 0; i < m_cntItem; ++i) {
            delete m_lstItem[i];
        }

        delete[] m_lstItem;
    }

    bool CustomerOrder::isOrderFilled() const {
        return all_of(m_lstItem, m_lstItem + m_cntItem, [](Item* item) {
            return item->m_isFilled;
            }
        );
    }

    bool CustomerOrder::isItemFilled(const string& itemName) const {
        return none_of(m_lstItem, m_lstItem + m_cntItem, [itemName](const Item* item) {
            return item->m_itemName == itemName && !item->m_isFilled;
            }
        );
    }

    void CustomerOrder::fillItem(Station& station, ostream& os) {
        for (size_t i = 0; i < m_cntItem; ++i) {
            if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled) {
                if (station.getQuantity() > 0) {
                    station.updateQuantity();
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;

                    os << "    Filled " << m_name << ", " << m_product
                        << " [" << station.getItemName() << "]" << endl;

                    break;
                }
                else {
                    os << "    Unable to fill " << m_name << ", " << m_product
                        << " [" << station.getItemName() << "]" << endl;
                }
            }
        }
    }

    void CustomerOrder::display(ostream& os) const {
        os << m_name << " - " << m_product << endl;

        for (size_t i = 0; i < m_cntItem; ++i) {
            os << "[" << setw(6) << setfill('0') << right << m_lstItem[i]->m_serialNumber << "] "
                << setw(m_widthField) << setfill(' ') << left << m_lstItem[i]->m_itemName << " - "
                << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << endl;
        }
    }
}