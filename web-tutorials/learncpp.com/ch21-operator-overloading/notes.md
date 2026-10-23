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


## 21.3 Overloading operators using normal functions

Using a friend function to overload an operator is convenient because it gives you direct access to the internal members of the classes you’re operating on. In the initial Cents example above, our friend function version of operator+ accessed member variable m_cents directly.

However, if you don’t need that access, you can write your overloaded operators as normal functions. Note that the Cents class above contains an access function (getCents()) that allows us to get at m_cents without having to have direct access to private members. Because of this, we can write our overloaded operator+ as a non-friend:

```c++
#include <iostream>

class Cents
{
private:
  int m_cents{};

public:
  Cents(int cents)
    : m_cents{ cents }
  {}

  int getCents() const { return m_cents; }
};

// note: this function is not a member function nor a friend function!
Cents operator+(const Cents& c1, const Cents& c2)
{
  // use the Cents constructor and operator+(int, int)
  // we don't need direct access to private members here
  return Cents{ c1.getCents() + c2.getCents() };
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


## 21.4 Overloading the I/O operators

1. Overloading operator<< is similar to overloading operator+ (they are both binary operators), except that the parameter types are different.

Implementation of operator<< for our Point class is fairly straightforward -- because C++ already knows how to output doubles using operator<<, and our members are all doubles, we can simply use operator<< to output the data members of our Point. Here is the above Point class with the overloaded operator<<.

```c++
#include <iostream>

class Point
{
private:
    double m_x{};
    double m_y{};
    double m_z{};

public:
    Point(double x=0.0, double y=0.0, double z=0.0)
      : m_x{x}, m_y{y}, m_z{z}
    {
    }

    friend std::ostream& operator<< (std::ostream& out, const Point& point);
};

std::ostream& operator<< (std::ostream& out, const Point& point)
{
    // Since operator<< is a friend of the Point class, we can access Point's members directly.
    out << "Point(" << point.m_x << ", " << point.m_y << ", " << point.m_z << ')'; // actual output done here

    return out; // return std::ostream so we can chain calls to operator<<
}

int main()
{
    const Point point1 { 2.0, 3.0, 4.0 };

    std::cout << point1 << '\n';

    return 0;
}
```

2. It is also possible to overload the input operator. This is done in a manner analogous to overloading the output operator. The key thing you need to know is that std::cin is an object of type std::istream. Here’s our Point class with an overloaded operator>> added:

```c++
#include <iostream>

class Point
{
private:
    double m_x{};
    double m_y{};
    double m_z{};

public:
    Point(double x=0.0, double y=0.0, double z=0.0)
      : m_x{x}, m_y{y}, m_z{z}
    {
    }

    friend std::ostream& operator<< (std::ostream& out, const Point& point);
    friend std::istream& operator>> (std::istream& out, Point& point);
};

std::ostream& operator<< (std::ostream& out, const Point& point)
{
    // Since operator<< is a friend of the Point class, we can access Point's members directly.
    out << "Point(" << point.m_x << ", " << point.m_y << ", " << point.m_z << ')';

    return out;
}

// note that point must be non-const so we can modify the object
std::istream& operator>> (std::istream& in, Point& point)
{
    // This version subject to partial extraction issues (see below)
    in >> point.m_x >> point.m_y >> point.m_z;

    return in;
}

int main()
{
    std::cout << "Enter a point: ";

    Point point{ 1.0, 2.0, 3.0 }; // non-zero test data
    std::cin >> point;

    std::cout << "You entered: " << point << '\n';

    return 0;
}
```

However, the above implementation of operator>> can result in a partial extraction. So how might we avoid this? One way is to make our operations transactional. A transactional operation must either completely succeed or completely fail -- no partial successes or failures are allowed. This is sometimes known as “all or nothing”. If a failure occurs at any point during the transaction, prior changes made by the operation must be undone.

```c++
// note that point must be non-const so we can modify the object
// note that this implementation is a non-friend
std::istream& operator>> (std::istream& in, Point& point)
{
    double x{};
    double y{};
    double z{};

    if (in >> x >> y >> z)      // if all extractions succeeded
        point = Point{x, y, z}; // overwrite our existing point

    return in;
}
```

In this implementation, we’re not overwriting the data members directly with the user’s input. Instead, we’re extracting the user’s input to temporary variables (x, y, and z). Once all extraction attempts have completed, we check whether all extractions were successful. If so, then we update all the members of Point together. Otherwise, we do not update any of them.

Here’s an example of a transactional overloaded operator>> for Point that will cause the input stream to enter failure mode if the user inputs an extractable negative value:

```c++
std::istream& operator>> (std::istream& in, Point& point)
{
    double x{};
    double y{};
    double z{};

    in >> x >> y >> z;
    if (x < 0.0 || y < 0.0 || z < 0.0)       // if any extractable input is negative
        in.setstate(std::ios_base::failbit); // set failure mode manually
    point = in ? Point{x, y, z} : Point{};

    return in;
}
```

## 21.5 Overloading operators using member functions

1. Overloading operators using a member function is very similar to overloading operators using a friend function. When overloading an operator using a member function:
* The overloaded operator must be added as a member function of the left operand.
* The left operand becomes the implicit *this object
* All other operands become function parameters.

Operator overloaded using the member function method:

```c++
#include <iostream>

