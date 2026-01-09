

#pragma once
#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>
#include <iostream>

/**
 * @namespace rmpg
 * @brief Przestrzeń nazw dla projektu Roberta Moskala i Piotra Grabowskiego.
 */
namespace rmpg {

    /**
     * @class Person
     * @brief Klasa bazowa reprezentująca osobę w bazie danych.
     * @details Autor: Robert Moskal (RM)
     */
    class Person {
    protected:
        std::string firstName; ///< Imię osoby
        std::string lastName;  ///< Nazwisko osoby
        int age;               ///< Wiek osoby
        int id;                ///< Unikalne ID

        /// Stała statyczna dla celów optymalizacji
        static constexpr int MIN_AGE = 18;

    public:
        /**
         * @brief Konstruktor domyślny.
         */
        Person();

        /**
         * @brief Konstruktor parametryczny.
         * @param fName Imię
         * @param lName Nazwisko
         * @param age Wiek
         * @param id Numer ID
         */
        Person(std::string fName, std::string lName, int age, int id);

        /**
         * @brief Wirtualny destruktor.
         */
        virtual ~Person();

        // Gettery i Settery (z wyjątkami)
        void setAge(int newAge);
        int getAge() const;
        std::string getName() const;
        int getId() const;

        /**
         * @brief Metoda czysto wirtualna do pobierania danych w formacie CSV.
         * @return String z danymi oddzielonymi średnikami.
         */
        virtual std::string toCSV() const = 0;

        /**
         * @brief Przeciążony operator porównania.
         */
        bool operator==(const Person& other) const;

        /**
         * @brief Funkcja zaprzyjaźniona do wypisywania na strumień.
         */
        friend std::ostream& operator<<(std::ostream& os, const Person& p);
    };
}

#endif // PERSON_HPP
