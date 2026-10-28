// Write a program that asks the user to enter a number, and then enter a second number. The program should tell the user what the result of adding and subtracting the two numbers is.

// The output of the program should match the following (assuming inputs of 6 and 4):

// Enter an integer: 6
// Enter another integer: 4
// 6 + 4 is 10.
// 6 - 4 is 2.


#include <iostream>

int main()
{
    int a{}, b{};

    std::cout << "Enter an integer: "; 
    std::cin >> a;

    std::cout << "Enter another integer: ";
    std::cin >> b;

    std::cout << a << " + " << b << " is " << a + b << ".\n"; 
    std::cout << a << " - " << b << " is " << a - b << ".\n"; 

    return 0;
}