class Cents
{
private:
    int m_cents {};

public:
    Cents(int cents)
        : m_cents { cents } { }

    // Overload Cents + int
    Cents operator+(int value) const;

    int getCents() const { return m_cents; }
};

// note: this function is a member function!
// the cents parameter in the friend version is now the implicit *this parameter
Cents Cents::operator+ (int value) const
{
    return Cents { m_cents + value };
}

int main()
{
	const Cents cents1 { 6 };
	const Cents cents2 { cents1 + 2 };
	std::cout << "I have " << cents2.getCents() << " cents.\n";

	return 0;
}
```

2. Not everything can be overloaded as a friend function. 

The assignment (=), subscript ([]), function call (()), and member selection (->) operators must be overloaded as member functions, because the language requires them to be. 

Not everything can be overloaded as a member function. Why not? Because the overloaded operator must be added as a member of the left operand. 

3. In most cases, the language leaves it up to you to determine whether you want to use the normal/friend or member function version of the overload. However, one of the two is usually a better choice than the other. The following rules of thumb can help you determine which form is best for a given situation:
* If you’re overloading assignment (=), subscript ([]), function call (()), or member selection (->), do so as a member function.
* If you’re overloading a unary operator, do so as a member function.
* If you’re overloading a binary operator that does not modify its left operand (e.g. operator+), do so as a normal function (preferred) or friend function.
* If you’re overloading a binary operator that modifies its left operand, but you can’t add members to the class definition of the left operand (e.g. operator<<, which has a left operand of type ostream), do so as a normal function (preferred) or friend function.
* If you’re overloading a binary operator that modifies its left operand (e.g. operator+=), and you can modify the definition of the left operand, do so as a member function.


## 21.6 Overloading unary operators +, -, and !

1. Unlike the operators you’ve seen so far, the positive (+), negative (-) and logical not (!) operators all are unary operators, which means they only operate on one operand. Because they only operate on the object they are applied to, typically unary operator overloads are implemented as member functions. All three operators are implemented in an identical manner.

Let’s take a look at how we’d implement operator- on the Cents class we used in a previous example:

```c++
#include <iostream>

class Cents
{
private:
    int m_cents {};

public:
    Cents(int cents): m_cents{cents} {}

    // Overload -Cents as a member function
    Cents operator-() const;

    int getCents() const { return m_cents; }
};

// note: this function is a member function!
Cents Cents::operator-() const
{
    return -m_cents; // since return type is a Cents, this does an implicit conversion from int to Cents using the Cents(int) constructor
}

int main()
{
    const Cents nickle{ 5 };
    std::cout << "A nickle of debt is worth " << (-nickle).getCents() << " cents\n";

    return 0;
}
```


## 21.7 Overloading the comparison operators

1. Because the comparison operators are all binary operators that do not modify their left operands, we will make our overloaded comparison operators friend functions.Here’s an example Car class with an overloaded operator== and operator!=.

Because the comparison operators are all binary operators that do not modify their left operands, we will make our overloaded comparison operators friend functions.

Here’s an example Car class with an overloaded operator== and operator!=.

```c++
#include <iostream>
#include <string>
#include <string_view>

class Car
{
private:
    std::string m_make;
    std::string m_model;

public:
    Car(std::string_view make, std::string_view model)
        : m_make{ make }, m_model{ model }
    {
    }

    friend bool operator== (const Car& c1, const Car& c2);
    friend bool operator!= (const Car& c1, const Car& c2);
};

bool operator== (const Car& c1, const Car& c2)
{
    return (c1.m_make == c2.m_make &&
            c1.m_model == c2.m_model);
}

