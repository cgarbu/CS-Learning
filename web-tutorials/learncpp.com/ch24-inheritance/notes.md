## 24.1 Introduction to inheritance

Inheritance involves creating new objects by directly acquiring the attributes and behaviors of other objects and then extending or specializing them.

A hierarchy is a diagram that shows how various objects are related.


## 24.2 Basic inheritance in C++

Inheritance in C++ takes place between classes. In an inheritance (is-a) relationship, the class being inherited from is called the parent class, base class, or superclass, and the class doing the inheriting is called the child class, derived class, or subclass.

To have BaseballPlayer inherit from our Person class, the syntax is fairly simple. After the class BaseballPlayer declaration, we use a colon, the word “public”, and the name of the class we wish to inherit. This is called public inheritance. We’ll talk more about what public inheritance means in a future lesson.
```c++
// BaseballPlayer publicly inheriting Person
class BaseballPlayer : public Person
{
public:
    double m_battingAverage{};
    int m_homeRuns{};

    BaseballPlayer(double battingAverage = 0.0, int homeRuns = 0)
       : m_battingAverage{battingAverage}, m_homeRuns{homeRuns}
    {
    }
};
```

Thus, BaseballPlayer objects will have 4 member variables: m_battingAverage and m_homeRuns from BaseballPlayer, and m_name and m_age from Person.
```c++
#include <iostream>
#include <string>
#include <string_view>

class Person
{
public:
    std::string m_name{};
    int m_age{};

    Person(std::string_view name = "", int age = 0)
        : m_name{name}, m_age{age}
    {
    }

    const std::string& getName() const { return m_name; }
    int getAge() const { return m_age; }

};

// BaseballPlayer publicly inheriting Person
class BaseballPlayer : public Person
{
public:
    double m_battingAverage{};
    int m_homeRuns{};

    BaseballPlayer(double battingAverage = 0.0, int homeRuns = 0)
       : m_battingAverage{battingAverage}, m_homeRuns{homeRuns}
    {
    }
};

int main()
{
    // Create a new BaseballPlayer object
    BaseballPlayer joe{};
    // Assign it a name (we can do this directly because m_name is public)
    joe.m_name = "Joe";
    // Print out the name
    std::cout << joe.getName() << '\n'; // use the getName() function we've acquired from the Person base class

    return 0;
}
```

It’s possible to inherit from a class that is itself derived from another class. There is nothing noteworthy or special when doing so -- everything proceeds as in the examples above.

Inheritance allows us to reuse classes by having other classes inherit their members. 


## 24.3 Order of inheritance 

C++ classes construct "downwards" from the base class (superclass) to the derived class (subclass).

This process is actually easy to illustrate.
```c++
#include <iostream>

class Base
{
public:
    int m_id {};

    Base(int id=0)
        : m_id { id }
    {
        std::cout << "Base\n";
    }

    int getId() const { return m_id; }
};

class Derived: public Base
{
public:
    double m_cost {};

    Derived(double cost=0.0)
        : m_cost { cost }
    {
        std::cout << "Derived\n";
    }

    double getCost() const { return m_cost; }
};

int main()
{
    std::cout << "Instantiating Base\n";
    Base base;

    std::cout << "Instantiating Derived\n";
    Derived derived;

    return 0;
}
```

This program produces the following result:
$$
Instantiating Base
Base
Instantiating Derived
Base
Derived
$$

C++ constructs derived classes in phases, starting with the most-base class (at the top of the inheritance tree) and finishing with the most-child class (at the bottom of the inheritance tree). As each class is constructed, the appropriate constructor from that class is called to initialize that part of the class.


## 24.4 Constructors and initialization of derived classes

With non-derived classes, constructors only have to worry about their own members. 

Here’s what actually happens when the base class is instantiated:
1. Memory for base is set aside
2. The appropriate Base constructor is called
3. The member initializer list initializes variables
4. The body of the constructor executes
5. Control is returned to the caller

With derived classes, things are slightly more complex:
1. Memory for derived is set aside (enough for both the Base and Derived portions)
2. The appropriate Derived constructor is called
3. The Base object is constructed first using the appropriate Base constructor. If no base constructor is specified, the default constructor will be used.
4. The member initializer list initializes variables
5. The body of the constructor executes
6. Control is returned to the caller

The only real difference between this case and the non-inherited case is that before the Derived constructor can do anything substantial, the Base constructor is called first. The Base constructor sets up the Base portion of the object, control is returned to the Derived constructor, and the Derived constructor is allowed to finish up its job.

