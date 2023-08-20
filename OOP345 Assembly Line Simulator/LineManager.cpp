// Name: Sang Hyon Jeon
// Seneca Student ID: 113552194
// Seneca email: shjeon5@myseneca.ca
// Date of completion: August 5, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <algorithm>
#include "Utilities.h"
#include "LineManager.h"

using namespace std;

namespace sdds {
    LineManager::LineManager(const string& file, const vector<Workstation*>& stations) {
        ifstream myFile(file);

        if (!myFile) {
            throw string("Unable to open the file: " + file);
        }

        string line;
        Utilities utilities;

        while (getline(myFile, line)) {
            size_t next_pos = 0;
            bool more = true;

            string stationName = utilities.extractToken(line, next_pos, more);

            auto stationIterator = find_if(stations.begin(), stations.end(), [&stationName](const Workstation* station) {
                return station->getItemName() == stationName;
                });

            if (stationIterator == stations.end()) {
                throw string("Station not found: " + stationName);
            }

            if (more) {
                string nextStationName = utilities.extractToken(line, next_pos, more);

                auto nextStationIterator = find_if(stations.begin(), stations.end(), [&nextStationName](const Workstation* station) {
                    return station->getItemName() == nextStationName;
                    });

                if (nextStationIterator == stations.end()) {
                    throw string("Next station not found: " + nextStationName);
                }

                (*stationIterator)->setNextStation(*nextStationIterator);
            }

            m_activeLine.push_back(*stationIterator);
        }

        m_firstStation = *find_if(m_activeLine.begin(), m_activeLine.end(), [this](const Workstation* station) {
            return none_of(m_activeLine.begin(), m_activeLine.end(), [&station](const Workstation* otherStation) {
                return otherStation->getNextStation() == station;
                });
            });

        if (!m_firstStation) {
            throw string("First Station not found");
        }

        m_cntCustomerOrder = g_pending.size();
    }

    void LineManager::reorderStations() {
        vector<Workstation*> ordered{};
        Workstation* station{ m_firstStation };

        while (station) {
            ordered.push_back(station);
            station = station->getNextStation();
        }

        m_activeLine = ordered;
    }

    bool LineManager::run(ostream& os) {
        static size_t iterationCount{};

        ++iterationCount;

        os << "Line Manager Iteration: " << iterationCount << endl;

        if (!g_pending.empty()) {
            *m_firstStation += move(g_pending.front());
            g_pending.pop_front();
        }

        for (auto& station : m_activeLine) {
            station->fill(os);
        }

        for (auto& station : m_activeLine) {
            station->attemptToMoveOrder();
        }

        return (g_completed.size() + g_incomplete.size()) == m_cntCustomerOrder;
    }

    void LineManager::display(ostream& os) const {
        for (const auto& station : m_activeLine) {
            station->display(os);
        }
    }
}