bool operator!= (const Car& c1, const Car& c2)
{
    return (c1.m_make != c2.m_make ||
            c1.m_model != c2.m_model);
}

int main()
{
    Car corolla{ "Toyota", "Corolla" };
    Car camry{ "Toyota", "Camry" };

    if (corolla == camry)
        std::cout << "a Corolla and Camry are the same.\n";

    if (corolla != camry)
        std::cout << "a Corolla and Camry are not the same.\n";

    return 0;
}
```

Only define overloaded operators that make intuitive sense for your class.

C++20 introduces the spaceship operator (operator<=>), which allows us to reduce the number of comparison functions we need to write down to 2 at most, and sometimes just 1!


## 21.8 Overloading the increment and decrement operators

1. Prefix increment and decrement are overloaded exactly the same as any normal unary operator. We’ll do this one by example:
```c++
#include <iostream>

class Digit
{
private:
    int m_digit{};
public:
    Digit(int digit=0)
        : m_digit{digit}
    {
    }

    Digit& operator++();
    Digit& operator--();

    friend std::ostream& operator<< (std::ostream& out, const Digit& d);
};

Digit& Digit::operator++()
{
    // If our number is already at 9, wrap around to 0
    if (m_digit == 9)
        m_digit = 0;
    // otherwise just increment to next number
    else
        ++m_digit;

    return *this;
}

Digit& Digit::operator--()
{
    // If our number is already at 0, wrap around to 9
    if (m_digit == 0)
        m_digit = 9;
    // otherwise just decrement to next number
    else
        --m_digit;

    return *this;
}

std::ostream& operator<< (std::ostream& out, const Digit& d)
{
	out << d.m_digit;
	return out;
}

int main()
{
    Digit digit { 8 };

    std::cout << digit;
    std::cout << ++digit;
    std::cout << ++digit;
    std::cout << --digit;
    std::cout << --digit;

    return 0;
}
```

```c++
Digit& operator++(); // prefix has no parameter
Digit& operator--(); // prefix has no parameter

Digit operator++(int); // postfix has an int parameter
Digit operator--(int); // postfix has an int parameter
```


## 21.9 Overloading the subscript operator

1. An overloaded operator[] function will always take one parameter: the subscript that the user places between the hard braces. In our IntList case, we expect the user to pass in an integer index, and we’ll return an integer value back as a result.

```c++
#include <iostream>

class IntList
{
private:
    int m_list[10]{};

public:
    int& operator[] (int index)
    {
        return m_list[index];
    }
};

/*
// Can also be implemented outside the class definition
int& IntList::operator[] (int index)
{
    return m_list[index];
}
*/

int main()
{
    IntList list{};
    list[2] = 3; // set a value
    std::cout << list[2] << '\n'; // get a value

    return 0;
}
```

2. The function parameter does not need to be an integral type. 


## 21.10 Overloading the parenthesis operator

1. Let’s take a look at an example that lends itself to overloading this operator:

```c++
class Matrix
{
private:
    double data[4][4]{};
};
```

Matrices are a key component of linear algebra, and are often used to do geometric modeling and 3D computer graphics work. In this case, all you need to recognize is that the Matrix class is a 4 by 4 two-dimensional array of doubles. However, because the () operator can take as many parameters as we want it to have, we can declare a version of operator() that takes two integer index parameters, and use it to access our two-dimensional array. Here is an example of this:

```c++
#include <cassert> // for assert()

class Matrix
{
private:
    double m_data[4][4]{};

public:
    double& operator()(int row, int col);
    double operator()(int row, int col) const; // for const objects
};

double& Matrix::operator()(int row, int col)
{
    assert(row >= 0 && row < 4);
    assert(col >= 0 && col < 4);

    return m_data[row][col];
}

double Matrix::operator()(int row, int col) const
{
    assert(row >= 0 && row < 4);
    assert(col >= 0 && col < 4);

    return m_data[row][col];
}
```

Now we can declare a Matrix and access its elements like this:
```c++
#include <iostream>

int main()
{
    Matrix matrix;
    matrix(1, 2) = 4.5;
    std::cout << matrix(1, 2) << '\n';

    return 0;
}
```

which produces the result:
$$
4.5
$$

Now, let’s overload the () operator again, this time in a way that takes no parameters at all:
```c++
#include <cassert> // for assert()
class Matrix
{
private:
    double m_data[4][4]{};

public:
    double& operator()(int row, int col);
    double operator()(int row, int col) const;
    void operator()();
};

