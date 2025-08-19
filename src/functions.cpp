#include <cmath>

#include "functions.hpp"

namespace mathex {

float OperationNeg::eval(const VariableContext& ctx) const {
    return -operand->eval(ctx);
}

Expression* OperationNeg::clone() const {
    return new OperationNeg(operand->clone());
}

Expression* OperationNeg::differentiate(const std::string& varName) const {
    // (-u)' = -u'
    auto du = operand->differentiate(varName);
    return new OperationNeg(du);
}

float OperationSin::eval(const VariableContext& ctx) const {
    return std::sin(operand->eval(ctx));
}

Expression* OperationSin::clone() const {
    return new OperationSin(operand->clone());
}

Expression* OperationSin::differentiate(const std::string& varName) const {
    // (sin(u))' = u'cos(u)
    auto u = operand->clone();
    auto du = operand->differentiate(varName);
    return new BinaryOperation(BinaryOperator::MUL, du, new OperationCos(u));
}

float OperationCos::eval(const VariableContext& ctx) const {
    return std::cos(operand->eval(ctx));
}

Expression* OperationCos::clone() const {
    return new OperationCos(operand->clone());
}

Expression* OperationCos::differentiate(const std::string& varName) const {
    // (cos(u))' = -u'sin(u)
    auto u = operand->clone();
    auto du = operand->differentiate(varName);
    return new OperationNeg(
        new BinaryOperation(BinaryOperator::MUL, du, new OperationSin(u))
    );
}

float OperationTan::eval(const VariableContext& ctx) const {
    return std::tan(operand->eval(ctx));
}

Expression* OperationTan::clone() const {
    return new OperationTan(operand->clone());
}

Expression* OperationTan::differentiate(const std::string& varName) const {
    // (tan(u))' = u'(sec(u))^2
    auto u = operand->clone();
    auto du = operand->differentiate(varName);
    return new BinaryOperation(
        BinaryOperator::MUL,
        du,
        new BinaryOperation(     // (sec(u))^2
            BinaryOperator::POW,
            new OperationSec(u), // sec(u)
            new Constant(2.0f)
        )
    );
}

float OperationCsc::eval(const VariableContext& ctx) const {
    return 1.0f / std::sin(operand->eval(ctx));
}

Expression* OperationCsc::clone() const {
    return new OperationCsc(operand->clone());
}

Expression* OperationCsc::differentiate(const std::string& varName) const {
    // (csc(u))' = -u'csc(u)cot(u)
    auto u = operand->clone();
    auto du = operand->differentiate(varName);
    return new OperationNeg(
        new BinaryOperation(                  // u'csc(u)cot(u)
            BinaryOperator::MUL,
            du,
            new BinaryOperation(              // tan(u)sec(u)
                BinaryOperator::MUL,
                new OperationCsc(u->clone()), // csc(u)
                new OperationCot(u)           // cot(u)
            )
        )
    );
}

float OperationSec::eval(const VariableContext& ctx) const {
    return 1.0f / std::cos(operand->eval(ctx));
}

Expression* OperationSec::clone() const {
    return new OperationSec(operand->clone());
}

Expression* OperationSec::differentiate(const std::string& varName) const {
    // (sec(u))' = u'tan(u)sec(u)
    auto u = operand->clone();
    auto du = operand->differentiate(varName);
    return new BinaryOperation(
        BinaryOperator::MUL,
        du,
        new BinaryOperation(              // tan(u)sec(u)
            BinaryOperator::MUL,
            new OperationTan(u->clone()), // tan(u)
            new OperationSec(u)           // sec(u)
        )
    );
}

float OperationCot::eval(const VariableContext& ctx) const {
    return 1.0f / std::tan(operand->eval(ctx));
}

Expression* OperationCot::clone() const {
    return new OperationCot(operand->clone());
}

Expression* OperationCot::differentiate(const std::string& varName) const {
    // (cot(u))' = -u'(csc(u))^2
    auto u = operand->clone();
    auto du = operand->differentiate(varName);
    return new OperationNeg(
        new BinaryOperation(         // u'(csc(u))^2
            BinaryOperator::MUL,
            du,
            new BinaryOperation(     // (csc(u))^2
                BinaryOperator::POW,
                new OperationCsc(u), // csc(u)
                new Constant(2.0f)
            )
        )
    );
}

float OperationLn::eval(const VariableContext& ctx) const {
    return std::log(operand->eval(ctx));
}

Expression* OperationLn::clone() const {
    return new OperationLn(operand->clone());
}

Expression* OperationLn::differentiate(const std::string& varName) const {
    // (ln(u))' = u'/u
    auto u = operand->clone();
    auto du = operand->differentiate(varName);
    return new BinaryOperation(BinaryOperator::DIV, du, u);
}

float OperationLog10::eval(const VariableContext& ctx) const {
    return std::log10(operand->eval(ctx));
}

Expression* OperationLog10::clone() const {
    return new OperationLog10(operand->clone());
}

Expression* OperationLog10::differentiate(const std::string& varName) const {
    // (log10(u))' = u' / (ln(10) * u)
    auto u = operand->clone();
    auto du = operand->differentiate(varName);
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

float OperationExp::eval(const VariableContext& ctx) const {
    return std::exp(operand->eval(ctx));
}

Expression* OperationExp::clone() const {
    return new OperationExp(operand->clone());
}

Expression* OperationExp::differentiate(const std::string& varName) const {
    // (e^u)' = u'e^u
    auto u = operand->clone();
    auto du = operand->differentiate(varName);
    return new BinaryOperation(BinaryOperator::MUL, du, u);
}

float OperationSqrt::eval(const VariableContext& ctx) const {
    return std::sqrt(operand->eval(ctx));
}

Expression* OperationSqrt::clone() const {
    return new OperationSqrt(operand->clone());
}

Expression* OperationSqrt::differentiate(const std::string& varName) const {
    // (sqrt(u))' = u' / 2sqrt(u)
    auto u = operand->clone();
    auto du = operand->differentiate(varName);
    return new BinaryOperation(
        BinaryOperator::DIV,
        du,
        new BinaryOperation(      // 2sqrt(u)
            BinaryOperator::MUL,
            new Constant(2.0f),   // 2
            new OperationSqrt(u)  // sqrt(u)
        )
    );
}

float OperationAbs::eval(const VariableContext& ctx) const {
    return std::abs(operand->eval(ctx));
}

Expression* OperationAbs::clone() const {
    return new OperationAbs(operand->clone());
}

Expression* OperationAbs::differentiate(const std::string& varName) const {
    // (|x|)' = u' * |u| / u
    auto u = operand->clone();
    auto du = operand->differentiate(varName);
    return new BinaryOperation(
        BinaryOperator::MUL,
        du,
        new BinaryOperation(              // |u| / u
            BinaryOperator::DIV,
            new OperationAbs(u->clone()), // |u|
            u                             // u
        )
    );
}

} // namespace mathex