Fortunately, C++ gives us the ability to explicitly choose which Base class constructor will be called! To do this, simply add a call to the Base class constructor in the member initializer list of the derived class:
```c++
class Derived: public Base
{
public:
    double m_cost {};

    Derived(double cost=0.0, int id=0)
        : Base{ id } // Call Base(int) constructor with value id!
        , m_cost{ cost }
    {
    }

    double getCost() const { return m_cost; }
};
```

This is pretty straight forward. Think of it like functions. The Derived constructor calls the Base constructor to intialize id. 

Classes in a long inheritance chain work in exactly the same way.
```c++
#include <iostream>

class A
{
public:
    A(int a)
    {
        std::cout << "A: " << a << '\n';
    }
};

class B: public A
{
public:
    B(int a, double b)
    : A{ a }
    {
        std::cout << "B: " << b << '\n';
    }
};

class C: public B
{
public:
    C(int a, double b, char c)
    : B{ a, b }
    {
        std::cout << "C: " << c << '\n';
    }
};

int main()
{
    C c{ 5, 4.3, 'R' };

    return 0;
}
```

When a derived class is destroyed, each destructor is called in the reverse order of construction. In the above example, when c is destroyed, the C destructor is called first, then the B destructor, then the A destructor. If your base class has virtual functions, your destructor should also be virtual, otherwise undefined behavior will result in certain cases. 


## 24.5 Inheritance and access specifiers

C++ has a third access specifier that we have yet to talk about because it’s only useful in an inheritance context. The protected access specifier allows the class the member belongs to, friends, and derived classes to access the member. However, protected members are not accessible from outside the class.

First, there are three different ways for classes to inherit from other classes: public, protected, and private.

To do so, simply specify which type of access you want when choosing the class to inherit from:
```c++
// Inherit from Base publicly
class Pub: public Base
{
};

// Inherit from Base protectedly
class Pro: protected Base
{
};

// Inherit from Base privately
class Pri: private Base
{
};

class Def: Base // Defaults to private inheritance
{
};
```

If you do not choose an inheritance type, C++ defaults to private inheritance (just like members default to private access if you do not specify otherwise). That gives us 9 combinations: 3 member access specifiers (public, private, and protected), and 3 inheritance types (public, private, and protected).

Use public inheritance unless you have a specific reason to do otherwise.

| Base Class Access | Public Inheritance | Private Inheritance | Protected Inheritance |
|-------------------|--------------------|---------------------|-----------------------|
| Public            | Public             | Private             | Protected             |
| Protected         | Protected          | Private             | Protected             |
| Private           | Inaccessible       | Inaccessible        | Inaccessible          |


## 24.7 Calling inherited functions and overriding behavior

When a member function is called on a derived class object, the compiler first looks to see if any function with that name exists in the derived class. If so, all overloaded functions with that name are considered, and the function overload resolution process is used to determine whether there is a best match. If not, the compiler walks up the inheritance chain, checking each parent class in turn in the same way.

Put another way, the compiler will select the best matching function from the most-derived class with at least one function with that name.

First, let’s explore what happens when the derived class has no matching function, but the base class does:
```c++
#include <iostream>

class Base
{
public:
    Base() { }

    void identify() const { std::cout << "Base::identify()\n"; }
};

class Derived: public Base
{
public:
    Derived() { }
};

int main()
{
    Base base {};
    base.identify();

    Derived derived {};
    derived.identify();

    return 0;
}
```

When base.identify() is called, the compiler looks to see if a function named identify() has been defined in class Base. It has, so the compiler looks to see if it is a match. It is, so it is called

When derived.identify() is called, the compiler looks to see if a function named identify() has been defined in the Derived class. It hasn’t. So it moves to the parent class (in this case, Base), and tries again there. Base has defined an identify() function, so it uses that one. In other words, Base::identify() was used because Derived::identify() doesn’t exist.

This means that if the behavior provided by a base class is sufficient, we can simply use the base class behavior.

However, if we had defined Derived::identify() in the Derived class, it would have been used instead.

Sometimes we don’t want to completely replace a base class function, but instead want to add additional functionality to it when called with a derived object.

To have a derived function call a base function of the same name, simply do a normal function call, but prefix the function with the scope qualifier of the base class. For example:
```c++
#include <iostream>

class Base
{
public:
    Base() { }

    void identify() const { std::cout << "Base::identify()\n"; }
};

class Derived: public Base
{
public:
    Derived() { }

    void identify() const
    {
        std::cout << "Derived::identify()\n";
        Base::identify(); // note call to Base::identify() here
    }
};

int main()
{
    Base base {};
    base.identify();

    Derived derived {};
    derived.identify();

    return 0;
}
```


