// Write a program that asks the user to input an integer, and tells the user whether the number is even or odd. Write a constexpr function called isEven() that returns true if an integer passed to it is even, and false otherwise. Use the remainder operator to test whether the integer parameter is even. Make sure isEven() works with both positive and negative numbers.

// Your program should match the following output:

// Enter an integer: 5
// 5 is odd

#include <iostream>

constexpr bool isEven(int x)
{
    return x % 2 == 0;
}

int main()
{
    int x{};
    std::cout << "Enter an integer: ";
    std::cin >> x;

    if (isEven(x))
        std::cout << x << " is even.";
    else
        std::cout << x << " is odd.";

    return 0;
}