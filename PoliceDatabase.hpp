

#pragma once
#ifndef POLICEDATABASE_HPP
#define POLICEDATABASE_HPP

#include "Person.hpp"
#include <vector>
#include <string>

namespace rmpg {

    /**
     * @class PoliceDatabase
     * @brief Główna klasa zarządzająca bazą danych.
     * @details Odpowiada za I/O i przechowywanie obiektów. Autor: Piotr Grabowski (PG)
     */
    class PoliceDatabase {
    private:
        // Polimorficzny kontener - przechowuje wskaźniki do klasy bazowej
        std::vector<Person*> records;
        std::string dbFilename;

        // Metoda pomocnicza do czyszczenia pamięci
        void clearMemory();

    public:
        /**
         * @brief Konstruktor bazy danych.
         * @param filename Nazwa pliku do zapisu/odczytu.
         */
        explicit PoliceDatabase(std::string filename);

        /**
         * @brief Destruktor. Zwalnia pamięć.
         */
        ~PoliceDatabase();

        // Metody zarządzające
        void addPerson(Person* person);
        void saveToFile();
        void loadFromFile();
        
        // Zwraca string do wyświetlenia (nie drukuje sama!)
        std::string getAllRecords() const;

        /**
         * @brief Przeciążony operator += do dodawania osoby.
         */
        PoliceDatabase& operator+=(Person* p);
    };
}

#endif // POLICEDATABASE_HPP
