#include <cmath>

#include "binary_operation.hpp"
#include "variable.hpp"
#include "constant.hpp"

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

BinaryOperation::BinaryOperation(const BinaryOperation& b)
  : op{b.op},
    left{b.left ? b.left->clone() : nullptr},
    right{b.right ? b.right->clone() : nullptr} {
}

BinaryOperation& BinaryOperation::operator=(const BinaryOperation& b) {
    // Self-assignment
    if (this == &b) {
        return *this;
    }

    // Free existing memory
    delete left;
    delete right;

    op = b.op;
    left = b.left ? b.left->clone() : nullptr;
    right = b.right ? b.right->clone() : nullptr;
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
    return 0.0f;
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

BinaryOperation BinaryOperation::operator-() const {
    return BinaryOperation(
        BinaryOperator::MUL,
        new Constant(-1.0f),
        new BinaryOperation(*this)
    );
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