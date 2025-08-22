# Mathex

Mathex is a simple library to create math expressions directly with C++ operators and evaluate them. Example:

```cpp
// Create variable and function
mathex::Variable x("x");
auto f = x*x - 10*x + 16; // x² - 10x + 16

// Create context for variables
mathex::VariableContext ctx;
ctx["x"] = 8;

// Evaluate function
printf("f(8) = %.3f\n", f.eval(ctx)); // f(8) = 0.000
```

## Supported operations

- The 4 basic operations: addition, subtraction, multiplication and division
- Exponentiation (use the `pow` helper function)
- Functions such as `sin`, `cos`, `ln` `sqrt`, `abs` etc.

## Derivatives

You can get the derivative of an expression with respect to a specific variable name. Example:

```cpp
mathex::Variable x("x");
auto f = ln(pow(x, 2)); // ln(x²)
auto df = f.differentiate("x"); // 2/x

// The returned derivative is a pointer to an expression; you must delete it manually after usage
printf("f'(4) = %.3f\n", df->eval({{ "x", 4 }})); // f'(4) = 0.500
delete df;
```