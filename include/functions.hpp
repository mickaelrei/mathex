#pragma once

#include "unary_operation.hpp"
#include "binary_operation.hpp"
#include "constant.hpp"

namespace mathex {

inline UnaryOperation sin(const Expression& expr) {
    return UnaryOperation(UnaryOperator::SIN, expr.clone());
}

inline UnaryOperation cos(const Expression& expr) {
    return UnaryOperation(UnaryOperator::COS, expr.clone());
}

inline UnaryOperation tan(const Expression& expr) {
    return UnaryOperation(UnaryOperator::TAN, expr.clone());
}

inline UnaryOperation csc(const Expression& expr) {
    return UnaryOperation(UnaryOperator::CSC, expr.clone());
}

inline UnaryOperation sec(const Expression& expr) {
    return UnaryOperation(UnaryOperator::SEC, expr.clone());
}

inline UnaryOperation cot(const Expression& expr) {
    return UnaryOperation(UnaryOperator::COT, expr.clone());
}

inline UnaryOperation ln(const Expression& expr) {
    return UnaryOperation(UnaryOperator::LN, expr.clone());
}

inline UnaryOperation log10(const Expression& expr) {
    return UnaryOperation(UnaryOperator::LOG10, expr.clone());
}

inline UnaryOperation exp(const Expression& expr) {
    return UnaryOperation(UnaryOperator::EXP, expr.clone());
}

inline UnaryOperation sqrt(const Expression& expr) {
    return UnaryOperation(UnaryOperator::SQRT, expr.clone());
}

inline UnaryOperation abs(const Expression& expr) {
    return UnaryOperation(UnaryOperator::ABS, expr.clone());
}

inline BinaryOperation pow(const Expression& base, const Expression& exp) {
    return BinaryOperation(
        BinaryOperator::POW,
        base.clone(),
        exp.clone()
    );
}

inline BinaryOperation pow(const Expression& base, float exp) {
    return pow(base, Constant(exp));
}

inline BinaryOperation pow(float base, const Expression& exp) {
    return pow(Constant(base), exp);
}

inline BinaryOperation pow(float base, float exp) {
    return pow(Constant(base), Constant(exp));
}

} // namespace mathex