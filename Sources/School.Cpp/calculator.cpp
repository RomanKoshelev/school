#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>

// Calculator: supports +, -, *, / with floating point numbers
// Usage: enter expressions like "3.5 + 2", "10 / 4", etc.
// Type "exit" to quit.

class Calculator {
public:
    double add(double a, double b) { return a + b; }
    double sub(double a, double b) { return a - b; }
    double mul(double a, double b) { return a * b; }
    double div(double a, double b) {
        if (b == 0.0)
            throw std::invalid_argument("Division by zero");
        return a / b;
    }

    double evaluate(double a, char op, double b) {
        switch (op) {
            case '+': return add(a, b);
            case '-': return sub(a, b);
            case '*': return mul(a, b);
            case '/': return div(a, b);
            default:
                throw std::invalid_argument(std::string("Unknown operator: ") + op);
        }
    }
};

void calculator_run() {
    Calculator calc;
    std::string line;

    std::cout << "Calculator (enter 'exit' to quit)\n";
    std::cout << "Format: <number> <+|-|*|/> <number>\n\n";

    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break;
        if (line == "exit" || line == "quit") break;
        if (line.empty()) continue;

        double a, b;
        char op;
        std::istringstream ss(line);

        if (!(ss >> a >> op >> b)) {
            std::cout << "Invalid input. Example: 3.5 + 2\n";
            continue;
        }

        try {
            double result = calc.evaluate(a, op, b);
            std::cout << "= " << result << "\n";
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }
}

void calculator_test() {
    std::cout << "calculator_test\n\n";

    Calculator calc;

    // Basic operations
    _ASSERTE(calc.add(2, 3)    == 5.0);
    _ASSERTE(calc.sub(10, 4)   == 6.0);
    _ASSERTE(calc.mul(3, 4)    == 12.0);
    _ASSERTE(calc.div(9, 3)    == 3.0);

    // Floating point
    _ASSERTE(calc.div(1, 4)    == 0.25);
    _ASSERTE(calc.mul(1.5, 2)  == 3.0);

    // Negative numbers
    _ASSERTE(calc.add(-5, 3)   == -2.0);
    _ASSERTE(calc.sub(0, 7)    == -7.0);

    // Division by zero
    bool caught = false;
    try {
        calc.div(5, 0);
    } catch (const std::invalid_argument&) {
        caught = true;
    }
    _ASSERTE(caught);

    std::cout << "add(2, 3)   = " << calc.add(2, 3)   << "\n";
    std::cout << "sub(10, 4)  = " << calc.sub(10, 4)  << "\n";
    std::cout << "mul(3, 4)   = " << calc.mul(3, 4)   << "\n";
    std::cout << "div(9, 3)   = " << calc.div(9, 3)   << "\n";
    std::cout << "div(1, 4)   = " << calc.div(1, 4)   << "\n";
    std::cout << "\nAll tests passed.\n\n";
}
