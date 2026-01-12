#pragma once
#ifndef POLICEDATABASE_HPP
#define POLICEDATABASE_HPP

#include "Person.hpp"
#include <vector>
#include <string>

namespace rmpg {

class PoliceDatabase {
private:
    std::vector<Person*> records;
    std::string dbFilename;

    void clearMemory();
    Person* findById(int id);

public:
    explicit PoliceDatabase(std::string filename);
    ~PoliceDatabase();

    void addPerson(Person* person);
    PoliceDatabase& operator+=(Person* p);

    void saveToFile();
    void loadFromFile();

    std::string getAllRecords() const;

    // 🔹 NEW
    bool removeById(int id);
    bool editById(int id);
};

}

#endif

