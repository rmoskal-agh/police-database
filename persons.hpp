#pragma once

#include <string>
#include <vector>
#include <optional>
#include <stdexcept>

namespace rmpg {

enum class PersonStatus {
    Free,
    InPrison,
    InCustody,
    Deceased
};

class Person {
private:
    // basic data, applies to every entry
    std::string firstName_;
    std::string lastName_;
    std::string birthDate_;   // YYYY-MM-DD
    PersonStatus status_;

    // only when status == deceased 
    std::optional<std::string> deathDate_;
    std::optional<std::string> causeOfDeath_;

    // only when status =- inprison
    std::optional<std::string> prisonEntryDate_;
    std::optional<int> prisonSentenceYears_;
    std::optional<std::string> prisonReleaseDate_;

    // only when status == inprison/ in custody, free and deceased persons intentionally omitted here
    std::vector<int> relatedCaseIds_;

public:
    //constuctors
    Person();
    Person(const std::string& firstName,
           const std::string& lastName,
           const std::string& birthDate,
           PersonStatus status = PersonStatus::Free);

    // getters
    const std::string& getFirstName() const;
    const std::string& getLastName() const;
    const std::string& getBirthDate() const;
    PersonStatus getStatus() const;

    // default setters
    void setFirstName(const std::string& firstName);
    void setLastName(const std::string& lastName);
    void setBirthDate(const std::string& birthDate);

    void setStatus(PersonStatus status);

    void setDeathInfo(const std::string& deathDate,
                      const std::string& cause);

    void setPrisonInfo(const std::string& entryDate,
                       int sentenceYears,
                       const std::string& releaseDate);

    void addRelatedCase(int caseId);
    const std::vector<int>& getRelatedCases() const;

    std::string toString() const;
};

} // namespace rmpg
