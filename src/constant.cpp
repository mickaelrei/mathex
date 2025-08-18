#include "constant.hpp"
#include "variable.hpp"
#include "binary_operation.hpp"
#include "unary_operation.hpp"

namespace mathex {

Constant::Constant(float c) : c{c} {}

float Constant::eval(const VariableContext& ctx) const {
    (void)ctx;
    return c;
}

Expression* Constant::clone() const {
    return new Constant(*this);
}

Expression* Constant::differentiate(const std::string& varName) const {
    (void)varName;

    // Derivative of a constant is always zero
    return new Constant(0.0f);
}

// --------------------------
// --------------------------
// Constant and Constant
Constant Constant::operator+(const Constant& _c) const {
    return Constant(c + _c.c);
}

Constant Constant::operator-(const Constant& _c) const {
    return Constant(c - _c.c);
}

Constant Constant::operator*(const Constant& _c) const {
    return Constant(c * _c.c);
}

Constant Constant::operator/(const Constant& _c) const {
    return Constant(c / _c.c);
}

Constant Constant::operator-() const {
    return Constant(-c);
}

// --------------------------
// --------------------------
// Constant and Variable
BinaryOperation Constant::operator+(const Variable& v) const {
    return BinaryOperation(
        BinaryOperator::ADD,
        new Constant(*this),
        new Variable(v)
    );
}

BinaryOperation Constant::operator-(const Variable& v) const {
    return BinaryOperation(
        BinaryOperator::SUB,
        new Constant(*this),
        new Variable(v)
    );
}

BinaryOperation Constant::operator*(const Variable& v) const {
    return BinaryOperation(
        BinaryOperator::MUL,
        new Constant(*this),
        new Variable(v)
    );
}

BinaryOperation Constant::operator/(const Variable& v) const {
    return BinaryOperation(
        BinaryOperator::DIV,
        new Constant(*this),
        new Variable(v)
    );
}

// --------------------------
// --------------------------
// Constant and UnaryOperation
BinaryOperation Constant::operator+(const UnaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::ADD,
        new Constant(*this),
        new UnaryOperation(o)
    );
}

BinaryOperation Constant::operator-(const UnaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::SUB,
        new Constant(*this),
        new UnaryOperation(o)
    );
}

BinaryOperation Constant::operator*(const UnaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::MUL,
        new Constant(*this),
        new UnaryOperation(o)
    );
}

BinaryOperation Constant::operator/(const UnaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::DIV,
        new Constant(*this),
        new UnaryOperation(o)
    );
}

// --------------------------
// --------------------------
// Constant and BinaryOperation
BinaryOperation Constant::operator+(const BinaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::ADD,
        new Constant(*this),
        new BinaryOperation(o)
    );
}

BinaryOperation Constant::operator-(const BinaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::SUB,
        new Constant(*this),
        new BinaryOperation(o)
    );
}

BinaryOperation Constant::operator*(const BinaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::MUL,
        new Constant(*this),
        new BinaryOperation(o)
    );
}

BinaryOperation Constant::operator/(const BinaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::DIV,
        new Constant(*this),
        new BinaryOperation(o)
    );
}

// --------------------------
// --------------------------
// Constant and float
Constant Constant::operator+(float f) const {
    return Constant(c + f);
}

Constant Constant::operator-(float f) const {
    return Constant(c - f);
}

Constant Constant::operator*(float f) const {
    return Constant(c * f);
}

Constant Constant::operator/(float f) const {
    return Constant(c / f);
}

// --------------------------
// --------------------------
// float and Constant
Constant operator+(float f, const Constant& c) { return c + f; }
Constant operator-(float f, const Constant& c) { return c - f; }
Constant operator*(float f, const Constant& c) { return c * f; }
Constant operator/(float f, const Constant& c) { return c / f; }

} // namespace mathex