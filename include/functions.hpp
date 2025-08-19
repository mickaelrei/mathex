#pragma once

#include "unary_operation.hpp"
#include "binary_operation.hpp"
#include "constant.hpp"

namespace mathex {

class OperationNeg : public UnaryOperation {
public:
    OperationNeg(Expression* operand) : UnaryOperation{operand} {}

    virtual float eval(const VariableContext& ctx) const override;
    virtual Expression* clone() const override;
    virtual Expression* differentiate(const std::string& varName) const override;
};

class OperationSin : public UnaryOperation {
public:
    OperationSin(Expression* operand) : UnaryOperation{operand} {}

    virtual float eval(const VariableContext& ctx) const override;
    virtual Expression* clone() const override;
    virtual Expression* differentiate(const std::string& varName) const override;
};

class OperationCos : public UnaryOperation {
public:
    OperationCos(Expression* operand) : UnaryOperation{operand} {}

    virtual float eval(const VariableContext& ctx) const override;
    virtual Expression* clone() const override;
    virtual Expression* differentiate(const std::string& varName) const override;
};

class OperationTan : public UnaryOperation {
public:
    OperationTan(Expression* operand) : UnaryOperation{operand} {}

    virtual float eval(const VariableContext& ctx) const override;
    virtual Expression* clone() const override;
    virtual Expression* differentiate(const std::string& varName) const override;
};

class OperationCsc : public UnaryOperation {
public:
    OperationCsc(Expression* operand) : UnaryOperation{operand} {}

    virtual float eval(const VariableContext& ctx) const override;
    virtual Expression* clone() const override;
    virtual Expression* differentiate(const std::string& varName) const override;
};

class OperationSec : public UnaryOperation {
public:
    OperationSec(Expression* operand) : UnaryOperation{operand} {}

    virtual float eval(const VariableContext& ctx) const override;
    virtual Expression* clone() const override;
    virtual Expression* differentiate(const std::string& varName) const override;
};

class OperationCot : public UnaryOperation {
public:
    OperationCot(Expression* operand) : UnaryOperation{operand} {}

    virtual float eval(const VariableContext& ctx) const override;
    virtual Expression* clone() const override;
    virtual Expression* differentiate(const std::string& varName) const override;
};

class OperationLn : public UnaryOperation {
public:
    OperationLn(Expression* operand) : UnaryOperation{operand} {}

    virtual float eval(const VariableContext& ctx) const override;
    virtual Expression* clone() const override;
    virtual Expression* differentiate(const std::string& varName) const override;
};

class OperationLog10 : public UnaryOperation {
public:
    OperationLog10(Expression* operand) : UnaryOperation{operand} {}

    virtual float eval(const VariableContext& ctx) const override;
    virtual Expression* clone() const override;
    virtual Expression* differentiate(const std::string& varName) const override;
};

class OperationExp : public UnaryOperation {
public:
    OperationExp(Expression* operand) : UnaryOperation{operand} {}

    virtual float eval(const VariableContext& ctx) const override;
    virtual Expression* clone() const override;
    virtual Expression* differentiate(const std::string& varName) const override;
};

class OperationSqrt : public UnaryOperation {
public:
    OperationSqrt(Expression* operand) : UnaryOperation{operand} {}

    virtual float eval(const VariableContext& ctx) const override;
    virtual Expression* clone() const override;
    virtual Expression* differentiate(const std::string& varName) const override;
};

class OperationAbs : public UnaryOperation {
public:
    OperationAbs(Expression* operand) : UnaryOperation{operand} {}

    virtual float eval(const VariableContext& ctx) const override;
    virtual Expression* clone() const override;
    virtual Expression* differentiate(const std::string& varName) const override;
};


inline OperationSin sin(const Expression& expr) {
    return OperationSin(expr.clone());
}

inline OperationCos cos(const Expression& expr) {
    return OperationCos(expr.clone());
}

inline OperationTan tan(const Expression& expr) {
    return OperationTan(expr.clone());
}

inline OperationCsc csc(const Expression& expr) {
    return OperationCsc(expr.clone());
}

inline OperationSec sec(const Expression& expr) {
    return OperationSec(expr.clone());
}

inline OperationCot cot(const Expression& expr) {
    return OperationCot(expr.clone());
}

inline OperationLn ln(const Expression& expr) {
    return OperationLn(expr.clone());
}

inline OperationLog10 log10(const Expression& expr) {
    return OperationLog10(expr.clone());
}

inline OperationExp exp(const Expression& expr) {
    return OperationExp(expr.clone());
}

inline OperationSqrt sqrt(const Expression& expr) {
    return OperationSqrt(expr.clone());
}

inline OperationAbs abs(const Expression& expr) {
    return OperationAbs(expr.clone());
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