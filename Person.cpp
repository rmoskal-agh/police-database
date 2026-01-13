
#include "Person.hpp"
#include <stdexcept>

namespace rmpg {

    Person::Person() : firstName("Unknown"), lastName("Unknown"), age(MIN_AGE), id(0) {}

    Person::Person(std::string fName, std::string lName, int a, int i) 
        : firstName(fName), lastName(lName), id(i) {
        setAge(a); 
    }

    Person::~Person() {
    }

    void Person::setAge(int newAge) {
        if (newAge < MIN_AGE) {
            throw std::invalid_argument("Individuals whose ages are lower than 18 are not allowed to be recorded here.");
        }
        this->age = newAge;
    }

    int Person::getAge() const {
        return this->age;
    }

    std::string Person::getName() const {
        return firstName + " " + lastName;
    }

    int Person::getId() const {
        return id;
    }

    bool Person::operator==(const Person& other) const {
        return (this->id == other.id);
    }

    std::ostream& operator<<(std::ostream& os, const Person& p) {
        os << "ID: " << p.id << " | " << p.firstName << " " << p.lastName << " (" << p.age << " years old)";
        return os;
    }
}
