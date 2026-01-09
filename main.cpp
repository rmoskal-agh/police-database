
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

    std::cout << "Witaj w Systemie Policyjnym (Autorzy: R. Moskal & P. Grabowski)\n";
    
    while (true) {
        std::cout << "\n1. Wyswietl baze\n";
        std::cout << "2. Dodaj Policjanta (RM)\n";
        std::cout << "3. Dodaj Podejrzanego (PG)\n";
        std::cout << "4. Zapisz i Wyjdz\n";
        std::cout << "Wybor: ";

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
                
                std::cout << "Imie: "; std::cin >> fName;
                std::cout << "Nazwisko: "; std::cin >> lName;
                std::cout << "Wiek: "; std::cin >> age;
                std::cout << "ID: "; std::cin >> id;
                std::cout << "Stopien: "; std::cin >> rank;
                std::cout << "Nr odznaki: "; std::cin >> badge;

                // Tworzenie obiektu dynamicznie (polimorfizm)
                rmpg::Officer* newOfficer = new rmpg::Officer(fName, lName, age, id, rank, badge);
                
                // Demonstracja operatora RM (awans)
                std::cout << "Czy awansowac od razu? (1-Tak, 0-Nie): ";
                int promote;
                std::cin >> promote;
                if(promote) {
                    ++(*newOfficer); // Operator ++
                }

                db += newOfficer; // Użycie operatora += z klasy PG
                std::cout << "Dodano policjanta.\n";
            }
            else if (choice == 3) {
                std::string fName, lName, crime;
                int age, id;
                bool dangerous;
                
                std::cout << "Imie: "; std::cin >> fName;
                std::cout << "Nazwisko: "; std::cin >> lName;
                std::cout << "Wiek: "; std::cin >> age;
                std::cout << "ID: "; std::cin >> id;
                std::cout << "Przestepstwo: "; std::cin >> crime;
                std::cout << "Czy niebezpieczny (1-Tak, 0-Nie): "; std::cin >> dangerous;

                rmpg::Suspect* newSuspect = new rmpg::Suspect(fName, lName, age, id, crime, dangerous);
                
                // Demonstracja metody i obsługi wyjątków przy tworzeniu
                // (wyjątek zostanie rzucony w konstruktorze jeśli dane są złe, np. wiek < 18)

                db.addPerson(newSuspect);
                std::cout << "Dodano podejrzanego.\n";
            }
        }
        catch (const std::exception& e) {
            std::cerr << "[BLAD]: " << e.what() << "\n";
        }
    }

    std::cout << "Zapisano dane. Koniec programu.\n";
    return 0;
}
