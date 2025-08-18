#include <iostream>

#include "constant.hpp"
#include "variable.hpp"
#include "binary_operation.hpp"
#include "functions.hpp"

int main(int argc, char **argv) {
    // Get value from arg
    float val = 1.0f;
    if (argc > 1) {
        val = atof(argv[1]);
    }

    // Create complex function
    // f = ln( (x² + 25sin(x) + 25) / (|x³| + 10) )
    mathex::Variable x("x");
    mathex::Constant e(2.718281828);
    auto f = ln( (pow(x, 2) + 25*sin(x) + 25) / (abs(pow(x, 3)) + 10) );
    printf("f(x) = x³ | x = %.3f | f(x) = %.3f\n", val, f.eval({{ "x", val }}));

    // Get f' (derivative)
    auto df = f.differentiate("x");
    printf("f'(x) = 3x² | x = %.3f | f'(x) = %.3f\n", val, df->eval({{ "x", val }}));

    // Derivative is returned as heap pointer; need to delete it after usage
    delete df;

    return 0;
}