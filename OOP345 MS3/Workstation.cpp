// Name: Sang Hyon Jeon
// Seneca Student ID: 113552194
// Seneca email: shjeon5@myseneca.ca
// Date of completion: August 5, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Workstation.h"

using namespace std;

namespace sdds {

	deque<CustomerOrder> g_pending{};
	deque<CustomerOrder> g_completed{};
	deque<CustomerOrder> g_incomplete{};

	Workstation::Workstation(const string& str) : Station(str), m_pNextStation(nullptr) {}

	
	void Workstation::fill(ostream& os) {
		if (!m_orders.empty()) {
			m_orders.front().fillItem(*this, os);
		}
	}
	
	bool Workstation::attemptToMoveOrder() {
		bool orderMoved{ false };

		if (!m_orders.empty()) {
			if (m_orders.front().isItemFilled(getItemName()) || getQuantity() == 0) {
				if (m_pNextStation) {
					*m_pNextStation += move(m_orders.front());
				}
				else {
					if (m_orders.front().isOrderFilled()) {
						g_completed.push_back(move(m_orders.front()));
					}
					else {
						g_incomplete.push_back(move(m_orders.front()));
					}
				}

				m_orders.pop_front();
				orderMoved = true;
			}
		}

		return orderMoved;
	}
	
	void Workstation::setNextStation(Workstation* station) {
		m_pNextStation = station;
	}

	Workstation* Workstation::getNextStation() const {
		return m_pNextStation;
	}

	void Workstation::display(ostream& os) const {
		if (m_pNextStation) {
			os << getItemName() << " --> " << m_pNextStation->getItemName() << '\n';
		}
		else {
			os << getItemName() << " --> End of Line\n";
		}
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
		m_orders.push_back(move(newOrder));
		return *this;
	}
}