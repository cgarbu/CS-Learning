// Write a complete program that reads an integer from the user, doubles it using the doubleNumber() 
// function you wrote in the previous quiz question, and then prints the doubled value out to the console.

#include <iostream>

int doubleNumber(int x)
{
    return x * 2;
}

int main()
{
    int x{};
    std::cin >> x;

    std::cout << doubleNumber(x);

    return 0;
}