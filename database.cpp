#include "PoliceDatabase.hpp"
#include "Officer.hpp"
#include "Suspect.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>  

namespace rmpg {

    PoliceDatabase::PoliceDatabase(std::string filename) : dbFilename(filename) {
        loadFromFile();
    }

    PoliceDatabase::~PoliceDatabase() {
        saveToFile();
        clearMemory();
    }

    void PoliceDatabase::clearMemory() {
        for (Person* p : records) {
            delete p;
        }
        records.clear();
    }

    void PoliceDatabase::addPerson(Person* person) {
        records.push_back(person);
    }

    PoliceDatabase& PoliceDatabase::operator+=(Person* p) {
        addPerson(p);
        return *this;
    }

    void PoliceDatabase::saveToFile() {
        std::ofstream file(dbFilename);
        if (!file) return;

        for (const auto* p : records) {
            file << p->toCSV() << "\n";
        }
    }

    void PoliceDatabase::loadFromFile() {
        clearMemory();
        std::ifstream file(dbFilename);
        if (!file) return;

        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::vector<std::string> parts;
            std::string seg;

            while (std::getline(ss, seg, ';')) {
                parts.push_back(seg);
            }

            if (parts.empty()) continue;

            try {
                char type = parts[0][0];
                int id = std::stoi(parts[1]);
                std::string fn = parts[2];
                std::string ln = parts[3];
                int age = std::stoi(parts[4]);

                if (type == 'O') {
                    records.push_back(new Officer(
                        fn, ln, age, id,
                        parts[5], std::stoi(parts[6])
                    ));
                }
                else if (type == 'S') {
                    records.push_back(new Suspect(
                        fn, ln, age, id,
                        parts[5], (parts[6] == "1")
                    ));
                }
            }
            catch (...) {
                continue;
            }
        }
    }

    std::string PoliceDatabase::getAllRecords() const {
        std::stringstream ss;
        ss << "--- Police Database ---\n";
        for (const auto* p : records) {
            ss << *p; 
            
            if (const Officer* o = dynamic_cast<const Officer*>(p)) {
                ss << " [OFFICER: " << o->getRank() << "]";
            }
            else if (const Suspect* s = dynamic_cast<const Suspect*>(p)) {
                ss << " [SUSPECT: " << s->getCrime()
                   << (s->getIsDangerous() ? " !" : "") << "]";
            }
            ss << "\n";
        }
        return ss.str();
    }

    Person* PoliceDatabase::findById(int id) {
        for (auto* p : records) {
            if (p->getId() == id) return p;
        }
        return nullptr;
    }

    bool PoliceDatabase::removeById(int id) {
        for (auto it = records.begin(); it != records.end(); ++it) {
            if ((*it)->getId() == id) {
                delete *it;
                records.erase(it);
                return true;
            }
        }
        return false;
    }

    bool PoliceDatabase::editById(int id) {
        Person* p = findById(id);
        if (!p) return false;

        std::cout << "\nEditing record ID " << id << "\n";
        std::cout << "What do you want to edit?\n";
        std::cout << "1. Age\n";
        
        bool isOfficer = (dynamic_cast<Officer*>(p) != nullptr);
        bool isSuspect = (dynamic_cast<Suspect*>(p) != nullptr);

        if (isOfficer) std::cout << "2. Officer rank\n";
        if (isSuspect) {
            std::cout << "3. Crime type\n";
            std::cout << "4. Dangerous flag\n";
        }

        std::cout << "Choice: ";
        int choice;
        std::cin >> choice;

        try {
            if (choice == 1) {
                int newAge;
                std::cout << "New age: ";
                std::cin >> newAge;
                p->setAge(newAge);
            }
            else if (choice == 2 && isOfficer) {
                Officer* o = dynamic_cast<Officer*>(p);
                std::string newRank;
                std::cout << "New rank: ";
                std::cin >> newRank;
                *o = Officer(o->getName(), "", o->getAge(), o->getId(), newRank, 0); 
            }
            else if (choice == 3 && isSuspect) {
                Suspect* s = dynamic_cast<Suspect*>(p);
                Suspect::printCrimeMenu();
                int c;
                std::cout << "Choice: ";
                std::cin >> c;
                s->setCrimeType(Suspect::crimeFromChoice(c));
            }
            else if (choice == 4 && isSuspect) {
                Suspect* s = dynamic_cast<Suspect*>(p);
                !(*s);
                std::cout << "Dangerous status toggled.\n";
            }
            else {
                std::cout << "Invalid choice.\n";
                return false;
            }
        }
        catch (const std::exception& e) {
            std::cout << "[Error] " << e.what() << "\n";
            return false;
        }

        std::cout << "Record updated successfully.\n";
        return true;
    }

    void PoliceDatabase::printStatistics() const {
        int officerCount = 0;
        int suspectCount = 0;
        std::map<std::string, int> crimeStats;

        for (const auto* p : records) {
            if (dynamic_cast<const Officer*>(p)) {
                officerCount++;
            }
            else if (const Suspect* s = dynamic_cast<const Suspect*>(p)) {
                suspectCount++;
                crimeStats[s->getCrime()]++;
            }
        }

        std::cout << "\n=== STATISTICS REPORT ===\n";
        std::cout << "Total Officers: " << officerCount << "\n";
        std::cout << "Total Suspects: " << suspectCount << "\n";
        std::cout << "--- Crimes Breakdown ---\n";
        
        if (crimeStats.empty()) {
            std::cout << "(No crimes recorded)\n";
        } else {
            for (const auto& entry : crimeStats) {
                std::cout << " - " << entry.first << ": " << entry.second << "\n";
            }
        }
        std::cout << "=========================\n";
    }

}


