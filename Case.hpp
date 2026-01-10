
#ifndef CASE_HPP
#define CASE_HPP

#include <string>
#include <iostream>
#include <vector>

namespace rmpg {

    /**
     * @class Case
     * @brief Klasa reprezentująca sprawę policyjną.
     * @details Autor: Robert Moskal (RM)
     */
    class Case {
    private:
        int id;                     ///< ID sprawy
        std::string type;           ///< Typ (Theft, Burglary, etc.)
        std::string description;    ///< Opis zdarzenia

        // Pomocnicza metoda do sprawdzania typu
        bool isValidType(const std::string& t) const;

    public:
        // Konstruktory
        Case();
        Case(int id, std::string type, std::string description);

        // Destruktor
        ~Case();

        // Settery i Gettery
        void setType(std::string newType);
        std::string getType() const;
        std::string getDescription() const;
        int getId() const;

        /**
         * @brief Zwraca format CSV do zapisu.
         */
        std::string toCSV() const;

        /**
         * @brief Wyświetla dostępne typy przestępstw.
         */
        static void printAvailableTypes();
    };
}

#endif // CASE_HPP
