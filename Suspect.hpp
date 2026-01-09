
#pragma once
#ifndef SUSPECT_HPP
#define SUSPECT_HPP

#include "Person.hpp"

namespace rmpg {

    /**
     * @class Suspect
     * @brief Klasa reprezentująca podejrzanego/przestępcę.
     * @details Dziedziczy po Person. Autor: Piotr Grabowski (PG)
     */
    class Suspect : public Person {
    private:
        std::string crimeType;  ///< Rodzaj przestępstwa
        bool isDangerous;       ///< Czy jest niebezpieczny

    public:
        /**
         * @brief Konstruktor domyślny.
         */
        Suspect();

        /**
         * @brief Konstruktor parametryczny.
         */
        Suspect(std::string fName, std::string lName, int age, int id, std::string crime, bool dangerous);

        /**
         * @brief Destruktor.
         */
        ~Suspect() override;

        /**
         * @brief Setter z walidacją (rzuca wyjątek).
         */
        void setCrimeType(std::string crime);

        // Implementacja metody wirtualnej
        std::string toCSV() const override;

        /**
         * @brief Przeciążony operator negacji.
         * Zmienia status niebezpieczeństwa (np. po resocjalizacji).
         */
        bool operator!();
        
        bool getIsDangerous() const;
        std::string getCrime() const;
    };
}

#endif // SUSPECT_HPP