double& Matrix::operator()(int row, int col)
{
    assert(row >= 0 && row < 4);
    assert(col >= 0 && col < 4);

    return m_data[row][col];
}

double Matrix::operator()(int row, int col) const
{
    assert(row >= 0 && row < 4);
    assert(col >= 0 && col < 4);

    return m_data[row][col];
}

void Matrix::operator()()
{
    // reset all elements of the matrix to 0.0
    for (int row{ 0 }; row < 4; ++row)
    {
        for (int col{ 0 }; col < 4; ++col)
        {
            m_data[row][col] = 0.0;
        }
    }
}
```

And here’s our new example:
```c++
#include <iostream>

int main()
{
    Matrix matrix{};
    matrix(1, 2) = 4.5;
    matrix(); // erase matrix
    std::cout << matrix(1, 2) << '\n';

    return 0;
}
```

which produces the result:
$$
0
$$

2. Operator() is also commonly overloaded to implement functors (or function object), which are classes that operate like functions. The advantage of a functor over a normal function is that functors can store data in member variables (since they are classes).

Here’s a simple functor: 
```c++
#include <iostream>

class Accumulator
{
private:
    int m_counter{ 0 };

public:
    int operator() (int i) { return (m_counter += i); }

    void reset() { m_counter = 0; } // optional
};

int main()
{
    Accumulator acc{};
    std::cout << acc(1) << '\n'; // prints 1
    std::cout << acc(3) << '\n'; // prints 4

    Accumulator acc2{};
    std::cout << acc2(10) << '\n'; // prints 10
    std::cout << acc2(20) << '\n'; // prints 30

    return 0;
}
```


## 21.11 Overloading typecasts

1. Let’s show how we overload a typecast to define a conversion from Cents to int:
```c++
class Cents
{
private:
    int m_cents{};
public:
    Cents(int cents=0)
        : m_cents{ cents }
    {
    }

    // Overloaded int cast
    operator int() const { return m_cents; }

    int getCents() const { return m_cents; }
    void setCents(int cents) { m_cents = cents; }
};
```

There are a few things worth noting here:
* Overloaded typecasts must be non-static members, and should be const so they can be used with const objects.
* Overloaded typecasts do not have explicit parameters, as there is no way to pass explicit arguments to them. They do still have a hidden *this parameter, pointing to the implicit object (which is the object to be converted).
* Overloaded typecast do not declare a return type. The name of the conversion (e.g. int) is used as the return type, as it is the only return type allowed. This prevents redundancy in the declaration.

Just like we can make constructors explicit so that they can’t be used for implicit conversions, we can also make our overloaded typecasts explicit for the same reason. Explicit typecasts can only be invoked by casting (e.g. static_cast) or by a form of direct initialization (either parenthesis or brace). They are not considered when doing copy-initialization.
```c++
#include <iostream>

class Cents
{
private:
    int m_cents{};
public:
    Cents(int cents=0)
        : m_cents{ cents }
    {
    }

    explicit operator int() const { return m_cents; } // now marked as explicit

    int getCents() const { return m_cents; }
    void setCents(int cents) { m_cents = cents; }
};

class Dollars
{
private:
    int m_dollars{};
public:
    Dollars(int dollars=0)
        : m_dollars{ dollars }
    {
    }

    operator Cents() const { return Cents { m_dollars * 100 }; }
};

void printCents(Cents cents)
{
//  std::cout << cents;                   // no longer works because cents won't implicit convert to an int
    std::cout << static_cast<int>(cents); // we can use an explicit cast instead
}

int main()
{
    Dollars dollars{ 9 };
    printCents(dollars); // implicit conversion from Dollars to Cents okay because its not marked as explicit

    std::cout << '\n';

    return 0;
}
```

When possible, prefer converting constructors, and avoid overloaded typecasts.


## 21.12 Overloading the assignment operator

1. The copy assignment operator (operator=) is used to copy values from one object to another already existing object.

2. The purpose of the copy constructor and the copy assignment operator are almost equivalent -- both copy one object to another. However, the copy constructor initializes new objects, whereas the assignment operator replaces the contents of existing objects. The difference between the copy constructor and the copy assignment operator causes a lot of confusion for new programmers, but it’s really not all that difficult. Summarizing:
* If a new object has to be created before the copying can occur, the copy constructor is used (note: this includes passing or returning objects by value).
* If a new object does not have to be created before the copying can occur, the assignment operator is used.

3. Overloading the copy assignment operator (operator=) is fairly straightforward, with one specific caveat that we’ll get to. The copy assignment operator must be overloaded as a member function:
```c++
#include <cassert>
#include <iostream>

