

#pragma once
#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>
#include <iostream>

namespace rmpg {

    /**
     * @class Person
     * @brief A core class that represent an entry in the database. Both suspect and officer inherit for it.
     * @details First and last name, age and ID are universal for every entry. ID cannot be edited by program later on.
     */
    class Person {
    protected:
        std::string firstName; 
        std::string lastName;  
        int age;               
        int id;                

        /// using of constexpr for the sake of optimalization
        static constexpr int MIN_AGE = 18;

    public:
        /**
         * @brief deafault constructor
         */
        Person();

        /**
         * @brief parametrical constructor
         * @param fName first name
         * @param lName last name
         * @param age not lower than 18, 
         * @param id 
         */
        Person(std::string fName, std::string lName, int age, int id);

        
        virtual ~Person();

        
        void setAge(int newAge);
        int getAge() const;
        std::string getName() const;
        int getId() const;

        /**
         * @brief Virtual metod used to download data in CSV format
         * @return strings separated by semicolons (;) see police_db.txt file for reference
         */
        virtual std::string toCSV() const = 0;

        /**
         * @brief overloaded compare operator
         */
        bool operator==(const Person& other) const;

        /**
        * @brief Friend stream operator for printing Person objects.
         *
         * Enables formatted output of a Person instance using standard streams.
         */
        friend std::ostream& operator<<(std::ostream& os, const Person& p);
    };
}

#endif // PERSON_HPP

