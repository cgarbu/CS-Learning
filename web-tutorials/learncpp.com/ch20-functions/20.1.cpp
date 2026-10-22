// In this quiz, we’re going to write a version of our basic calculator using function pointers.
// 1a) Create a short program asking the user for two integer inputs and a mathematical operation ('+', '-', '*', '/'). Ensure the user enters a valid operation.
// 1b) Write functions named add(), subtract(), multiply(), and divide(). These should take two integer parameters and return an integer.
// 1c) Create a type alias named ArithmeticFunction for a pointer to a function that takes two integer parameters and returns an integer. 
// Use std::function, and include the appropriate header.
// 1d) Write a function named getArithmeticFunction() that takes an operator character and returns the appropriate function as a function pointer.
// 1e) Modify your main() function to call getArithmeticFunction(). Call the return value from that function with your inputs and print the result.

#include <limits> 
#include <functional> 
#include <string> 
#include <string_view> 
#include <iostream>

// using ArithemticFunction = int(*)(int, int); <- Function Pointer
using ArithmeticFunction = std::function<int(int, int)>; // <- Callable Wrapper 

int getInteger()
{
    std::cout << "Enter an integer: "; 
    int input{ }; 
    while (!(std::cin >> input))
    {
        std::cout << "Invalid input. Enter an integer: ";

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return input; 
}

char getMathOperation()
{
    constexpr std::string_view validOperations{ "+-*/" };

    std::cout << "Enter a mathematical operation : "; 
    char mathOperation{ }; 

    // std::string_view::npos is a special value (typically of std::size_t) that signifies a search did not find the requested character or substring.
    while (!(std::cin >> mathOperation) || validOperations.find(mathOperation) == std::string_view::npos)
    {
        std::cout << "Invalid input. Enter a mathematical operation ('+', '-', '*', '/'): ";

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return mathOperation; 
}

int add(int a, int b)
{
    return a + b; 
}

int subtract(int a, int b)
{
    return a - b; 
}

int multiply(int a, int b)
{
    return a * b;
}

int divide(int a, int b)
{
    return a / b; 
}

ArithmeticFunction getArithmeticFunction(char mathOperation)
{
    // To be pedantic, I add the reference (&) operator in front of each, but the return types are implicitly converted to function pointers.  
    switch (mathOperation)
    {
    case '+':   return &add;
    case '-':   return &subtract;
    case '*':   return &multiply;
    case '/':   return &divide; 
    default:    return nullptr;   
    }
}

int main()
{
    int integerOne{ getInteger() };
    int integerTwo{ getInteger() };
    char mathOperation{ getMathOperation() };

    ArithmeticFunction function{ getArithmeticFunction(mathOperation) };
    if (function)
        std::cout << integerOne << ' ' << mathOperation << ' ' << integerTwo << " = " << function(integerOne, integerTwo); 

    return 0;
}