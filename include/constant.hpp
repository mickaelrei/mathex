#pragma once

#include "expression.hpp"

namespace mathex {

class Variable;
class UnaryOperation;
class BinaryOperation;

class Constant : public Expression {
public:
    Constant(float c);

    virtual float eval(const VariableContext& ctx) const override;
    Expression* clone() const override;

    // Constant and Constant
    Constant operator+(const Constant& c) const;
    Constant operator-(const Constant& c) const;
    Constant operator*(const Constant& c) const;
    Constant operator/(const Constant& c) const;
    Constant operator-() const;

    // Constant and Variable
    BinaryOperation operator+(const Variable& v) const;
    BinaryOperation operator-(const Variable& v) const;
    BinaryOperation operator*(const Variable& v) const;
    BinaryOperation operator/(const Variable& v) const;

    // Constant and UnaryOperation
    BinaryOperation operator+(const UnaryOperation& o) const;
    BinaryOperation operator-(const UnaryOperation& o) const;
    BinaryOperation operator*(const UnaryOperation& o) const;
    BinaryOperation operator/(const UnaryOperation& o) const;

    // Constant and BinaryOperation
    BinaryOperation operator+(const BinaryOperation& o) const;
    BinaryOperation operator-(const BinaryOperation& o) const;
    BinaryOperation operator*(const BinaryOperation& o) const;
    BinaryOperation operator/(const BinaryOperation& o) const;

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