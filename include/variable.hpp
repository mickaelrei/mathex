#pragma once

#include "expression.hpp"

namespace mathex {

class Constant;
class UnaryOperation;
class BinaryOperation;
class OperationNeg;

class Variable : public Expression {
public:
    Variable(const std::string& name);

    virtual float eval(const VariableContext& ctx) const override;
    virtual Expression* clone() const override;
    virtual Expression* differentiate(const std::string& varName) const override;

    // Variable and Constant
    BinaryOperation operator+(const Constant& c) const;
    BinaryOperation operator-(const Constant& c) const;
    BinaryOperation operator*(const Constant& c) const;
    BinaryOperation operator/(const Constant& c) const;
    OperationNeg operator-() const;

    // Variable and Variable
    BinaryOperation operator+(const Variable& v) const;
    BinaryOperation operator-(const Variable& v) const;
    BinaryOperation operator*(const Variable& v) const;
    BinaryOperation operator/(const Variable& v) const;

    // Variable and UnaryOperation
    BinaryOperation operator+(const UnaryOperation& o) const;
    BinaryOperation operator-(const UnaryOperation& o) const;
    BinaryOperation operator*(const UnaryOperation& o) const;
    BinaryOperation operator/(const UnaryOperation& o) const;

    // Variable and BinaryOperation
    BinaryOperation operator+(const BinaryOperation& o) const;
    BinaryOperation operator-(const BinaryOperation& o) const;
    BinaryOperation operator*(const BinaryOperation& o) const;
    BinaryOperation operator/(const BinaryOperation& o) const;

    // Variable and float
    BinaryOperation operator+(float f) const;
    BinaryOperation operator-(float f) const;
    BinaryOperation operator*(float f) const;
    BinaryOperation operator/(float f) const;

protected:
    std::string name;
};

// float and Variable
BinaryOperation operator+(float f, const Variable& v);
BinaryOperation operator-(float f, const Variable& v);
BinaryOperation operator*(float f, const Variable& v);
BinaryOperation operator/(float f, const Variable& v);

} // namespace mathex