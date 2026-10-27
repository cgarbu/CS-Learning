// Create a struct to hold a fraction. The struct should have an integer numerator and an integer denominator member.

// Write a function to read in a Fraction from the user, and use it to read-in two fraction objects. Write another function to multiply two Fractions together and return the result as a Fraction (you don’t need to reduce the fraction). Write another function that prints a fraction.

// Your program’s output should match the following:

// Enter a value for the numerator: 1
// Enter a value for the denominator: 2

// Enter a value for the numerator: 3
// Enter a value for the denominator: 4

// Your fractions multiplied together: 3/8

// When multiplying two fractions together, the resulting numerator is the product of the two numerators, and the resulting denominator is the product of the two denominators.

#include <iostream>

struct Fraction
{
    int numerator{ 0 };
    int denominator{ 1 };
};

Fraction readInFrac()
{
    Fraction fraction{ }; 
    std::cout << "Enter a value for the numerator: ";
    std::cin >> fraction.numerator;
    std::cout << "Enter a value for the denominator: ";
    std::cin >> fraction.denominator; 

    return fraction; 
}

constexpr Fraction multiplyTwoFracs(const Fraction& fractionOne, const Fraction& fractionTwo)
{
    return { fractionOne.numerator * fractionTwo.numerator, fractionOne.denominator * fractionTwo.denominator };
}

void printMultipliedFraction(const Fraction& fractionOne, const Fraction& fractionTwo)
{
    Fraction multipliedFraction{ multiplyTwoFracs(fractionOne, fractionTwo) };

    std::cout << "Your fractions multiplied together: " << multipliedFraction.numerator << '/' << multipliedFraction.denominator; 
}

int main()
{
    Fraction fractionOne{ readInFrac() };
    Fraction fractionTwo{ readInFrac() };

    printMultipliedFraction(fractionOne, fractionTwo);

    return 0;
}