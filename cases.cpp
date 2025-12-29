#include "cases.hpp"

namespace rmpg {

// --- constructors ---

Case::Case()
    : id_(0),
      type_(CaseType::Other),
      description_("") {}

Case::Case(int id, CaseType type, const std::string& description)
    : id_(0),
      type_(CaseType::Other),
      description_("") {

    setId(id);
    setType(type);
    setDescription(description);
}

// --- getters ---

int Case::getId() const {
    return id_;
}

CaseType Case::getType() const {
    return type_;
}

const std::string& Case::getDescription() const {
    return description_;
}

// ID of cases is pressumed to be a three-digit number, either case, numbers lower than 0 won't be accepted in any sctructure

void Case::setId(int id) {
    if (id <= 0) {
        throw std::invalid_argument("Case ID must be greater than zero.");
    }
    id_ = id;
}

void Case::setType(CaseType type) {
    type_ = type;
}

void Case::setDescription(const std::string& description) {
    if (description.empty()) {
        throw std::invalid_argument("Case description cannot be empty.");
    }
    description_ = description;
}

// --- utilities ---

std::string Case::toString() const {
    std::string typeStr;

    switch (type_) {
        case CaseType::Theft:
            typeStr = "Theft";
            break;
        case CaseType::Burglary:
            typeStr = "Burglary";
            break;
        case CaseType::Assault:
            typeStr = "Assault";
            break;
        case CaseType::Homicide:
            typeStr = "Homicide";
            break;
        case CaseType::DisruptingPeace:
            typeStr = "Disrupting the peace";
            break;
        case CaseType::Fraud:
            typeStr = "Fraud";
            break;
        case CaseType::Other:
        default:
            typeStr = "Other";
            break;
    }

    return "Case ID: " + std::to_string(id_) +
           " | Type: " + typeStr +
           " | Description: " + description_;
}

} // namespace rmpg
