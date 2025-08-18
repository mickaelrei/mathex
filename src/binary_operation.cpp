#include <stdexcept>
#include <cmath>

#include "binary_operation.hpp"
#include "variable.hpp"
#include "constant.hpp"
#include "unary_operation.hpp"

namespace mathex {

std::string to_string(BinaryOperator op) {
    switch (op) {
    case BinaryOperator::ADD:
        return "ADD";
    case BinaryOperator::SUB:
        return "SUB";
    case BinaryOperator::MUL:
        return "MUL";
    case BinaryOperator::DIV:
        return "DIV";
    case BinaryOperator::POW:
        return "POW";
    }

    return "UNKNOWN";
}

std::ostream& operator<<(std::ostream& os, BinaryOperator op) {
    os << to_string(op);
    return os;
}

BinaryOperation::BinaryOperation(
    BinaryOperator operand,
    Expression* left,
    Expression* right
) : op{operand},
    left{left},
    right{right} {}

BinaryOperation::BinaryOperation(const BinaryOperation& o)
  : op{o.op},
    left{o.left ? o.left->clone() : nullptr},
    right{o.right ? o.right->clone() : nullptr} {
}

BinaryOperation& BinaryOperation::operator=(const BinaryOperation& o) {
    // Self-assignment
    if (this == &o) {
        return *this;
    }

    // Free existing memory
    delete left;
    delete right;

    op = o.op;
    left = o.left ? o.left->clone() : nullptr;
    right = o.right ? o.right->clone() : nullptr;
    return *this;
}

BinaryOperation::~BinaryOperation() {
    delete left;
    delete right;
}

float BinaryOperation::eval(const VariableContext& ctx) const {
    auto l = left->eval(ctx);
    auto r = right->eval(ctx);

    switch (op) {
    case BinaryOperator::ADD:
        return l + r;
    case BinaryOperator::SUB:
        return l - r;
    case BinaryOperator::MUL:
        return l * r;
    case BinaryOperator::DIV:
        return l / r;
    case BinaryOperator::POW:
        return std::pow(l, r);
    }

    // Should never reach this
    throw std::runtime_error{"[BinaryOperator::eval] Unknown operation"};
}

Expression* BinaryOperation::clone() const {
    return new BinaryOperation(*this);
}

// --------------------------
// --------------------------
// BinaryOperation and Constant
BinaryOperation BinaryOperation::operator+(const Constant& c) const {
    return BinaryOperation(
        BinaryOperator::ADD,
        new BinaryOperation(*this),
        new Constant(c)
    );
}

BinaryOperation BinaryOperation::operator-(const Constant& c) const {
    return BinaryOperation(
        BinaryOperator::SUB,
        new BinaryOperation(*this),
        new Constant(c)
    );
}

BinaryOperation BinaryOperation::operator*(const Constant& c) const {
    return BinaryOperation(
        BinaryOperator::MUL,
        new BinaryOperation(*this),
        new Constant(c)
    );
}

BinaryOperation BinaryOperation::operator/(const Constant& c) const {
    return BinaryOperation(
        BinaryOperator::DIV,
        new BinaryOperation(*this),
        new Constant(c)
    );
}

UnaryOperation BinaryOperation::operator-() const {
    return UnaryOperation(UnaryOperator::NEG, new BinaryOperation(*this));
}

// --------------------------
// --------------------------
// BinaryOperation and Variable
BinaryOperation BinaryOperation::operator+(const Variable& v) const {
    return BinaryOperation(
        BinaryOperator::ADD,
        new BinaryOperation(*this),
        new Variable(v)
    );
}

BinaryOperation BinaryOperation::operator-(const Variable& v) const {
    return BinaryOperation(
        BinaryOperator::SUB,
        new BinaryOperation(*this),
        new Variable(v)
    );
}

BinaryOperation BinaryOperation::operator*(const Variable& v) const {
    return BinaryOperation(
        BinaryOperator::MUL,
        new BinaryOperation(*this),
        new Variable(v)
    );
}

BinaryOperation BinaryOperation::operator/(const Variable& v) const {
    return BinaryOperation(
        BinaryOperator::DIV,
        new BinaryOperation(*this),
        new Variable(v)
    );
}

// --------------------------
// --------------------------
// BinaryOperation and UnaryOperation
BinaryOperation BinaryOperation::operator+(const UnaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::ADD,
        new BinaryOperation(*this),
        new UnaryOperation(o)
    );
}

BinaryOperation BinaryOperation::operator-(const UnaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::SUB,
        new BinaryOperation(*this),
        new UnaryOperation(o)
    );
}

BinaryOperation BinaryOperation::operator*(const UnaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::MUL,
        new BinaryOperation(*this),
        new UnaryOperation(o)
    );
}

BinaryOperation BinaryOperation::operator/(const UnaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::DIV,
        new BinaryOperation(*this),
        new UnaryOperation(o)
    );
}

// --------------------------
// --------------------------
// BinaryOperation and BinaryOperation
BinaryOperation BinaryOperation::operator+(const BinaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::ADD,
        new BinaryOperation(*this),
        new BinaryOperation(o)
    );
}

BinaryOperation BinaryOperation::operator-(const BinaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::SUB,
        new BinaryOperation(*this),
        new BinaryOperation(o)
    );
}

BinaryOperation BinaryOperation::operator*(const BinaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::MUL,
        new BinaryOperation(*this),
        new BinaryOperation(o)
    );
}

BinaryOperation BinaryOperation::operator/(const BinaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::DIV,
        new BinaryOperation(*this),
        new BinaryOperation(o)
    );
}

// --------------------------
// --------------------------
// BinaryOperation and float
BinaryOperation BinaryOperation::operator+(float f) const {
    return BinaryOperation(
        BinaryOperator::ADD,
        new BinaryOperation(*this),
        new Constant(f)
    );
}
BinaryOperation BinaryOperation::operator-(float f) const {
    return BinaryOperation(
        BinaryOperator::SUB,
        new BinaryOperation(*this),
        new Constant(f)
    );
}
BinaryOperation BinaryOperation::operator*(float f) const {
    return BinaryOperation(
        BinaryOperator::MUL,
        new BinaryOperation(*this),
        new Constant(f)
    );
}
BinaryOperation BinaryOperation::operator/(float f) const {
    return BinaryOperation(
        BinaryOperator::DIV,
        new BinaryOperation(*this),
        new Constant(f)
    );
}

// --------------------------
// --------------------------
// float and BinaryOperation
BinaryOperation operator+(float f, const BinaryOperation& c) { return c + f; }
BinaryOperation operator-(float f, const BinaryOperation& c) { return c - f; }
BinaryOperation operator*(float f, const BinaryOperation& c) { return c * f; }
BinaryOperation operator/(float f, const BinaryOperation& c) { return c / f; }

} // namespace mathex
