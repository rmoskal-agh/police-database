#pragma once
#ifndef SUSPECT_HPP
#define SUSPECT_HPP

#include "Person.hpp"
#include <string>
#include <vector>

namespace rmpg {

    /**
     * @class Suspect
     * @brief Class that represent a suspect, an singual entry in the database.
     * @details inherits from Person, type of crimes are limited to 5 + "other" for the simplicity
     * of gathering statistics. See Suspect.cpp for reference
     */
    class Suspect : public Person {
    private:
        std::string crimeType;  
        bool isDangerous;       

        static const std::vector<std::string> CRIME_TYPES;

    public:
        
        Suspect();
        Suspect(std::string fName,
                std::string lName,
                int age,
                int id,
                std::string crime,
                bool dangerous);

        ~Suspect() override;

        // Uses crime menu. See Suspect.cpp for reference
        static void printCrimeMenu();
        static std::string crimeFromChoice(int choice);

        
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
