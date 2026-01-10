
#include "PoliceDatabase.hpp"
#include "Officer.hpp"
#include "Suspect.hpp"
#include <fstream>
#include <sstream>
#include <iostream> // Tylko do debugowania w razie błędów krytycznych

namespace rmpg {

    // --- AUTOR: Piotr Grabowski (PG) ---

    PoliceDatabase::PoliceDatabase(std::string filename) : dbFilename(filename) {
        // Próba załadowania danych przy starcie
        loadFromFile();
    }

    PoliceDatabase::~PoliceDatabase() {
        // Zapis przy wyjściu
        saveToFile();
        clearMemory();
    }

    void PoliceDatabase::clearMemory() {
        for (Person* p : records) {
            delete p; // Ręczne zarządzanie pamięcią (wymagane w zadaniu zamiast smart pointers)
        }
        records.clear();
    }

    void PoliceDatabase::addPerson(Person* person) {
        records.push_back(person);
    }

    // Przeciążenie operatora += jako alternatywa dla addPerson
    PoliceDatabase& PoliceDatabase::operator+=(Person* p) {
        this->addPerson(p);
        return *this;
    }

    void PoliceDatabase::saveToFile() {
        std::ofstream file(dbFilename);
        if (file.is_open()) {
            for (const auto* p : records) {
                file << p->toCSV() << "\n";
            }
            file.close();
        }
    }

    void PoliceDatabase::loadFromFile() {
        // Najpierw czyścimy obecną pamięć, żeby nie dublować przy reloadzie
        clearMemory();

        std::ifstream file(dbFilename);
        std::string line;

        if (!file.is_open()) return; // Jeśli plik nie istnieje, po prostu zaczynamy z pustą bazą

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string segment;
            std::vector<std::string> parts;

            while (std::getline(ss, segment, ';')) {
                parts.push_back(segment);
            }

            if (parts.empty()) continue;

            // Parsowanie CSV - prosty parser studencki
            try {
                char type = parts[0][0];
                int id = std::stoi(parts[1]);
                std::string fName = parts[2];
                std::string lName = parts[3];
                int age = std::stoi(parts[4]);

                if (type == 'O') {
                    // Officer
                    std::string rank = parts[5];
                    int badge = std::stoi(parts[6]);
                    records.push_back(new Officer(fName, lName, age, id, rank, badge));
                } 
                else if (type == 'S') {
                    // Suspect
                    std::string crime = parts[5];
                    bool dangerous = (parts[6] == "1");
                    records.push_back(new Suspect(fName, lName, age, id, crime, dangerous));
                }
            } catch (...) {
                // Ignorujemy uszkodzone linie
                continue;
            }
        }
        file.close();
    }

    std::string PoliceDatabase::getAllRecords() const {
        std::stringstream ss;
        ss << "--- Police Database ---\n";
        if (records.empty()) {
            ss << "(No records available)\n";
        }
        for (const auto* p : records) {
            // Używamy polimorfizmu i przeciążonego operatora <<
            ss << *p; // To wywoła operator<< z Person.cpp
            
            // Rzutowanie dynamiczne (RTTI) aby pokazać szczegóły specyficzne dla klas
            if (const Officer* o = dynamic_cast<const Officer*>(p)) {
                ss << " [OFFICER: " << o->getRank() << "]";
            } else if (const Suspect* s = dynamic_cast<const Suspect*>(p)) {
                ss << " [SUSPECT: " << s->getCrime() << (s->getIsDangerous() ? " !" : "") << "]";
            }
            ss << "\n";
        }
        return ss.str();
    }
}
