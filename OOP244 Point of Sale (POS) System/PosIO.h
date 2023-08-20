/* Citation and Sources...
Final Project Milestone 5
Module: PosIO
Filename: PosIO.h
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
#ifndef SDDS_POSIO_H_
#define SDDS_POSIO_H_
#include <iostream>
#include <fstream>

namespace sdds {
    class PosIO {
    public:
        /***** ISTREAM/OSTREAM VIRTUAL METHODS *****/
        // Pure virtual function for reading data from an istream
        virtual std::istream& read(std::istream& is) = 0;
        // Pure virtual function for writing data to an ostream (does not modify the owner)
        virtual std::ostream& write(std::ostream& os) const = 0;

        /***** IFSTREAM/OFSTREAM VIRTUAL METHODS *****/
        // Pure virtual function for loading data from an ifstream
        virtual std::ifstream& load(std::ifstream& ifs) = 0;
        // Pure virtual function for saving data to an ofstream (does not modify the owner)
        virtual std::ofstream& save(std::ofstream& ofs) const = 0;

        /***** VIRTUAL DESTRUCTOR *****/
        // Virtual empty destructor
        virtual ~PosIO() {};
    };

    /***** HELPER FUNCTIONS ******/
    // Invokes the read method for PosIO objects to work with istream
    std::istream& operator>>(std::istream& is, PosIO& src);
    // Invokes the write method for PosIO objects to work with ostream
    std::ostream& operator<<(std::ostream& os, const PosIO& src);
    // Invokes the load method for PosIO objects to work with ifstream
    std::ifstream& operator>>(std::ifstream& ifs, PosIO& src);
    // Invokes the save method for PosIO objects to work with ofstream
    std::ofstream& operator<<(std::ofstream& ofs, const PosIO& src);
}
#endif // !SDDS_POSIO_H_