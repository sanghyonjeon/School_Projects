/* Citation and Sources...
Final Project Milestone 5
Module: Perishable
Filename: Perishable.h
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
#ifndef SDDS_PERISHABLE_H_
#define SDDS_PERISHABLE_H_
#include "Item.h"
#include "Date.h"

namespace sdds {
    class Perishable : public Item {
        /***** PRIVATE MEMBER ATTRIBUTE *****/
        Date m_expiryDate;

    public:
        /***** INPUT AND OUTPUT FUNCTIONS *****/
        // Override the input and output functions of base Item class
        virtual std::istream& read(std::istream& is);
        virtual std::ostream& write(std::ostream& os) const;
        virtual std::ifstream& load(std::ifstream& ifs);
        virtual std::ofstream& save(std::ofstream& ofs) const;

        /***** OTHER PUBLIC MEMBER FUNCTION *****/
        // Override the itemType function of base Item class to return 'P'
        virtual char itemType() const;
    };

}
#endif // !SDDS_PERISHABLE_H_