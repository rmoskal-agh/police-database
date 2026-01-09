


#include "Suspect.hpp"
#include <sstream>

namespace rmpg {

    // --- AUTOR: Piotr Grabowski (PG) ---

    Suspect::Suspect() : Person(), crimeType("Unknown"), isDangerous(false) {}

    Suspect::Suspect(std::string fName, std::string lName, int age, int id, std::string crime, bool dangerous)
        : Person(fName, lName, age, id), isDangerous(dangerous) {
        setCrimeType(crime);
    }

    Suspect::~Suspect() {}

    void Suspect::setCrimeType(std::string crime) {
        if (crime.empty()) {
            throw std::invalid_argument("Typ przestepstwa nie moze byc pusty!");
        }
        this->crimeType = crime;
    }

    std::string Suspect::toCSV() const {
        std::stringstream ss;
        // Format: S (jako Suspect), dane z Person, dane z Suspect
        ss << "S;" << id << ";" << firstName << ";" << lastName << ";" << age << ";" << crimeType << ";" << isDangerous;
        return ss.str();
    }

    // Operator ! zmienia status zagrożenia na przeciwny
    bool Suspect::operator!() {
        this->isDangerous = !this->isDangerous;
        return this->isDangerous;
    }
    
    bool Suspect::getIsDangerous() const { return isDangerous; }
    std::string Suspect::getCrime() const { return crimeType; }
}
