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

Expression* BinaryOperation::differentiate(const std::string& varName) const {
    auto du = left->differentiate(varName);
    auto dv = right->differentiate(varName);

    auto u = left->clone();
    auto v = right->clone();

    switch (op) {
    case BinaryOperator::ADD: {
        // Sum rule: (u + v)' = u' + v'
        delete u;
        delete v;
        return new BinaryOperation(BinaryOperator::ADD, du, dv);
    }

    case BinaryOperator::SUB: {
        // Difference rule: (u - v)' = u' - v'
        delete u;
        delete v;
        return new BinaryOperation(BinaryOperator::SUB, du, dv);
    }

    case BinaryOperator::MUL: {
        // Product rule: (u * v)' = u'v + uv'
        return new BinaryOperation(
            BinaryOperator::ADD,
            new BinaryOperation(BinaryOperator::MUL, du, v), // u'v
            new BinaryOperation(BinaryOperator::MUL, u, dv)  // uv'
        );
    }

    case BinaryOperator::DIV: {
        // Quotient rule: (u / v)' = (u'v - uv') / v^2
        return new BinaryOperation(
            BinaryOperator::DIV,
            new BinaryOperation(                                             // u'v - uv'
                BinaryOperator::SUB,
                new BinaryOperation(BinaryOperator::MUL, du, v->clone()),    // u'v
                new BinaryOperation(BinaryOperator::MUL, u, dv)              // uv'
            ),
            new BinaryOperation(BinaryOperator::POW, v, new Constant(2.0f))  // v^2
        );
    }

    case BinaryOperator::POW: {
        // Check if the exponent 'v' is a constant
        if (dynamic_cast<Constant*>(right) != nullptr) {
            // Simple Power Rule: (u^n)' = n * u^(n-1) * u'
            delete dv;
            return new BinaryOperation(
                BinaryOperator::MUL,
                du,
                new BinaryOperation(              // v * u^(v - 1)
                    BinaryOperator::MUL,
                    v->clone(),
                    new BinaryOperation(          // u^(v - 1)
                       BinaryOperator::POW,
                        u,
                        new BinaryOperation(      // v - 1
                            BinaryOperator::SUB,
                            v,
                            new Constant(1.0f)
                        )
                    )
                )
            );
        }
        // General Power rule: (u^v)' = (u^v)(v'ln(u) + vu'/u)
        return new BinaryOperation(
            BinaryOperator::MUL,
            new BinaryOperation(BinaryOperator::POW, u->clone(), v),   // u^v
            new BinaryOperation(                                       // v'ln(u) + vu'/u
                BinaryOperator::ADD,
                new BinaryOperation(                                   // v'ln(u)
                    BinaryOperator::MUL,
                    dv,
                    new UnaryOperation(UnaryOperator::LN, u->clone())  // ln(u)
                ),
                new BinaryOperation(                                   // vu'/u
                    BinaryOperator::MUL,
                    v->clone(),
                    new BinaryOperation(BinaryOperator::DIV, du, u)    // u'/u
                )
            )
        );
    }
    }

    // Should not be reached
    return new Constant(0.0f);
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
