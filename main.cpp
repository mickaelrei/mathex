#include <iostream>

#include "constant.hpp"
#include "variable.hpp"
#include "binary_operation.hpp"

int main(int argc, char **argv) {
    // Get upper bound from args
    float upperBound = 1.0f;
    if (argc > 1) {
        upperBound = atof(argv[1]);
    }

    // Calculate integral of x² from 0 to upperBound
    Variable x("x");
    const auto f = x*x;

    const float dt = 0.0001f;
    float area = 0.0f;
    VariableContext ctx;
    for (float t = 0.0f; t < std::abs(upperBound); t += dt) {
        ctx["x"] = t;
        area += f.eval(ctx) * dt;
    }
    if (upperBound < 0.0f) {
        area = -area; // Flip integral bounds
    }

    // Calculate actual area
    const auto integral = x*x*x / 3;
    float realArea = 0.0f;

    // Eval as f(upperBound) - f(0)
    ctx["x"] = upperBound;
    realArea += integral.eval(ctx); // eval at x=upperBound
    ctx["x"] = 0.0f;
    realArea -= integral.eval(ctx); // eval at x=0
    
    // Compare result with actual area
    printf("real area: %.5f\n", realArea);
    printf("calculated area: %.5f\n", area);
    printf("difference: %.5f\n", std::abs(realArea - area));

    return 0;
}