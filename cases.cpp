
#include "Case.hpp"
#include <algorithm> // do std::find

namespace rmpg {

    // Lista dozwolonych typów (hardcoded choices)
    const std::vector<std::string> VALID_TYPES = {
        "Theft", 
        "Burglary", 
        "Disrupting peace", 
        "Assault",
        "Other"
    };

    Case::Case() : id(0), type("Other"), description("No description") {}

    Case::Case(int id, std::string t, std::string desc) : id(id), description(desc) {
        setType(t); // Używamy settera do walidacji
    }

    Case::~Case() {}

    bool Case::isValidType(const std::string& t) const {
        for (const auto& valid : VALID_TYPES) {
            if (valid == t) return true;
        }
        return false;
    }

    void Case::setType(std::string newType) {
        if (isValidType(newType)) {
            this->type = newType;
        } else {
            // Jeśli użytkownik wpisze coś dziwnego, ustawiamy "Other"
            std::cout << "[INFO] Unknown type: " << newType << ". Set as 'Other'.\n";
            this->type = "Other";
        }
    }

    std::string Case::getType() const { return type; }
    std::string Case::getDescription() const { return description; }
    int Case::getId() const { return id; }

    std::string Case::toCSV() const {
        // Format: C;ID;TYP;OPIS
        return "C;" + std::to_string(id) + ";" + type + ";" + description;
    }

    void Case::printAvailableTypes() {
        std::cout << "Select a type from the following: ";
        for (const auto& t : VALID_TYPES) {
            std::cout << "[" << t << "] ";
        }
        std::cout << "\n";
    }
}
