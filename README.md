# Math Expressions

Create math expressions directly with C++ operators and evaluate them. Example:

```cpp
// Create variable and function
Variable x("x");
auto f = x*x - 10*x + 16; // x² - 10x + 16

// Create context for variables
VariableContext ctx;
ctx["x"] = 8;

// Evaluate function
printf("f(8) = %.3f\n", f.eval(ctx)); // f(8) = 0.000
```

## Supported operations

- The 4 basic operations: addition, subtraction, multiplication and division
- Exponentiation (use the `pow()` helper function)