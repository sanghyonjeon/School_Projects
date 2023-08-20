/* Citation and Sources...
Final Project Milestone 5
Module: PosIO
Filename: PosIO.cpp
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
#include "PosIO.h"

using namespace std;

namespace sdds {
    /***** HELPER FUNCTIONS ******/
    // Invokes the read method for PosIO objects to work with istream
    std::istream& operator>>(std::istream& is, PosIO& src) {
        return src.read(is);
    }

    // Invokes the write method for PosIO objects to work with ostream
    std::ostream& operator<<(std::ostream& os, const PosIO& src) {
        return src.write(os);
    }

    // Invokes the load method for PosIO objects to work with ifstream
    std::ifstream& operator>>(std::ifstream& ifs, PosIO& src) {
        return src.load(ifs);
    }

    // Invokes the save method for PosIO objects to work with ofstream
    std::ofstream& operator<<(std::ofstream& ofs, const PosIO& src) {
        return src.save(ofs);
    }
}