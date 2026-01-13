#pragma once
#ifndef POLICEDATABASE_HPP
#define POLICEDATABASE_HPP

#include "Person.hpp"
#include <vector>
#include <string>

namespace rmpg {

    /**
     * @class PoliceDatabase
     * @brief Main database management class.
     *
     * @details This class is responsible for storing, managing and persisting
     * records of police officers and suspects. It owns dynamically allocated
     * Person-derived objects and handles file input/output in CSV format.
     */
    class PoliceDatabase {
    private:
        /**
         * @brief Polymorphic container holding all records.
         *
         * Stores pointers to Person base class to enable runtime polymorphism
         * between Officer and Suspect objects.
         */
        std::vector<Person*> records;

        /**
         * @brief Name of the database file used for persistence.
         */
        std::string dbFilename;

        /**
         * @brief Frees all dynamically allocated records and clears the container.
         *
         * Used internally during destruction and file reload to avoid memory leaks.
         */
        void clearMemory();

        /**
         * @brief Finds a record by its unique ID.
         * @param id ID of the person to search for
         * @return Pointer to Person if found, nullptr otherwise
         */
        Person* findById(int id);

    public:
        /**
         * @brief Explicit constructor of the database.
         * @param filename Name of the file used for saving and loading records
         *
         * Automatically attempts to load data from the given file.
         */
        explicit PoliceDatabase(std::string filename);

        /**
         * @brief Destructor.
         *
         * Saves all records to file and releases allocated memory.
         */
        ~PoliceDatabase();

        /**
         * @brief Adds a new person to the database.
         * @param person Pointer to dynamically allocated Person-derived object
         */
        void addPerson(Person* person);

        /**
         * @brief Overloaded += operator for adding a record.
         *
         * Acts as an alternative interface to addPerson().
         */
        PoliceDatabase& operator+=(Person* p);

        /**
         * @brief Saves all records to file in CSV format.
         */
        void saveToFile();

        /**
         * @brief Loads records from file.
         *
         * Existing records are cleared before loading to prevent duplication.
         */
        void loadFromFile();

        /**
         * @brief Returns all records formatted as a readable string.
         * @return String representation of the entire database
         */
        std::string getAllRecords() const;

        /**
         * @brief Removes a record with a given ID.
         * @param id ID of the record to remove
         * @return true if a record was removed, false otherwise
         */
        bool removeById(int id);

        /**
         * @brief Edits a record with a given ID.
         *
         * Allows modification of selected fields depending on the actual
         * runtime type (Officer or Suspect).
         *
         * @param id ID of the record to edit
         * @return true if record was found and edited, false otherwise
         */
        bool editById(int id);

        /**
         * @brief Prints database statistics.
         *
         * Displays number of officers, suspects and crime-type distribution
         * based on the currently loaded records.
         */
        void printStatistics() const;
    };
}

#endif // POLICEDATABASE_HPP

