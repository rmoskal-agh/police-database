#include <iostream>
#include <limits>
#include "Person.hpp"
#include "Officer.hpp"
#include "Suspect.hpp"
#include "PoliceDatabase.hpp"

// Funkcja pomocnicza do czyszczenia bufora wejścia
void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    // Inicjalizacja bazy danych (przestrzeń nazw PG)
    rmpg::PoliceDatabase db("police_db.txt");

    std::cout << "Welcome to Police Records (System provided by R. Moskal & P. Grabowski)\n";
    
    while (true) {
        std::cout << "\n1. Display all records\n";
        std::cout << "2. Add a police officer\n";
        std::cout << "3. Add a suspect\n";
        std::cout << "4. Save and close\n";
        std::cout << "Choice: ";

        int choice;
        if (!(std::cin >> choice)) {
            clearInput();
            continue;
        }

        if (choice == 4) break;

        try {
            if (choice == 1) {
                // Wyświetlanie danych zwróconych przez klasę (nie klasa drukuje!)
                std::cout << db.getAllRecords();
            }
            else if (choice == 2) {
                std::string fName, lName, rank;
                int age, id, badge;
                
                std::cout << "First name: "; std::cin >> fName;
                std::cout << "Last name: "; std::cin >> lName;
                std::cout << "Age: "; std::cin >> age;
                std::cout << "ID: "; std::cin >> id;
                std::cout << "Rank: "; std::cin >> rank;
                std::cout << "Badge ID: "; std::cin >> badge;

                // Tworzenie obiektu dynamicznie (polimorfizm)
                rmpg::Officer* newOfficer = new rmpg::Officer(fName, lName, age, id, rank, badge);
                
                // Demonstracja operatora RM (awans)
                std::cout << "Do you want to promote this person? (1-Yes, 0-No): ";
                int promote;
                std::cin >> promote;
                if(promote) {
                    ++(*newOfficer); // Operator ++
                }

                db += newOfficer; // Użycie operatora += z klasy PG
                std::cout << "A police officer has been added.\n";
            }
            else if (choice == 3) {
                std::string fName, lName;
                int age, id;
                bool dangerous;
                            
                std::cout << "First name: "; std::cin >> fName;
                std::cout << "Last name: "; std::cin >> lName;
                std::cout << "Age: "; std::cin >> age;
                std::cout << "ID: "; std::cin >> id;
            
                rmpg::Suspect::printCrimeMenu();
            
                int crimeChoice;
                std::cout << "Choice: ";
                std::cin >> crimeChoice;
            
                std::string crime = rmpg::Suspect::crimeFromChoice(crimeChoice);
            
                std::cout << "Are they dangerous (1-Yes, 0-No): ";
                std::cin >> dangerous;
            
                rmpg::Suspect* newSuspect =
                    new rmpg::Suspect(fName, lName, age, id, crime, dangerous);
            
                db.addPerson(newSuspect);
                std::cout << "A suspect has been added.\n";
            }

        }
        catch (const std::exception& e) {
            std::cerr << "[Error]: " << e.what() << "\n";
        }
    }

    std::cout << "Data has been saved succesfully. End of session.\n";
    return 0;
}
