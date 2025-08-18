#pragma once

#include <string>
#include <unordered_map>

namespace mathex {

/// @brief Type used to pass values for each variable when evaluating an expression
using VariableContext = std::unordered_map<std::string, float>;

/// @brief Interface for a math expression
class Expression {
public:
    /// @brief Virtual destructor
    virtual ~Expression() = default;

    /// @brief Evaluates this expression with the given variable context
    /// @param ctx Will be used as variable value lookup
    virtual float eval(const VariableContext& ctx) const = 0;

    /// @brief Create a clone heap pointer of this expression
    virtual Expression* clone() const = 0;

    /// @brief Computes and returns the derivative of this expression
    /// @param varName The name of the variable to differentiate with respect to
    virtual Expression* differentiate(const std::string& varName) const = 0;
};

} // namespace mathex