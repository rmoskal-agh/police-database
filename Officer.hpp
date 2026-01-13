
#pragma once
#ifndef OFFICER_HPP
#define OFFICER_HPP

#include "Person.hpp"

namespace rmpg {

    /**
     * @class Officer
     * @brief This class represents a single entry of the Officer (depitcted O in the database file)
     * @details Inherits from class Person
     */
    class Officer : public Person {
    private:
        std::string rank;       
        int badgeNumber;        

    public:
        /**
         * @brief Default constructor
         */
        Officer();

        /**
         * @brief Parametrical constructor 
         */
        Officer(std::string fName, std::string lName, int age, int id, std::string rank, int badge);

        
        ~Officer() override;

        /**
         * @brief Overload of on operator here implies promoting of an officer 
         * Serves as an example of overloading a single-argument operator 
         */
        Officer& operator++();

        // an implification of an virtual metod
        std::string toCSV() const override;

        std::string getRank() const;
    };
}

#endif // OFFICER_HPP
