#pragma once

#include <string>
#include <unordered_map>

namespace mathex {

using VariableContext = std::unordered_map<std::string, float>;

class Expression {
public:
    virtual ~Expression() = default;

    virtual float eval(const VariableContext& ctx) const = 0;
    virtual Expression* clone() const = 0;
};

} // namespace mathex