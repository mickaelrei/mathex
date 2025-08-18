#pragma once

#include "binary_operation.hpp"
#include "constant.hpp"
#include "variable.hpp"

BinaryOperation pow(const Expression& base, const Expression& exp);

BinaryOperation pow(const Expression& base, float exp);

BinaryOperation pow(float base, const Expression& exp);

BinaryOperation pow(float base, float exp);