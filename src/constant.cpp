#include "constant.hpp"
#include "variable.hpp"
#include "binary_operation.hpp"

namespace mathex {

Constant::Constant(float c) : c{c} {}

float Constant::eval(const VariableContext& ctx) const {
    (void)ctx;
    return c;
}

Expression* Constant::clone() const {
    return new Constant(*this);
}

// --------------------------
// --------------------------
// Constant and Constant
Constant Constant::operator+(const Constant& v) const {
    return Constant(c + v.c);
}

Constant Constant::operator-(const Constant& v) const {
    return Constant(c - v.c);
}

Constant Constant::operator*(const Constant& v) const {
    return Constant(c * v.c);
}

Constant Constant::operator/(const Constant& v) const {
    return Constant(c / v.c);
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
// Constant and BinaryOperation
BinaryOperation Constant::operator+(const BinaryOperation& v) const {
    return BinaryOperation(
        BinaryOperator::ADD,
        new Constant(*this),
        new BinaryOperation(v)
    );
}

BinaryOperation Constant::operator-(const BinaryOperation& v) const {
    return BinaryOperation(
        BinaryOperator::SUB,
        new Constant(*this),
        new BinaryOperation(v)
    );
}

BinaryOperation Constant::operator*(const BinaryOperation& v) const {
    return BinaryOperation(
        BinaryOperator::MUL,
        new Constant(*this),
        new BinaryOperation(v)
    );
}

BinaryOperation Constant::operator/(const BinaryOperation& v) const {
    return BinaryOperation(
        BinaryOperator::DIV,
        new Constant(*this),
        new BinaryOperation(v)
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