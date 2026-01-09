
#pragma once
#ifndef OFFICER_HPP
#define OFFICER_HPP

#include "Person.hpp"

namespace rmpg {

    /**
     * @class Officer
     * @brief Klasa reprezentująca policjanta.
     * @details Dziedziczy po Person. Autor: Robert Moskal (RM)
     */
    class Officer : public Person {
    private:
        std::string rank;       ///< Stopień (np. Sierżant)
        int badgeNumber;        ///< Numer odznaki

    public:
        /**
         * @brief Konstruktor domyślny.
         */
        Officer();

        /**
         * @brief Konstruktor parametryczny.
         */
        Officer(std::string fName, std::string lName, int age, int id, std::string rank, int badge);

        /**
         * @brief Destruktor.
         */
        ~Officer() override;

        /**
         * @brief Przeciążony operator inkrementacji (awansuje oficera wirtualnie).
         * Przykład użycia operatora jednoargumentowego.
         */
        Officer& operator++();

        // Implementacja metody wirtualnej
        std::string toCSV() const override;

        // Gettery
        std::string getRank() const;
    };
}

#endif // OFFICER_HPP
