// Write the following program: The user is asked to enter 2 floating point numbers (use doubles). The user is then asked to enter one of the following mathematical symbols: +, -, *, or /. The program computes the answer on the two numbers the user entered and prints the results. If the user enters an invalid symbol, the program should print nothing.

// Example of program:

// Enter a double value: 6.2
// Enter a double value: 5
// Enter +, -, *, or /: *
// 6.2 * 5 is 31

#include <iostream> 

int main()
{
    double a{};
    std::cout << "Enter a double value: ";
    std::cin >> a;

    double b{};
    std::cout << "Enter a double value: ";
    std::cin >> b; 

    char op{};
    std::cout << "Enter +, -, *, or /: ";
    std::cin >> op; 

    if (op == '+')
        std::cout << a << " " << op << " " << b << " is " << a + b;
    else if (op == '-')
        std::cout << a << " " << op << " " << b << " is " << a - b;
    else if (op == '*')
        std::cout << a << " " << op << " " << b << " is " << a * b;
    else if (op == '/')
        std::cout << a << " " << op << " " << b << " is " << a / b;

    return 0;
}