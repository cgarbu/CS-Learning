## 21.1 Introduction to operator overloading

1. In C++, operators are implemented as functions. By using function overloading on the operator functions, you can define your own versions of the operators that work with different data types (including classes that you’ve written). Using function overloading to overload operators is called operator overloading.

When evaluating an expression containing an operator, the compiler uses the following rules:
* If all of the operands are fundamental data types, the compiler will call a built-in routine if one exists. If one does not exist, the compiler will produce an error.
* If any of the operands are program-defined types (e.g. one of your classes, or an enum type), the compiler will use the function overload resolution algorithm to see if it can find an overloaded operator that is an unambiguous best match. This may involve implicitly converting one or more operands to match the parameter types of an overloaded operator. It may also involve implicitly converting program-defined types into fundamental types (via an overloaded typecast, which we’ll cover later in this chapter) so that it can match a built-in operator. If no match can be found (or an ambiguous match is found), the compiler will error.

First, almost any existing operator in C++ can be overloaded. The exceptions are: conditional (?:), sizeof, scope (::), member selector (.), pointer member selector (.*), typeid, and the casting operators. 

Second, you can only overload the operators that exist. You can not create new operators or rename existing operators. For example, you could not create an operator** to do exponents. Third, at least one of the operands in an overloaded operator must be a user-defined type. This means you could overload operator+(int, Mystring), but not operator+(int, double).

Third, at least one of the operands in an overloaded operator must be a user-defined type. This means you could overload operator+(int, Mystring), but not operator+(int, double).

An overloaded operator should operate on at least one program-defined type (either as a parameter of the function, or the implicit object).

Fourth, it is not possible to change the number of operands an operator supports.

Finally, all operators keep their default precedence and associativity (regardless of what they’re used for) and this can not be changed.

When overloading operators, it’s best to keep the function of the operators as close to the original intent of the operators as possible.

If the meaning of an overloaded operator is not clear and intuitive, use a named function instead.

Finally, overloaded operators should return values in the way that is consistent with the original operators. Operators that do not modify their operands (e.g. arithmetic operators) should generally return results by value. Operators that modify their leftmost operand (e.g. pre-increment, any of the assignment operators) should generally return the leftmost operand by reference.
* Operators that do not modify their operands (e.g. arithmetic operators) should generally return results by value.
* Operators that modify their leftmost operand (e.g. pre-increment, any of the assignment operators) should generally return the leftmost operand by reference.


## 21.2 Overloading the arithmetic operators using friend functions

1. It turns out that there are three different ways to overload operators: the member function way, the friend function way, and the normal function way.

Consider the following class:

```c++
class Cents
{
private:
	int m_cents {};

public:
	Cents(int cents) : m_cents{ cents } { }
	int getCents() const { return m_cents; }
};
```

The following example shows how to overload operator plus (+) in order to add two “Cents” objects together:

```c++
#include <iostream>

class Cents
{
private:
	int m_cents {};

public:
	Cents(int cents) : m_cents{ cents } { }

	// add Cents + Cents using a friend function
	friend Cents operator+(const Cents& c1, const Cents& c2);

	int getCents() const { return m_cents; }
};

// note: this function is not a member function!
Cents operator+(const Cents& c1, const Cents& c2)
{
	// use the Cents constructor and operator+(int, int)
	// we can access m_cents directly because this is a friend function
	return c1.m_cents + c2.m_cents;
}

int main()
{
	Cents cents1{ 6 };
	Cents cents2{ 8 };
	Cents centsSum{ cents1 + cents2 };
	std::cout << "I have " << centsSum.getCents() << " cents.\n";

	return 0;
}
```

Even though friend functions are not members of the class, they can still be defined inside the class if desired.

