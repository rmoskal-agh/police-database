#pragma once

#include <vector>
#include <memory>
#include <optional>

#include "persons.hpp"
#include "cases.hpp"

namespace rmpg {

class Database {
public:
    Database() = default;

    // ===== PERSONS =====
    bool addPerson(std::shared_ptr<Person> person);
    std::shared_ptr<Person> getPerson(std::size_t index) const;
    bool removePerson(std::size_t index); // not to confuse removePerson with type of case - homicide
    std::size_t personCount() const noexcept;

    // ===== CASES =====
    bool addCase(const Case& c);
    std::optional<Case> getCaseById(std::uint32_t id) const;
    bool removeCaseById(std::uint32_t id);
    std::size_t caseCount() const noexcept;

    // ===== CLEAR =====
// brief this function clears
    void clear();

private:
    std::vector<std::shared_ptr<Person>> m_persons;
    std::vector<Case> m_cases;
};

} // namespace rmpg
