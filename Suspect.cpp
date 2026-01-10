#include "Suspect.hpp"
#include <sstream>
#include <iostream>
#include <stdexcept>

namespace rmpg {

    // --- AUTOR: Piotr Grabowski (PG) ---

    const std::vector<std::string> Suspect::CRIME_TYPES = {
        "Theft",
        "Burglary",
        "Assault",
        "Fraud",
        "Disturbing the peace",
        "Other"
    };

    Suspect::Suspect()
        : Person(), crimeType("Other"), isDangerous(false) {}

    Suspect::Suspect(std::string fName,
                     std::string lName,
                     int age,
                     int id,
                     std::string crime,
                     bool dangerous)
        : Person(fName, lName, age, id),
          isDangerous(dangerous) {
        setCrimeType(crime);
    }

    Suspect::~Suspect() {}

    void Suspect::setCrimeType(std::string crime) {
        if (crime.empty()) {
            throw std::invalid_argument("Cannot be empty.");
        }
        crimeType = crime;
    }

    void Suspect::printCrimeMenu() {
        std::cout << "\n--- Available crimes ---\n";
        for (size_t i = 0; i < CRIME_TYPES.size(); ++i) {
            std::cout << (i + 1) << ". " << CRIME_TYPES[i] << "\n";
        }
    }

    std::string Suspect::crimeFromChoice(int choice) {
        if (choice < 1 || choice > static_cast<int>(CRIME_TYPES.size())) {
            throw std::out_of_range("Not a valid number");
        }
        return CRIME_TYPES[choice - 1];
    }

    std::string Suspect::toCSV() const {
        std::stringstream ss;
        ss << "S;"
           << id << ";"
           << firstName << ";"
           << lastName << ";"
           << age << ";"
           << crimeType << ";"
           << isDangerous;
        return ss.str();
    }

    bool Suspect::operator!() {
        isDangerous = !isDangerous;
        return isDangerous;
    }

    bool Suspect::getIsDangerous() const {
        return isDangerous;
    }

    std::string Suspect::getCrime() const {
        return crimeType;
    }
}