## 24.8 Hiding inherited functionality

C++ gives us the ability to change an inherited member’s access specifier in the derived class. This is done by using a using declaration to identify the (scoped) base class member that is having its access changed in the derived class, under the new access specifier.

For example, consider the following Base:

```c++
#include <iostream>

class Base
{
private:
    int m_value {};

public:
    Base(int value)
        : m_value { value }
    {
    }

protected:
    void printValue() const { std::cout << m_value; }
};
```

Because Base::printValue() has been declared as protected, it can only be called by Base or its derived classes. The public can not access it.

Let’s define a Derived class that changes the access specifier of printValue() to public:

```c++
class Derived: public Base
{
public:
    Derived(int value)
        : Base { value }
    {
    }

    // Base::printValue was inherited as protected, so the public has no access
    // But we're changing it to public via a using declaration
    using Base::printValue; // note: no parenthesis here
};
This means that this code will now work:

int main()
{
    Derived derived { 7 };

    // printValue is public in Derived, so this is okay
    derived.printValue(); // prints 7
    return 0;
}
```

You can only change the access specifiers of base members the derived class would normally be able to access. Therefore, you can never change the access specifier of a base member from private to protected or public, because derived classes do not have access to private members of the base class.

In C++, it is not possible to remove or restrict functionality from a base class other than by modifying the source code. However, in a derived class, it is possible to hide functionality that exists in the base class, so that it can not be accessed through the derived class. This can be done simply by changing the relevant access specifier.

You can also mark member functions as deleted in the derived class, which ensures they can’t be called at all through a derived object. 


## 24.9 Multiple inheritance 

Multiple inheritance enables a derived class to inherit members from more than one parent.

Let’s say we wanted to write a program to keep track of a bunch of teachers. A teacher is a person. However, a teacher is also an employee (they are their own employer if working for themselves). Multiple inheritance can be used to create a Teacher class that inherits properties from both Person and Employee. To use multiple inheritance, simply specify each base class (just like in single inheritance), separated by a comma.

```c++
#include <string>
#include <string_view>

class Person
{
private:
    std::string m_name{};
    int m_age{};

public:
    Person(std::string_view name, int age)
        : m_name{ name }, m_age{ age }
    {
    }

    const std::string& getName() const { return m_name; }
    int getAge() const { return m_age; }
};

class Employee
{
private:
    std::string m_employer{};
    double m_wage{};

public:
    Employee(std::string_view employer, double wage)
        : m_employer{ employer }, m_wage{ wage }
    {
    }

    const std::string& getEmployer() const { return m_employer; }
    double getWage() const { return m_wage; }
};

// Teacher publicly inherits Person and Employee
class Teacher : public Person, public Employee
{
private:
    int m_teachesGrade{};

public:
    Teacher(std::string_view name, int age, std::string_view employer, double wage, int teachesGrade)
        : Person{ name, age }, Employee{ employer, wage }, m_teachesGrade{ teachesGrade }
    {
    }
};

int main()
{
    Teacher t{ "Mary", 45, "Boo", 14.3, 8 };

    return 0;
}

```

A mixin (also spelled “mix-in”) is a small class that can be inherited from in order to add properties to a class. The name mixin indicates that the class is intended to be mixed into other classes, not instantiated on its own.

While multiple inheritance seems like a simple extension of single inheritance, multiple inheritance introduces a lot of issues that can markedly increase the complexity of programs and make them a maintenance nightmare. First, ambiguity can result when multiple base classes contain a function with the same name. 

However, there is a way to work around this problem: you can explicitly specify which version you meant to call:

```c++
int main()
{
    WirelessAdapter c54G { 5442, 181742 };
    std::cout << c54G.USBDevice::getID();

    return 0;
}
```

Second, and more serious is the diamond problem. This occurs when a class multiply inherits from two classes which each inherit from a single base class. This leads to a diamond shaped inheritance pattern. For example, consider the following set of classes:

```c++
class PoweredDevice
{
};

class Scanner: public PoweredDevice
{
};

class Printer: public PoweredDevice
{
};

class Copier: public Scanner, public Printer
{
};
```

Scanners and printers are both powered devices, so they derived from PoweredDevice. However, a copy machine incorporates the functionality of both Scanners and Printers.

There are many issues that arise in this context, including whether Copier should have one or two copies of PoweredDevice, and how to resolve certain types of ambiguous references. 

Avoid multiple inheritance unless alternatives lead to more complexity.

Construction happens in order from most-Parent to most-Child. Destruction happens in the opposite order.
Base()
Derived()
~Derived()
~Base()