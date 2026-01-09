


#include "Officer.hpp"
#include <sstream>

namespace rmpg {

    // --- AUTOR: Robert Moskal (RM) ---

    Officer::Officer() : Person(), rank("Cadet"), badgeNumber(0) {}

    Officer::Officer(std::string fName, std::string lName, int age, int id, std::string r, int badge)
        : Person(fName, lName, age, id), rank(r), badgeNumber(badge) {}

    Officer::~Officer() {}

    // Operator ++ "awansuje" oficera przez dodanie "+" do rangi
    // Jest to przykład "studenckiego" przeciążenia operatora
    Officer& Officer::operator++() {
        this->rank += "+";
        return *this;
    }

    std::string Officer::toCSV() const {
        std::stringstream ss;
        // Format: O (jako Officer), dane z Person, dane z Officer
        ss << "O;" << id << ";" << firstName << ";" << lastName << ";" << age << ";" << rank << ";" << badgeNumber;
        return ss.str();
    }

    std::string Officer::getRank() const {
        return rank;
    }
}
