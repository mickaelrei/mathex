#include <iostream>

#include "constant.hpp"
#include "variable.hpp"
#include "binary_operation.hpp"
#include "power.hpp"

int main(int argc, char **argv) {
    // Get value from arg
    float val = 1.0f;
    if (argc > 1) {
        val = atof(argv[1]);
    }

    // f = e^x
    Variable x("x");
    Constant e(2.718281828);
    auto f = pow(e, -x);

    printf("f(x) = e^(-x) | x=%.3f | f(x) = %.3f\n", val, f.eval({{ "x", val }}));

    return 0;
}