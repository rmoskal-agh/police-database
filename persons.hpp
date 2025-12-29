#pragma once

#include <string>
#include <vector>
#include <optional>
#include <cstdint>

namespace rmpg {

/**
 * @brief Enumeration describing the current status of a person, used to provide accurate date
 */
enum class PersonStatus {
    Free,
    Arrested,
    Imprisoned,
    Deceased
};

/**
 * @brief Base class representing a person in the police database.
 */
class Person {
public:
    Person() = default;
    Person(std::string firstName, std::string lastName);

    virtual ~Person() = default;

    [[nodiscard]] const std::string& getFirstName() const noexcept;
    [[nodiscard]] const std::string& getLastName() const noexcept;

    void setFirstName(const std::string& firstName);
    void setLastName(const std::string& lastName);

    [[nodiscard]] virtual PersonStatus getStatus() const noexcept = 0;

protected:
    std::string m_firstName;
    std::string m_lastName;
};

/**
 * @brief Represents a living person (base for all non-deceased persons).
 */
class LivingPerson : public Person {
public:
    LivingPerson() = default;
    LivingPerson(std::string firstName,
                 std::string lastName,
                 std::string dateOfBirth);

    [[nodiscard]] const std::string& getDateOfBirth() const noexcept;

    bool setDateOfBirth(const std::string& dateOfBirth);

protected:
    std::string m_dateOfBirth; // YYYY-MM-DD
};

/**
 * @brief Represents a free person (not arrested or imprisoned).
 */
class FreePerson final : public LivingPerson {
public:
    using LivingPerson::LivingPerson;

    [[nodiscard]] PersonStatus getStatus() const noexcept override;
};

/**
 * @brief Represents a person currently under arrest.
 */
class ArrestedPerson final : public LivingPerson {
public:
    ArrestedPerson() = default;
    ArrestedPerson(std::string firstName,
                    std::string lastName,
                    std::string dateOfBirth,
                    std::vector<std::uint32_t> relatedCaseIds);

    [[nodiscard]] PersonStatus getStatus() const noexcept override;

    [[nodiscard]] const std::vector<std::uint32_t>& getRelatedCases() const noexcept;
    void addCase(std::uint32_t caseId);

private:
    std::vector<std::uint32_t> m_relatedCaseIds;
};

/**
 * @brief Represents a person serving a prison sentence.
 */
class ImprisonedPerson final : public LivingPerson {
public:
    ImprisonedPerson() = default;
    ImprisonedPerson(std::string firstName,
                     std::string lastName,
                     std::string dateOfBirth,
                     std::string imprisonmentStartDate,
                     std::uint32_t sentenceLengthMonths,
                     std::vector<std::uint32_t> relatedCaseIds);

    [[nodiscard]] PersonStatus getStatus() const noexcept override;

    [[nodiscard]] const std::string& getImprisonmentStartDate() const noexcept;
    [[nodiscard]] std::uint32_t getSentenceLengthMonths() const noexcept;
    [[nodiscard]] const std::vector<std::uint32_t>& getRelatedCases() const noexcept;

private:
    std::string m_imprisonmentStartDate; // YYYY-MM-DD
    std::uint32_t m_sentenceLengthMonths {0};
    std::vector<std::uint32_t> m_relatedCaseIds;
};

/**
 * @brief Represents a deceased person.
 */
class DeceasedPerson final : public Person {
public:
    DeceasedPerson() = default;
    DeceasedPerson(std::string firstName,
                   std::string lastName,
                   std::string dateOfDeath,
                   std::string causeOfDeath);

    [[nodiscard]] PersonStatus getStatus() const noexcept override;

    [[nodiscard]] const std::string& getDateOfDeath() const noexcept;
    [[nodiscard]] const std::string& getCauseOfDeath() const noexcept;

private:
    std::string m_dateOfDeath;   // YYYY-MM-DD
    std::string m_causeOfDeath; // NOT case_id in which that person died 
};

} // namespace rmpg

