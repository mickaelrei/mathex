#include <stdexcept>

#include "variable.hpp"
#include "constant.hpp"
#include "unary_operation.hpp"
#include "binary_operation.hpp"

namespace mathex {

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
BinaryOperation Variable::operator+(const Constant& c) const {
    return BinaryOperation(
        BinaryOperator::ADD,
        new Variable(*this),
        new Constant(c)
    );
}

BinaryOperation Variable::operator-(const Constant& c) const {
    return BinaryOperation(
        BinaryOperator::SUB,
        new Variable(*this),
        new Constant(c)
    );
}

BinaryOperation Variable::operator*(const Constant& c) const {
    return BinaryOperation(
        BinaryOperator::MUL,
        new Variable(*this),
        new Constant(c)
    );
}

BinaryOperation Variable::operator/(const Constant& c) const {
    return BinaryOperation(
        BinaryOperator::DIV,
        new Variable(*this),
        new Constant(c)
    );
}

UnaryOperation Variable::operator-() const {
    return UnaryOperation(UnaryOperator::NEG, new Variable(*this));
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
// Variable and UnaryOperation
BinaryOperation Variable::operator+(const UnaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::ADD,
        new Variable(*this),
        new UnaryOperation(o)
    );
}

BinaryOperation Variable::operator-(const UnaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::SUB,
        new Variable(*this),
        new UnaryOperation(o)
    );
}

BinaryOperation Variable::operator*(const UnaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::MUL,
        new Variable(*this),
        new UnaryOperation(o)
    );
}

BinaryOperation Variable::operator/(const UnaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::DIV,
        new Variable(*this),
        new UnaryOperation(o)
    );
}

// --------------------------
// --------------------------
// Variable and BinaryOperation
BinaryOperation Variable::operator+(const BinaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::ADD,
        new Variable(*this),
        new BinaryOperation(o)
    );
}

BinaryOperation Variable::operator-(const BinaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::SUB,
        new Variable(*this),
        new BinaryOperation(o)
    );
}

BinaryOperation Variable::operator*(const BinaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::MUL,
        new Variable(*this),
        new BinaryOperation(o)
    );
}

BinaryOperation Variable::operator/(const BinaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::DIV,
        new Variable(*this),
        new BinaryOperation(o)
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
BinaryOperation operator+(float f, const Variable& v) { return v + f; }
BinaryOperation operator-(float f, const Variable& v) { return v - f; }
BinaryOperation operator*(float f, const Variable& v) { return v * f; }
BinaryOperation operator/(float f, const Variable& v) { return v / f; }

} // namespace mathex