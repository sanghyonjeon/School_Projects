// Name: Sang Hyon Jeon
// Seneca Student ID: 113552194
// Seneca email: shjeon5@myseneca.ca
// Date of completion: August 5, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <string>

namespace sdds {
    class Station {
        int m_id{};
        std::string m_itemName{};
        std::string m_description{};
        size_t m_serialNumber{};
        size_t m_currentStock{};
        static size_t m_widthField;
        static int id_generator;
    public:
        Station() {};
        Station(const std::string& src);
        const std::string& getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(std::ostream& os, bool full) const;
    };
}

#endif // SDDS_STATION_H