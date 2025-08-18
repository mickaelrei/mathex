#pragma once

#include "expression.hpp"

namespace mathex {

class Variable;
class BinaryOperation;

class Constant : public Expression {
public:
    Constant(float c);

    virtual float eval(const VariableContext& ctx) const override;
    Expression* clone() const override;

    // Constant and Constant
    Constant operator+(const Constant& v) const;
    Constant operator-(const Constant& v) const;
    Constant operator*(const Constant& v) const;
    Constant operator/(const Constant& v) const;
    Constant operator-() const;

    // Constant and Variable
    BinaryOperation operator+(const Variable& v) const;
    BinaryOperation operator-(const Variable& v) const;
    BinaryOperation operator*(const Variable& v) const;
    BinaryOperation operator/(const Variable& v) const;

    // Constant and BinaryOperation
    BinaryOperation operator+(const BinaryOperation& v) const;
    BinaryOperation operator-(const BinaryOperation& v) const;
    BinaryOperation operator*(const BinaryOperation& v) const;
    BinaryOperation operator/(const BinaryOperation& v) const;

    // Constant and float
    Constant operator+(float f) const;
    Constant operator-(float f) const;
    Constant operator*(float f) const;
    Constant operator/(float f) const;

private:
    float c;
};

// float and Constant
Constant operator+(float f, const Constant& c);
Constant operator-(float f, const Constant& c);
Constant operator*(float f, const Constant& c);
Constant operator/(float f, const Constant& c);

} // namespace mathex