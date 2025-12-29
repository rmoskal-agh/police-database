#include "database.hpp"

namespace rmpg {

// =====================
// PERSONS
// =====================

bool Database::addPerson(std::shared_ptr<Person> person) {
    if (!person) {
        return false;
    }
    m_persons.push_back(std::move(person));
    return true;
}

std::shared_ptr<Person>
Database::getPerson(std::size_t index) const {
    if (index >= m_persons.size()) {
        return nullptr;
    }
    return m_persons[index];
}

bool Database::removePerson(std::size_t index) {
    if (index >= m_persons.size()) {
        return false;
    }
    m_persons.erase(m_persons.begin() + index);
    return true;
}

std::size_t Database::personCount() const noexcept {
    return m_persons.size();
}

// =====================
// CASES
// =====================

bool Database::addCase(const Case& c) {
    for (const auto& existing : m_cases) {
        if (existing.getId() == c.getId()) {
            return false;
        }
    }
    m_cases.push_back(c);
    return true;
}

std::optional<Case>
Database::getCaseById(std::uint32_t id) const {
    for (const auto& c : m_cases) {
        if (c.getId() == id) {
            return c;
        }
    }
    return std::nullopt;
}

bool Database::removeCaseById(std::uint32_t id) {
    for (auto it = m_cases.begin(); it != m_cases.end(); ++it) {
        if (it->getId() == id) {
            m_cases.erase(it);
            return true;
        }
    }
    return false;
}

std::size_t Database::caseCount() const noexcept {
    return m_cases.size();
}

// =====================
// CLEAR
// =====================

void Database::clear() {
    m_persons.clear();
    m_cases.clear();
}

} // namespace rmpg