class Fraction
{
private:
	int m_numerator { 0 };
	int m_denominator { 1 };

public:
	// Default constructor
	Fraction(int numerator = 0, int denominator = 1 )
		: m_numerator { numerator }, m_denominator { denominator }
	{
		assert(denominator != 0);
	}

	// Copy constructor
	Fraction(const Fraction& copy)
		: m_numerator { copy.m_numerator }, m_denominator { copy.m_denominator }
	{
		// no need to check for a denominator of 0 here since copy must already be a valid Fraction
		std::cout << "Copy constructor called\n"; // just to prove it works
	}

	// Overloaded assignment
	Fraction& operator= (const Fraction& fraction);

	friend std::ostream& operator<<(std::ostream& out, const Fraction& f1);

};

std::ostream& operator<<(std::ostream& out, const Fraction& f1)
{
	out << f1.m_numerator << '/' << f1.m_denominator;
	return out;
}

// A simplistic implementation of operator= (see better implementation below)
Fraction& Fraction::operator= (const Fraction& fraction)
{
    // do the copy
    m_numerator = fraction.m_numerator;
    m_denominator = fraction.m_denominator;

    // return the existing object so we can chain this operator
    return *this;
}

int main()
{
    Fraction fiveThirds { 5, 3 };
    Fraction f;
    f = fiveThirds; // calls overloaded assignment
    std::cout << f;

    return 0;
}
```

Be careful of self-assignment. 

Unlike other operators, the compiler will provide an implicit public copy assignment operator for your class if you do not provide a user-defined one. This assignment operator does memberwise assignment (which is essentially the same as the memberwise initialization that default copy constructors do).

Just like other constructors and operators, you can prevent assignments from being made by making your copy assignment operator private or using the delete keyword.


## 21.13 Shallow vs. deep copying

1. Because C++ does not know much about your class, the default copy constructor and default assignment operators it provides use a copying method known as a memberwise copy (also known as a shallow copy). This means that C++ copies each member of the class individually (using the assignment operator for overloaded operator=, and direct initialization for the copy constructor). When classes are simple (e.g. do not contain any dynamically allocated memory), this works very well.

2. One answer to this problem is to do a deep copy on any non-null pointers being copied. A deep copy allocates memory for the copy and then copies the actual value, so that the copy lives in distinct memory from the source. This way, the copy and source are distinct and will not affect each other in any way. Doing deep copies requires that we write our own copy constructors and overloaded assignment operators.

Let’s go ahead and show how this is done for our MyString class:
```c++
// assumes m_data is initialized
void MyString::deepCopy(const MyString& source)
{
    // first we need to deallocate any value that this string is holding!
    delete[] m_data;

    // because m_length is not a pointer, we can shallow copy it
    m_length = source.m_length;

    // m_data is a pointer, so we need to deep copy it if it is non-null
    if (source.m_data)
    {
        // allocate memory for our copy
        m_data = new char[m_length];

        // do the copy
        for (int i{ 0 }; i < m_length; ++i)
            m_data[i] = source.m_data[i];
    }
    else
        m_data = nullptr;
}

// Copy constructor
MyString::MyString(const MyString& source)
{
    deepCopy(source);
}
```

As you can see, this is quite a bit more involved than a simple shallow copy! First, we have to check to make sure source even has a string (line 11). If it does, then we allocate enough memory to hold a copy of that string (line 14). Finally, we have to manually copy the string (lines 17 and 18).

Now let’s do the overloaded assignment operator. The overloaded assignment operator is slightly trickier:
```c++
// Assignment operator
MyString& MyString::operator=(const MyString& source)
{
    // check for self-assignment
    if (this != &source)
    {
        // now do the deep copy
        deepCopy(source);
    }

    return *this;
}
```

Remember the rule of three? If a class requires a user-defined destructor, copy constructor, or copy assignment operator, then it probably requires all three. This is why. If we’re user-defining any of these functions, it’s probably because we’re dealing with dynamic memory allocation. We need the copy constructor and copy assignment to handle deep copies, and the destructor to deallocate memory.

* The default copy constructor and default assignment operators do shallow copies, which is fine for classes that contain no dynamically allocated variables.
* Classes with dynamically allocated variables need to have a copy constructor and assignment operator that do a deep copy.
* Favor using classes in the standard library over doing your own memory management.


## 21.14 Overloading operators and function templates

To overload operators with templates, simply overload the operators involved in the templates themselves.