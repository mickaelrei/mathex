#pragma once

#include <cmath>
#include "expression.hpp"

namespace mathex {

class Constant;
class Variable;
class BinaryOperation;

enum class UnaryOperator {
    NEG,
    SIN,
    COS,
    SEC,
    CSC,
    TAN,
    COT,
    LN,
    LOG10,
    EXP,
    SQRT,
    ABS
};

class UnaryOperation : public Expression {
public:
    UnaryOperation(UnaryOperator op, Expression* operand);
    UnaryOperation(const UnaryOperation& other);
    UnaryOperation& operator=(const UnaryOperation& other);

    virtual ~UnaryOperation();

    virtual float eval(const VariableContext& ctx) const override;
    virtual Expression* clone() const override;
    virtual Expression* differentiate(const std::string& varName) const override;

    // UnaryOperation and Constant
    BinaryOperation operator+(const Constant& c) const;
    BinaryOperation operator-(const Constant& c) const;
    BinaryOperation operator*(const Constant& c) const;
    BinaryOperation operator/(const Constant& c) const;
    UnaryOperation operator-() const;

    // UnaryOperation and Variable
    BinaryOperation operator+(const Variable& v) const;
    BinaryOperation operator-(const Variable& v) const;
    BinaryOperation operator*(const Variable& v) const;
    BinaryOperation operator/(const Variable& v) const;

    // UnaryOperation and UnaryOperation
    BinaryOperation operator+(const UnaryOperation& o) const;
    BinaryOperation operator-(const UnaryOperation& o) const;
    BinaryOperation operator*(const UnaryOperation& o) const;
    BinaryOperation operator/(const UnaryOperation& o) const;

    // UnaryOperation and BinaryOperation
    BinaryOperation operator+(const BinaryOperation& o) const;
    BinaryOperation operator-(const BinaryOperation& o) const;
    BinaryOperation operator*(const BinaryOperation& o) const;
    BinaryOperation operator/(const BinaryOperation& o) const;

    // UnaryOperation and float
    BinaryOperation operator+(float f) const;
    BinaryOperation operator-(float f) const;
    BinaryOperation operator*(float f) const;
    BinaryOperation operator/(float f) const;

protected:
    UnaryOperator op;
    Expression* operand;
};

// float and UnaryOperation
BinaryOperation operator+(float f, const UnaryOperation& o);
BinaryOperation operator-(float f, const UnaryOperation& o);
BinaryOperation operator*(float f, const UnaryOperation& o);
BinaryOperation operator/(float f, const UnaryOperation& o);

} // namespace mathex
