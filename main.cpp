#include <iostream>

#include "constant.hpp"
#include "variable.hpp"
#include "binary_operation.hpp"

int main(int argc, char **argv) {
    // Build variable and expression function
    Variable x("x");
    auto f = x*x - 10*x + 16;

    // Attempt to get value from argument
    float val = 2.0f;
    if (argc > 1) {
        val = atof(argv[1]);
    }

    // Create variable context
    VariableContext ctx;
    ctx["x"] = val;

    // Testing output
    printf("f(x) = x² - 10x + 16 | x = %.3f | f(x) = %.3f\n", val, f.eval(ctx));

    return 0;
}