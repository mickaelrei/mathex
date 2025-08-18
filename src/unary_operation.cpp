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
    case UnaryOperator::SEC:
        return 1.0f / std::cos(v);
    case UnaryOperator::CSC:
        return 1.0f / std::sin(v);
    case UnaryOperator::COT:
        return 1.0f / std::tan(v);
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

Expression* UnaryOperation::differentiate(const std::string& varName) const {
    auto u = operand->clone();
    auto du = operand->differentiate(varName);

    switch (op) {
    case UnaryOperator::NEG: {
        // Simply negate du
        delete u;
        return new UnaryOperation(UnaryOperator::NEG, du);
    }

    case UnaryOperator::SIN: {
        // (sin(u))' = u'cos(u)
        return new BinaryOperation(
            BinaryOperator::MUL,
            du,
            new UnaryOperation(UnaryOperator::COS, u) // cos(u)
        );
    }

    case UnaryOperator::COS: {
        // (cos(u))' = -u'sin(u)
        return new UnaryOperation(
            UnaryOperator::NEG,
            new BinaryOperation(                          // u'sin(u)
                BinaryOperator::MUL,
                du,
                new UnaryOperation(UnaryOperator::SIN, u) // sin(u)
            )
        );
    }

    case UnaryOperator::TAN: {
        // (tan(u))' = u'(sec(u))^2
        return new BinaryOperation(
            BinaryOperator::MUL,
            du,
            new BinaryOperation(                           // (sec(u))^2
                BinaryOperator::POW,
                new UnaryOperation(UnaryOperator::SEC, u), // sec(u)
                new Constant(2.0f)
            )
        );
    }

    case UnaryOperator::SEC: {
        // (sec(u))' = u'tan(u)sec(u)
        return new BinaryOperation(
            BinaryOperator::MUL,
            du,
            new BinaryOperation(                                    // tan(u)sec(u)
                BinaryOperator::MUL,
                new UnaryOperation(UnaryOperator::TAN, u->clone()), // tan(u)
                new UnaryOperation(UnaryOperator::SEC, u)           // sec(u)
            )
        );
    }

    case UnaryOperator::CSC: {
        // (csc(u))' = -u'csc(u)cot(u)
        return new UnaryOperation(
            UnaryOperator::NEG,
            new BinaryOperation(                                        // u'csc(u)cot(u)
                BinaryOperator::MUL,
                du,
                new BinaryOperation(                                    // tan(u)sec(u)
                    BinaryOperator::MUL,
                    new UnaryOperation(UnaryOperator::CSC, u->clone()), // csc(u)
                    new UnaryOperation(UnaryOperator::COT, u)           // cot(u)
                )
            )
        );
    }

    case UnaryOperator::COT: {
        // (cot(u))' = -u'(csc(u))^2
        return new UnaryOperation(
            UnaryOperator::NEG,
            new BinaryOperation(                               // u'(csc(u))^2
                BinaryOperator::MUL,
                du,
                new BinaryOperation(                           // (csc(u))^2
                    BinaryOperator::POW,
                    new UnaryOperation(UnaryOperator::CSC, u), // csc(u)
                    new Constant(2.0f)
                )
            )
        );
    }

    case UnaryOperator::LN: {
        // (ln(u))' = u'/u
        return new BinaryOperation(BinaryOperator::DIV, du, u);
    }

    case UnaryOperator::LOG10: {
        // (log10(u))' = u' / (ln(10) * u)
        return new BinaryOperation(
            BinaryOperator::DIV,
            du,
            new BinaryOperation(                // ln(10) * u
                BinaryOperator::MUL,
                new Constant(std::log(10.0f)),  // ln(10)
                u
            )
        );
    }

    case UnaryOperator::EXP: {
        // (e^u)' = u'e^u
        return new BinaryOperation(BinaryOperator::MUL, du, u);
    }

    case UnaryOperator::SQRT: {
        // (sqrt(u))' = u' / 2sqrt(u)
        return new BinaryOperation(
            BinaryOperator::DIV,
            du,
            new BinaryOperation(                            // 2sqrt(u)
                BinaryOperator::MUL,
                new Constant(2.0f),                         // 2
                new UnaryOperation(UnaryOperator::SQRT, u)  // sqrt(u)
            )
        );
    }

    case UnaryOperator::ABS: {
        // (|x|)' = u' * |u| / u
        return new BinaryOperation(
            BinaryOperator::MUL,
            du,
            new BinaryOperation(                                     // |u| / u
                BinaryOperator::DIV,
                new UnaryOperation(UnaryOperator::ABS, u->clone()),  // |u|
                u                                                    // u
            )
        );
    }
    }

    // Should not be reached
    return new Constant(0.0f);
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