#pragma once
#ifndef SUSPECT_HPP
#define SUSPECT_HPP

#include "Person.hpp"
#include <string>
#include <vector>

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

        static const std::vector<std::string> CRIME_TYPES;

    public:
        // Konstruktory
        Suspect();
        Suspect(std::string fName,
                std::string lName,
                int age,
                int id,
                std::string crime,
                bool dangerous);

        ~Suspect() override;

        // Logika przestępstw (MENU)
        static void printCrimeMenu();
        static std::string crimeFromChoice(int choice);

        // Settery / gettery
        void setCrimeType(std::string crime);
        bool getIsDangerous() const;
        std::string getCrime() const;

        // CSV
        std::string toCSV() const override;

        // Operator
        bool operator!();
    };
}

#endif // SUSPECT_HPP

