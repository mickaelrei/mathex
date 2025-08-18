#include "pow.hpp"

namespace mathex {

BinaryOperation pow(const Expression& base, const Expression& exp) {
    return BinaryOperation(
        BinaryOperator::POW,
        base.clone(),
        exp.clone()
    );
}

BinaryOperation pow(const Expression& base, float exp) {
    return pow(base, Constant(exp));
}

BinaryOperation pow(float base, const Expression& exp) {
    return pow(Constant(base), exp);
}

BinaryOperation pow(float base, float exp) {
    return pow(Constant(base), Constant(exp));
}

} // namespace mathex