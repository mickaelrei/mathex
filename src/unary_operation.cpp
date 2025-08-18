#include <stdexcept>

#include "unary_operation.hpp"
#include "binary_operation.hpp"
#include "constant.hpp"
#include "variable.hpp"

namespace mathex {

UnaryOperation::UnaryOperation(UnaryOperator op, Expression* operand)
  : op{op},
    operand{operand} {}

UnaryOperation::UnaryOperation(const UnaryOperation& o)
  : op{o.op},
    operand{o.operand ? o.operand->clone() : nullptr} {}

UnaryOperation& UnaryOperation::operator=(const UnaryOperation& o) {
    // Self-assignment
    if (this == &o) {
        return *this;
    }

    // Free existing memory
    delete operand;

    op = o.op;
    operand = o.operand ? o.operand->clone() : nullptr;
    return *this;
}

UnaryOperation::~UnaryOperation() {
    delete operand;
}

float UnaryOperation::eval(const VariableContext& ctx) const {
    auto v = operand->eval(ctx);

    switch (op) {
    case UnaryOperator::NEG:
        return -v;
    case UnaryOperator::SIN:
        return std::sin(v);
    case UnaryOperator::COS:
        return std::cos(v);
    case UnaryOperator::TAN:
        return std::tan(v);
    case UnaryOperator::LN:
        return std::log(v);
    case UnaryOperator::LOG10:
        return std::log10(v);
    case UnaryOperator::EXP:
        return std::exp(v);
    case UnaryOperator::SQRT:
        return std::sqrt(v);
    case UnaryOperator::ABS:
        return std::abs(v);
    }

    // Should never reach this
    throw std::runtime_error{"[UnaryOperator::eval] Unknown operation"};
}

Expression* UnaryOperation::clone() const {
    return new UnaryOperation(*this);
}

// --------------------------
// --------------------------
// UnaryOperation and Constant
BinaryOperation UnaryOperation::operator+(const Constant& c) const {
    return BinaryOperation(
        BinaryOperator::ADD,
        new UnaryOperation(*this),
        new Constant(c)
    );
}

BinaryOperation UnaryOperation::operator-(const Constant& c) const {
    return BinaryOperation(
        BinaryOperator::SUB,
        new UnaryOperation(*this),
        new Constant(c)
    );
}

BinaryOperation UnaryOperation::operator*(const Constant& c) const {
    return BinaryOperation(
        BinaryOperator::MUL,
        new UnaryOperation(*this),
        new Constant(c)
    );
}

BinaryOperation UnaryOperation::operator/(const Constant& c) const {
    return BinaryOperation(
        BinaryOperator::DIV,
        new UnaryOperation(*this),
        new Constant(c)
    );
}

UnaryOperation UnaryOperation::operator-() const {
    return UnaryOperation(UnaryOperator::NEG, new UnaryOperation(*this));
}

// --------------------------
// --------------------------
// UnaryOperation and Variable
BinaryOperation UnaryOperation::operator+(const Variable& v) const {
    return BinaryOperation(
        BinaryOperator::ADD,
        new UnaryOperation(*this),
        new Variable(v)
    );
}

BinaryOperation UnaryOperation::operator-(const Variable& v) const {
    return BinaryOperation(
        BinaryOperator::SUB,
        new UnaryOperation(*this),
        new Variable(v)
    );
}

BinaryOperation UnaryOperation::operator*(const Variable& v) const {
    return BinaryOperation(
        BinaryOperator::MUL,
        new UnaryOperation(*this),
        new Variable(v)
    );
}

BinaryOperation UnaryOperation::operator/(const Variable& v) const {
    return BinaryOperation(
        BinaryOperator::DIV,
        new UnaryOperation(*this),
        new Variable(v)
    );
}

// --------------------------
// --------------------------
// UnaryOperation and UnaryOperation
BinaryOperation UnaryOperation::operator+(const UnaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::ADD,
        new UnaryOperation(*this),
        new UnaryOperation(o)
    );
}

BinaryOperation UnaryOperation::operator-(const UnaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::SUB,
        new UnaryOperation(*this),
        new UnaryOperation(o)
    );
}

BinaryOperation UnaryOperation::operator*(const UnaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::MUL,
        new UnaryOperation(*this),
        new UnaryOperation(o)
    );
}

BinaryOperation UnaryOperation::operator/(const UnaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::DIV,
        new UnaryOperation(*this),
        new UnaryOperation(o)
    );
}

// --------------------------
// --------------------------
// UnaryOperation and BinaryOperation
BinaryOperation UnaryOperation::operator+(const BinaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::ADD,
        new UnaryOperation(*this),
        new BinaryOperation(o)
    );
}

BinaryOperation UnaryOperation::operator-(const BinaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::SUB,
        new UnaryOperation(*this),
        new BinaryOperation(o)
    );
}

BinaryOperation UnaryOperation::operator*(const BinaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::MUL,
        new UnaryOperation(*this),
        new BinaryOperation(o)
    );
}

BinaryOperation UnaryOperation::operator/(const BinaryOperation& o) const {
    return BinaryOperation(
        BinaryOperator::DIV,
        new UnaryOperation(*this),
        new BinaryOperation(o)
    );
}

// --------------------------
// --------------------------
// UnaryOperation and float
BinaryOperation UnaryOperation::operator+(float f) const {
    return BinaryOperation(
        BinaryOperator::ADD,
        new UnaryOperation(*this),
        new Constant(f)
    );
}

BinaryOperation UnaryOperation::operator-(float f) const {
    return BinaryOperation(
        BinaryOperator::SUB,
        new UnaryOperation(*this),
        new Constant(f)
    );
}

BinaryOperation UnaryOperation::operator*(float f) const {
    return BinaryOperation(
        BinaryOperator::MUL,
        new UnaryOperation(*this),
        new Constant(f)
    );
}

BinaryOperation UnaryOperation::operator/(float f) const {
    return BinaryOperation(
        BinaryOperator::DIV,
        new UnaryOperation(*this),
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