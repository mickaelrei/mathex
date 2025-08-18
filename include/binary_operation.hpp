#pragma once

#include <memory>

#include "expression.hpp"

class Constant;
class Variable;

enum class BinaryOperator {
    ADD,
    SUB,
    MUL,
    DIV,
    POW
};

std::string to_string(BinaryOperator op);

std::ostream& operator<<(const std::ostream& os, BinaryOperator op);

class BinaryOperation : public Expression {
public:
    BinaryOperation(BinaryOperator operand, Expression* left, Expression* right);
    BinaryOperation(const BinaryOperation& b);
    BinaryOperation& operator=(const BinaryOperation& b);

    virtual ~BinaryOperation();

    virtual float eval(const VariableContext& ctx) const override;
    Expression* clone() const override;

    // BinaryOperation and Constant
    BinaryOperation operator+(const Constant& v) const;
    BinaryOperation operator-(const Constant& v) const;
    BinaryOperation operator*(const Constant& v) const;
    BinaryOperation operator/(const Constant& v) const;
    BinaryOperation operator-() const;

    // BinaryOperation and Variable
    BinaryOperation operator+(const Variable& v) const;
    BinaryOperation operator-(const Variable& v) const;
    BinaryOperation operator*(const Variable& v) const;
    BinaryOperation operator/(const Variable& v) const;

    // BinaryOperation and BinaryOperation
    BinaryOperation operator+(const BinaryOperation& v) const;
    BinaryOperation operator-(const BinaryOperation& v) const;
    BinaryOperation operator*(const BinaryOperation& v) const;
    BinaryOperation operator/(const BinaryOperation& v) const;

    // BinaryOperation and float
    BinaryOperation operator+(float f) const;
    BinaryOperation operator-(float f) const;
    BinaryOperation operator*(float f) const;
    BinaryOperation operator/(float f) const;

// private:
    BinaryOperator op;
    Expression* left;
    Expression* right;
};

// float and BinaryOperation
BinaryOperation operator+(float f, const BinaryOperation& c);
BinaryOperation operator-(float f, const BinaryOperation& c);
BinaryOperation operator*(float f, const BinaryOperation& c);
BinaryOperation operator/(float f, const BinaryOperation& c);