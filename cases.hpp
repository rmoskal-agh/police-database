#pragma once

#include <string>
#include <stdexcept>

namespace rmpg {

/**
 * @brief Enumeration representing basic case types.
 */
enum class CaseType {
    Theft,
    Burglary,
    Assault,
    Homicide, 
    DisruptingPeace,
    Fraud,
    Other
};

/**
 * @brief Represents a single police case.
 *
 * This class is a core data structure.
 * 
 * It contains no input/output logic.
 */
class Case {
private:
    int id_; 
    CaseType type_;
    std::string description_;

public:
    // --- constructors ---

    /**
     * @brief Default constructor.
     */
    Case();

    /**
     * @brief Parameterized constructor.
     *
     * @param id Unique case identifier
     * @param type Type of the case
     * @param description Human-readable description, pressumably not longer than 120 characters.
     */
    Case(int id, CaseType type, const std::string& description);

    // --- getters ---

    int getId() const;
    CaseType getType() const;
    const std::string& getDescription() const;

    // --- setters ---

    void setId(int id);
    void setType(CaseType type);
    void setDescription(const std::string& description);

    // --- utilities ---

    /**
     * @brief Converts case data into a readable string.
     * Intended for use by the terminal UI layer.
     */
    std::string toString() const;
};

} // namespace rmpg
