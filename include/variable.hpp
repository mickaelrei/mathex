#pragma once

#include "expression.hpp"

class Constant;
class BinaryOperation;

class Variable : public Expression {
public:
    Variable(const std::string& name);

    virtual float eval(const VariableContext& ctx) const override;
    Expression* clone() const override { return new Variable(*this); }
    // Variable and Constant
    BinaryOperation operator+(const Constant& v) const;
    BinaryOperation operator-(const Constant& v) const;
    BinaryOperation operator*(const Constant& v) const;
    BinaryOperation operator/(const Constant& v) const;

    // Variable and Variable
    BinaryOperation operator+(const Variable& v) const;
    BinaryOperation operator-(const Variable& v) const;
    BinaryOperation operator*(const Variable& v) const;
    BinaryOperation operator/(const Variable& v) const;

    // Variable and BinaryOperation
    BinaryOperation operator+(const BinaryOperation& v) const;
    BinaryOperation operator-(const BinaryOperation& v) const;
    BinaryOperation operator*(const BinaryOperation& v) const;
    BinaryOperation operator/(const BinaryOperation& v) const;

    // Variable and float
    BinaryOperation operator+(float f) const;
    BinaryOperation operator-(float f) const;
    BinaryOperation operator*(float f) const;
    BinaryOperation operator/(float f) const;

private:
    std::string name;
};

// float and Variable
BinaryOperation operator+(float f, const Variable& c);
BinaryOperation operator-(float f, const Variable& c);
BinaryOperation operator*(float f, const Variable& c);
BinaryOperation operator/(float f, const Variable& c);