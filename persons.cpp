#include "persons.hpp"

namespace rmpg {

// =====================
// Person
// =====================

Person::Person(std::string firstName, std::string lastName)
    : m_firstName(std::move(firstName)),
      m_lastName(std::move(lastName)) {}

const std::string& Person::getFirstName() const noexcept {
    return m_firstName;
}

const std::string& Person::getLastName() const noexcept {
    return m_lastName;
}

void Person::setFirstName(const std::string& firstName) {
    if (!firstName.empty()) {
        m_firstName = firstName;
    }
}

void Person::setLastName(const std::string& lastName) {
    if (!lastName.empty()) {
        m_lastName = lastName;
    }
}

// =====================
// LivingPerson
// =====================

LivingPerson::LivingPerson(std::string firstName,
                           std::string lastName,
                           std::string dateOfBirth)
    : Person(std::move(firstName), std::move(lastName)),
      m_dateOfBirth(std::move(dateOfBirth)) {}

const std::string& LivingPerson::getDateOfBirth() const noexcept {
    return m_dateOfBirth;
}

bool LivingPerson::setDateOfBirth(const std::string& dateOfBirth) {
    if (dateOfBirth.size() == 10) { // basic YYYY-MM-DD sanity check
        m_dateOfBirth = dateOfBirth;
        return true;
    }
    return false;
}

// =====================
// FreePerson
// =====================

PersonStatus FreePerson::getStatus() const noexcept {
    return PersonStatus::Free;
}

// =====================
// ArrestedPerson
// =====================

ArrestedPerson::ArrestedPerson(std::string firstName,
                               std::string lastName,
                               std::string dateOfBirth,
                               std::vector<std::uint32_t> relatedCaseIds)
    : LivingPerson(std::move(firstName),
                   std::move(lastName),
                   std::move(dateOfBirth)),
      m_relatedCaseIds(std::move(relatedCaseIds)) {}

PersonStatus ArrestedPerson::getStatus() const noexcept {
    return PersonStatus::Arrested;
}

const std::vector<std::uint32_t>&
ArrestedPerson::getRelatedCases() const noexcept {
    return m_relatedCaseIds;
}

void ArrestedPerson::addCase(std::uint32_t caseId) {
    m_relatedCaseIds.push_back(caseId);
}

// =====================
// ImprisonedPerson
// =====================

ImprisonedPerson::ImprisonedPerson(std::string firstName,
                                   std::string lastName,
                                   std::string dateOfBirth,
                                   std::string imprisonmentStartDate,
                                   std::uint32_t sentenceLengthMonths,
                                   std::vector<std::uint32_t> relatedCaseIds)
    : LivingPerson(std::move(firstName),
                   std::move(lastName),
                   std::move(dateOfBirth)),
      m_imprisonmentStartDate(std::move(imprisonmentStartDate)),
      m_sentenceLengthMonths(sentenceLengthMonths),
      m_relatedCaseIds(std::move(relatedCaseIds)) {}

PersonStatus ImprisonedPerson::getStatus() const noexcept {
    return PersonStatus::Imprisoned;
}

const std::string&
ImprisonedPerson::getImprisonmentStartDate() const noexcept {
    return m_imprisonmentStartDate;
}

std::uint32_t
ImprisonedPerson::getSentenceLengthMonths() const noexcept {
    return m_sentenceLengthMonths;
}

const std::vector<std::uint32_t>&
ImprisonedPerson::getRelatedCases() const noexcept {
    return m_relatedCaseIds;
}

// =====================
// DeceasedPerson
// =====================

DeceasedPerson::DeceasedPerson(std::string firstName,
                               std::string lastName,
                               std::string dateOfDeath,
                               std::string causeOfDeath)
    : Person(std::move(firstName), std::move(lastName)),
      m_dateOfDeath(std::move(dateOfDeath)),
      m_causeOfDeath(std::move(causeOfDeath)) {}

PersonStatus DeceasedPerson::getStatus() const noexcept {
    return PersonStatus::Deceased;
}

const std::string&
DeceasedPerson::getDateOfDeath() const noexcept {
    return m_dateOfDeath;
}

const std::string&
DeceasedPerson::getCauseOfDeath() const noexcept {
    return m_causeOfDeath;
}

} // namespace rmpg
