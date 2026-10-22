// a) Write a class named Fraction that has an integer numerator and denominator member. Write a print() function that prints out the fraction.
// This should print:
// 1/4
// 1/2

// b) Add overloaded multiplication operators to handle multiplication between a Fraction and integer, and between two Fractions. Use the friend function method.

// Hint: To multiply two fractions, first multiply the two numerators together, and then multiply the two denominators together. To multiply a fraction and an integer, multiply the numerator of the fraction by the integer and leave the denominator alone.


#include <iostream>

class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    explicit Fraction(int numerator, int denominator=1)
        : m_numerator{ numerator }
        , m_denominator{ denominator }
    {
    }

    void print()
    {
        std::cout << m_numerator << '/' << m_denominator << '\n';
    }

    friend Fraction operator*(const Fraction& a, const int& b);
    friend Fraction operator*(const Fraction& a, const Fraction& b);
};

Fraction operator*(const Fraction& a, const int& b)
{   
    return a.m_numerator * b; 
}

Fraction operator*(const Fraction& a, const Fraction& b)
{

}

int main()
{
    Fraction f1{2, 5};
    f1.print();

    Fraction f2{3, 8};
    f2.print();

    Fraction f3{ f1 * f2 };
    f3.print();

    Fraction f4{ f1 * 2 };
    f4.print();

    Fraction f5{ 2 * f2 };
    f5.print();

    Fraction f6{ Fraction{1, 2} * Fraction{2, 3} * Fraction{3, 4} };
    f6.print();

    return 0;
}