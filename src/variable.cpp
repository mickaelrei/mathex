#include <stdexcept>

#include "variable.hpp"
#include "constant.hpp"
#include "binary_operation.hpp"

Variable::Variable(const std::string& name) : name{name} {}

float Variable::eval(const VariableContext& ctx) const {
    // TODO: Get from param
    auto it = ctx.find(name);
    if (it == ctx.end()) {
        throw std::runtime_error{"[Variable::eval] Variable name not found in context"};
    }

    return it->second;
}

Expression* Variable::clone() const {
    return new Variable(*this);
}

// --------------------------
// --------------------------
// Variable and Constant
BinaryOperation Variable::operator+(const Constant& v) const {
    return BinaryOperation(
        BinaryOperator::ADD,
        new Variable(*this),
        new Constant(v)
    );
}

BinaryOperation Variable::operator-(const Constant& v) const {
    return BinaryOperation(
        BinaryOperator::SUB,
        new Variable(*this),
        new Constant(v)
    );
}

BinaryOperation Variable::operator*(const Constant& v) const {
    return BinaryOperation(
        BinaryOperator::MUL,
        new Variable(*this),
        new Constant(v)
    );
}

BinaryOperation Variable::operator/(const Constant& v) const {
    return BinaryOperation(
        BinaryOperator::DIV,
        new Variable(*this),
        new Constant(v)
    );
}

BinaryOperation Variable::operator-() const {
    return BinaryOperation(
        BinaryOperator::DIV,
        new Constant(-1.0f),
        new Variable(*this)
    );
}

// --------------------------
// --------------------------
// Variable and Variable
BinaryOperation Variable::operator+(const Variable& v) const {
    return BinaryOperation(
        BinaryOperator::ADD,
        new Variable(*this),
        new Variable(v)
    );
}

BinaryOperation Variable::operator-(const Variable& v) const {
    return BinaryOperation(
        BinaryOperator::SUB,
        new Variable(*this),
        new Variable(v)
    );
}

BinaryOperation Variable::operator*(const Variable& v) const {
    return BinaryOperation(
        BinaryOperator::MUL,
        new Variable(*this),
        new Variable(v)
    );
}

BinaryOperation Variable::operator/(const Variable& v) const {
    return BinaryOperation(
        BinaryOperator::DIV,
        new Variable(*this),
        new Variable(v)
    );
}

// --------------------------
// --------------------------
// Variable and BinaryOperation
BinaryOperation Variable::operator+(const BinaryOperation& v) const {
    return BinaryOperation(
        BinaryOperator::ADD,
        new Variable(*this),
        new BinaryOperation(v)
    );
}

BinaryOperation Variable::operator-(const BinaryOperation& v) const {
    return BinaryOperation(
        BinaryOperator::SUB,
        new Variable(*this),
        new BinaryOperation(v)
    );
}

BinaryOperation Variable::operator*(const BinaryOperation& v) const {
    return BinaryOperation(
        BinaryOperator::MUL,
        new Variable(*this),
        new BinaryOperation(v)
    );
}

BinaryOperation Variable::operator/(const BinaryOperation& v) const {
    return BinaryOperation(
        BinaryOperator::DIV,
        new Variable(*this),
        new BinaryOperation(v)
    );
}

// --------------------------
// --------------------------
// Variable and float
BinaryOperation Variable::operator+(float f) const {
    return BinaryOperation(
        BinaryOperator::ADD,
        new Variable(*this),
        new Constant(f)
    );
}

BinaryOperation Variable::operator-(float f) const {
    return BinaryOperation(
        BinaryOperator::SUB,
        new Variable(*this),
        new Constant(f)
    );
}

BinaryOperation Variable::operator*(float f) const {
    return BinaryOperation(
        BinaryOperator::MUL,
        new Variable(*this),
        new Constant(f)
    );
}

BinaryOperation Variable::operator/(float f) const {
    return BinaryOperation(
        BinaryOperator::DIV,
        new Variable(*this),
        new Constant(f)
    );
}

// --------------------------
// --------------------------
// float and Variable
BinaryOperation operator+(float f, const Variable& c) { return c + f; }
BinaryOperation operator-(float f, const Variable& c) { return c - f; }
BinaryOperation operator*(float f, const Variable& c) { return c * f; }
BinaryOperation operator/(float f, const Variable& c) { return c / f; }