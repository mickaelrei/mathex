#include <stdexcept>

#include "unary_operation.hpp"
#include "binary_operation.hpp"
#include "constant.hpp"
#include "variable.hpp"
#include "functions.hpp"

namespace mathex {

UnaryOperation::UnaryOperation(Expression* operand) : operand{operand} {}

UnaryOperation::UnaryOperation(const UnaryOperation& o)
  : operand{o.operand ? o.operand->clone() : nullptr} {}

UnaryOperation& UnaryOperation::operator=(const UnaryOperation& o) {
    // Self-assignment
    if (this == &o) {
        return *this;
    }

    // Free existing memory
    delete operand;

    operand = o.operand ? o.operand->clone() : nullptr;
    return *this;
}

UnaryOperation::~UnaryOperation() {
    delete operand;
}

// --------------------------
// --------------------------
// UnaryOperation and Constant
BinaryOperation UnaryOperation::operator+(const Constant& c) const {
    return BinaryOperation(
        BinaryOperator::ADD,
        clone(),
        new Constant(c)
    );
}

BinaryOperation UnaryOperation::operator-(const Constant& c) const {
    return BinaryOperation(
        BinaryOperator::SUB,
        clone(),
        new Constant(c)
    );
}

BinaryOperation UnaryOperation::operator*(const Constant& c) const {
    return BinaryOperation(
        BinaryOperator::MUL,
        clone(),
        new Constant(c)
    );
}

BinaryOperation UnaryOperation::operator/(const Constant& c) const {
    return BinaryOperation(
        BinaryOperator::DIV,
        clone(),
        new Constant(c)
    );
}

OperationNeg UnaryOperation::operator-() const {
    return OperationNeg(clone());
}

// --------------------------
// --------------------------
// UnaryOperation and Variable
BinaryOperation UnaryOperation::operator+(const Variable& v) const {
    return BinaryOperation(
        BinaryOperator::ADD,
        clone(),
        new Variable(v)
    );
}

BinaryOperation UnaryOperation::operator-(const Variable& v) const {
    return BinaryOperation(
        BinaryOperator::SUB,
        clone(),
        new Variable(v)
    );
}

BinaryOperation UnaryOperation::operator*(const Variable& v) const {
    return BinaryOperation(
        BinaryOperator::MUL,
        clone(),
        new Variable(v)
    );
}

BinaryOperation UnaryOperation::operator/(const Variable& v) const {
    return BinaryOperation(
        BinaryOperator::DIV,
        clone(),
        new Variable(v)
    );
}

// --------------------------
// --------------------------
// UnaryOperation and UnaryOperation
BinaryOperation UnaryOperation::operator+(const UnaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::ADD,
        clone(),
        o.clone()
    );
}

BinaryOperation UnaryOperation::operator-(const UnaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::SUB,
        clone(),
        o.clone()
    );
}

BinaryOperation UnaryOperation::operator*(const UnaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::MUL,
        clone(),
        o.clone()
    );
}

BinaryOperation UnaryOperation::operator/(const UnaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::DIV,
        clone(),
        o.clone()
    );
}

// --------------------------
// --------------------------
// UnaryOperation and BinaryOperation
BinaryOperation UnaryOperation::operator+(const BinaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::ADD,
        clone(),
        new BinaryOperation(o)
    );
}

BinaryOperation UnaryOperation::operator-(const BinaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::SUB,
        clone(),
        new BinaryOperation(o)
    );
}

BinaryOperation UnaryOperation::operator*(const BinaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::MUL,
        clone(),
        new BinaryOperation(o)
    );
}

BinaryOperation UnaryOperation::operator/(const BinaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::DIV,
        clone(),
        new BinaryOperation(o)
    );
}

// --------------------------
// --------------------------
// UnaryOperation and float
BinaryOperation UnaryOperation::operator+(float f) const {
    return BinaryOperation(
        BinaryOperator::ADD,
        clone(),
        new Constant(f)
    );
}

BinaryOperation UnaryOperation::operator-(float f) const {
    return BinaryOperation(
        BinaryOperator::SUB,
        clone(),
        new Constant(f)
    );
}

BinaryOperation UnaryOperation::operator*(float f) const {
    return BinaryOperation(
        BinaryOperator::MUL,
        clone(),
        new Constant(f)
    );
}

BinaryOperation UnaryOperation::operator/(float f) const {
    return BinaryOperation(
        BinaryOperator::DIV,
        clone(),
        new Constant(f)
    );
}

// --------------------------
// --------------------------
// float and UnaryOperation
BinaryOperation operator+(float f, const UnaryOperation& o) { return o + f; }
BinaryOperation operator-(float f, const UnaryOperation& o) { return o - f; }
BinaryOperation operator*(float f, const UnaryOperation& o) { return o * f; }
BinaryOperation operator/(float f, const UnaryOperation& o) { return o / f; }

} // namespace mathex