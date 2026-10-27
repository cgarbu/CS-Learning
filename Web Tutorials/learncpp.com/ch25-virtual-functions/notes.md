## 25.2 Pointers and references to the base class of derived objects

A virtual function is a special type of member function that, when called, resolves to the most-derived version of the function for the actual type of the object being referenced or pointed to. A derived function is considered a match if it has the same signature (name, parameter types, and whether it is const) and return type as the base version of the function. Such functions are called overrides.

To make a function virtual, simply place the “virtual” keyword before the function declaration.

Let’s take a look at a slightly more complex example:
```c++
#include <iostream>
#include <string_view>

class A
{
public:
    virtual std::string_view getName() const { return "A"; }
};

class B: public A
{
public:
    virtual std::string_view getName() const { return "B"; }
};

class C: public B
{
public:
    virtual std::string_view getName() const { return "C"; }
};

class D: public C
{
public:
    virtual std::string_view getName() const { return "D"; }
};

int main()
{
    C c {};
    A& rBase{ c };
    std::cout << "rBase is a " << rBase.getName() << '\n';

    return 0;
}
```

Let’s look at how this works. First, we instantiate a C class object. rBase is an A reference, which we set to reference the A portion of the C object. Finally, we call rBase.getName(). rBase.getName() evaluates to A::getName(). However, A::getName() is virtual, so the compiler will call the most-derived match between A and C. In this case, that is C::getName(). Note that it will not call D::getName(), because our original object was a C, not a D, so only functions between A and C are considered.

So the output matches "C". 

Virtual function resolution only works when a member function is called through a pointer or reference to a class type object.

In programming, polymorphism refers to the ability of an entity to have multiple forms (the term “polymorphism” literally means “many forms”). For example, consider the following two function declaration
```c++
int add(int, int);
double add(double, double);
```

Compile-time polymorphism refers to forms of polymorphism that are resolved by the compiler. These include function overload resolution, as well as template resolution.

Runtime polymorphism refers to forms of polymorphism that are resolved at runtime. This includes virtual function resolution.

If a function is virtual, all matching overrides in derived classes are implicitly virtual.

Under normal circumstances, the return type of a virtual function and its override must match.

Never call virtual functions from constructors or destructors.


## 25.3 The override and final specifiers, and covariant return types

As we mentioned in the previous lesson, a derived class virtual function is only considered an override if its signature and return types match exactly. That can lead to inadvertent issues, where a function that was intended to be an override actually isn’t.

To help address the issue of functions that are meant to be overrides but aren’t, the override specifier can be applied to any virtual function to tell the compiler to enforce that the function is an override. The override specifier is placed at the end of a member function declaration (in the same place where a function-level const goes). If a member function is const and an override, the const must come before override.

If a function marked as override does not override a base class function (or is applied to a non-virtual function), the compiler will flag the function as an error.
```c++
#include <string_view>

class A
{
public:
	virtual std::string_view getName1(int x) { return "A"; }
	virtual std::string_view getName2(int x) { return "A"; }
	virtual std::string_view getName3(int x) { return "A"; }
};

class B : public A
{
public:
	std::string_view getName1(short int x) override { return "B"; } // compile error, function is not an override
	std::string_view getName2(int x) const override { return "B"; } // compile error, function is not an override
	std::string_view getName3(int x) override { return "B"; } // okay, function is an override of A::getName3(int)

};

int main()
{
	return 0;
}
```

Use the override specifier (but not the virtual keyword) on override functions in derived classes. This includes virtual destructors.

Use the virtual keyword on virtual functions in a base class.

There may be cases where you don’t want someone to be able to override a virtual function, or inherit from a class. The final specifier can be used to tell the compiler to enforce this. If the user tries to override a function or inherit from a class that has been specified as final, the compiler will give a compile error.

In the case where we want to restrict the user from overriding a function, the final specifier is used in the same place the override specifier is, like so:
```c++
#include <string_view>

class A
{
public:
	virtual std::string_view getName() const { return "A"; }
};

class B : public A
{
public:
	// note use of final specifier on following line -- that makes this function not able to be overridden in derived classes
	std::string_view getName() const override final { return "B"; } // okay, overrides A::getName()
};

class C : public B
{
public:
	std::string_view getName() const override { return "C"; } // compile error: overrides B::getName(), which is final
};
```

There is one special case in which a derived class virtual function override can have a different return type than the base class and still be considered a matching override. If the return type of a virtual function is a pointer or a reference to some class, override functions can return a pointer or a reference to a derived class. These are called covariant return types. Here is an example:
```c++
#include <iostream>
#include <string_view>

class Base
{
public:
	// This version of getThis() returns a pointer to a Base class
	virtual Base* getThis() { std::cout << "called Base::getThis()\n"; return this; }
	void printType() { std::cout << "returned a Base\n"; }
};

class Derived : public Base
{
public:
	// Normally override functions have to return objects of the same type as the base function
	// However, because Derived is derived from Base, it's okay to return Derived* instead of Base*
	Derived* getThis() override { std::cout << "called Derived::getThis()\n";  return this; }
	void printType() { std::cout << "returned a Derived\n"; }
};

int main()
{
	Derived d{};
	Base* b{ &d };
	d.getThis()->printType(); // calls Derived::getThis(), returns a Derived*, calls Derived::printType
	b->getThis()->printType(); // calls Derived::getThis(), returns a Base*, calls Base::printType

	return 0;
}
```

In C++, marking a member function with the final specifier prevents any further derived classes from overriding that function. 

## 25.4 Virtual destructors, virtual assignment, and overriding virtualization

Whenever you are dealing with inheritance, you should make any explicit destructors virtual.

If you intend your class to be inherited from, make sure your destructor is virtual and public.

If you do not intend your class to be inherited from, mark your class as final. This will prevent other classes from inheriting from it in the first place, without imposing any other use restrictions on the class itself.


## 25.5 Early binding and late binding

In general programming, binding is the process of associating names with such properties. Function binding (or method binding) is the process that determines what function definition is associated with a function call. The process of actually invoking a bound function is called dispatching.

In C++, when a direct call is made to a non-member function or a non-virtual member function, the compiler can determine which function definition should be matched to the call. This is sometimes called early binding (or static binding), as it can be performed at compile-time. The compiler (or linker) can then generate machine language instructions that tells the CPU to jump directly to the address of the function.

Calls to overloaded functions and function templates can also be resolved at compile-time. 

In some cases, a function call can’t be resolved until runtime. In C++, this is sometimes known as late binding (or in the case of virtual function resolution, dynamic dispatch). In C++, one way to get late binding is to use function pointers.

To review function pointers briefly, a function pointer is a type of pointer that points to a function instead of a variable. The function that a function pointer points to can be called by using the function call operator () on the pointer.

For example, the following code calls the printValue() function through a function pointer:
```c++
#include <iostream>

void printValue(int value)
{
    std::cout << value << '\n';
}

int main()
{
    auto fcn { printValue }; // create a function pointer and make it point to function printValue
    fcn(5);                  // invoke printValue indirectly through the function pointer

    return 0;
}
```

Calling a function via a function pointer is also known as an indirect function call. At the point where fcn(5) is actually called, the compiler does not know at compile-time what function is being called. Instead, at runtime, an indirect function call is made to whatever function exists at the address held by the function pointer.


## 25.6 The virtual table

The C++ standard does not specify how virtual functions should be implemented (this detail is left up to the implementation).

The virtual table is a lookup table of functions used to resolve function calls in a dynamic/late binding manner. The virtual table sometimes goes by other names, such as “vtable”, “virtual function table”, “virtual method table”, or “dispatch table”. In C++, virtual function resolution is sometimes called dynamic dispatch.
* Early binding/static dispatch = direct function call overload resolution
* Late binding = indirect function call resolution
* Dynamic dispatch = virtual function override resolution

The virtual table is actually quite simple, though it’s a little complex to describe in words. First, every class that uses virtual functions (or is derived from a class that uses virtual functions) has a corresponding virtual table. This table is simply a static array that the compiler sets up at compile time. A virtual table contains one entry for each virtual function that can be called by objects of the class. Each entry in this table is simply a function pointer that points to the most-derived function accessible by that class.

Second, the compiler also adds a hidden pointer that is a member of the base class, which we will call *__vptr. *__vptr is set (automatically) when a class object is created so that it points to the virtual table for that class. Unlike the this pointer, which is actually a function parameter used by the compiler to resolve self-references, *__vptr is a real pointer member. Consequently, it makes each class object allocated bigger by the size of one pointer. It also means that *__vptr is inherited by derived classes, which is important.


## 25.7 Pure virtual functions, abstract base classes, and interface classes

So far, all of the virtual functions we have written have a body (a definition). However, C++ allows you to create a special kind of virtual function called a pure virtual function (or abstract function) that has no body at all! A pure virtual function simply acts as a placeholder that is meant to be redefined by derived classes.

To create a pure virtual function, rather than define a body for the function, we simply assign the function the value 0.
```c++
#include <string_view>

class Base
{
public:
    std::string_view sayHi() const { return "Hi"; } // a normal non-virtual function

    virtual std::string_view getName() const { return "Base"; } // a normal virtual function

    virtual int getValue() const = 0; // a pure virtual function

    int doSomething() = 0; // Compile error: can not set non-virtual functions to 0
};
```

When we add a pure virtual function to our class, we are effectively saying, “it is up to the derived classes to implement this function”.

Using a pure virtual function has two main consequences: First, any class with one or more pure virtual functions becomes an abstract base class, which means that it can not be instantiated! Consider what would happen if we could create an instance of Base:

Any class with pure virtual functions should also have a virtual destructor.

It turns out that we can create pure virtual functions that have definitions.

An interface class is a class that has no member variables, and where all of the functions are pure virtual! Interfaces are useful when you want to define the functionality that derived classes must implement, but leave the details of how the derived class implements that functionality entirely up to the derived class.

Interface classes are often named beginning with an I. Here’s a sample interface class:
```c++
#include <string_view>

class IErrorLog
{
public:
    virtual bool openLog(std::string_view filename) = 0;
    virtual bool closeLog() = 0;

    virtual bool writeError(std::string_view errorMessage) = 0;

    virtual ~IErrorLog() {} // make a virtual destructor in case we delete an IErrorLog pointer, so the proper derived destructor is called
};
```

A pure virtual function forces derived classes to provide their own implementation while making the base class abstract.

The virtual table entry for a class with a pure virtual function will generally either contain a null pointer, or point to a generic function that prints an error (sometimes this function is named __purecall).


## 25.8 Virtual base classes

To share a base class, simply insert the “virtual” keyword in the inheritance list of the derived class. This creates what is called a virtual base class, which means there is only one base object. The base object is shared between all objects in the inheritance tree and it is only constructed once. Here is an example (without constructors for simplicity) showing how to use the virtual keyword to create a shared base class:
```c++
class PoweredDevice
{
};

class Scanner: virtual public PoweredDevice
{
};

class Printer: virtual public PoweredDevice
{
};

class Copier: public Scanner, public Printer
{
};
```

Now, when you create a Copier class object, you will get only one copy of PoweredDevice per Copier that will be shared by both Scanner and Printer.

However, this leads to one more problem: if Scanner and Printer share a PoweredDevice base class, who is responsible for creating it? The answer, as it turns out, is Copier. The Copier constructor is responsible for creating PoweredDevice. Consequently, this is one time when Copier is allowed to call a non-immediate-parent constructor directly:
```c++
#include <iostream>

class PoweredDevice
{
public:
    PoweredDevice(int power)
    {
		std::cout << "PoweredDevice: " << power << '\n';
    }
};

class Scanner: virtual public PoweredDevice // note: PoweredDevice is now a virtual base class
{
public:
    Scanner(int scanner, int power)
        : PoweredDevice{ power } // this line is required to create Scanner objects, but ignored in this case
    {
		std::cout << "Scanner: " << scanner << '\n';
    }
};

class Printer: virtual public PoweredDevice // note: PoweredDevice is now a virtual base class
{
public:
    Printer(int printer, int power)
        : PoweredDevice{ power } // this line is required to create Printer objects, but ignored in this case
    {
		std::cout << "Printer: " << printer << '\n';
    }
};

class Copier: public Scanner, public Printer
{
public:
    Copier(int scanner, int printer, int power)
        : PoweredDevice{ power }, // PoweredDevice is constructed here
        Scanner{ scanner, power }, Printer{ printer, power }
    {
    }
};
```


## 25.9 Object slicing

The assigning of a Derived class object to a Base class object is called object slicing (or slicing for short).

If the Base class is not designed to be instantiated by itself (e.g. it is just an interface class), slicing can be avoided by making the Base class non-copyable (by deleting the Base copy constructor and Base assignment operator). 

Although C++ supports assigning derived objects to base objects via object slicing, in general, this is likely to cause nothing but headaches, and you should generally try to avoid slicing. Make sure your function parameters are references (or pointers) and try to avoid any kind of pass-by-value when it comes to derived classes.


## 25.10 Dynamic casting

C++ provides a casting operator named dynamic_cast. Although dynamic casts have a few different capabilities, by far the most common use for dynamic casting is for converting base-class pointers into derived-class pointers. This process is called downcasting.

Using dynamic_cast works just like static_cast. Here’s our example main() from above, using a dynamic_cast to convert our Base pointer back into a Derived pointer:
```c++
int main()
{
	Base* b{ getObject(true) };

	Derived* d{ dynamic_cast<Derived*>(b) }; // use dynamic cast to convert Base pointer into Derived pointer

	std::cout << "The name of the Derived is: " << d->getName() << '\n';

	delete b;

	return 0;
}
```

This prints:
$$
The name of the Derived is: Apple
$$

The above example works because b is actually pointing to a Derived object, so converting b into a Derived pointer is successful.

However, we’ve made quite a dangerous assumption: that b is pointing to a Derived object. What if b wasn’t pointing to a Derived object? This is easily tested by changing the argument to getObject() from true to false. In that case, getObject() will return a Base pointer to a Base object. When we try to dynamic_cast that to a Derived, it will fail, because the conversion can’t be made. If a dynamic_cast fails, the result of the conversion will be a null pointer.

Because we haven’t checked for a null pointer result, we access d->getName(), which will try to dereference a null pointer, leading to undefined behavior (probably a crash).

In order to make this program safe, we need to ensure the result of the dynamic_cast actually succeeded:
```c++
int main()
{
	Base* b{ getObject(true) };

	Derived* d{ dynamic_cast<Derived*>(b) }; // use dynamic cast to convert Base pointer into Derived pointer

	if (d) // make sure d is non-null
		std::cout << "The name of the Derived is: " << d->getName() << '\n';

	delete b;

	return 0;
}
```

Always ensure your dynamic casts actually succeeded by checking for a null pointer result.

Also note that there are several cases where downcasting using dynamic_cast will not work:
1. With protected or private inheritance.
2. For classes that do not declare or inherit any virtual functions (and thus don’t have a virtual table).
3. In certain cases involving virtual base classes (see this page for an example of some of these cases, and how to resolve them).

It turns out that downcasting can also be done with static_cast. The main difference is that static_cast does no runtime type checking to ensure that what you’re doing makes sense. This makes using static_cast faster, but more dangerous. If you cast a Base* to a Derived*, it will “succeed” even if the Base pointer isn’t pointing to a Derived object. This will result in undefined behavior when you try to access the resulting Derived pointer (that is actually pointing to a Base object).

Although all of the above examples show dynamic casting of pointers (which is more common), dynamic_cast can also be used with references. This works analogously to how dynamic_cast works with pointers.
```c++
#include <iostream>
#include <string>
#include <string_view>

class Base
{
protected:
	int m_value;

public:
	Base(int value)
		: m_value{value}
	{
	}

	virtual ~Base() = default;
};

class Derived : public Base
{
protected:
	std::string m_name;

public:
	Derived(int value, std::string_view name)
		: Base{value}, m_name{name}
	{
	}

	const std::string& getName() const { return m_name; }
};

int main()
{
	Derived apple{1, "Apple"}; // create an apple
	Base& b{ apple }; // set base reference to object
	Derived& d{ dynamic_cast<Derived&>(b) }; // dynamic cast using a reference instead of a pointer

	std::cout << "The name of the Derived is: " << d.getName() << '\n'; // we can access Derived::getName through d

	return 0;
}
```

Use static_cast unless you’re downcasting, in which case dynamic_cast is usually a better choice. However, you should also consider avoiding casting altogether and just use virtual functions.

Run-time type information (RTTI) is a feature of C++ that exposes information about an object’s data type at runtime. This capability is leveraged by dynamic_cast. Because RTTI has a pretty significant space performance cost, some compilers allow you to turn RTTI off as an optimization. Needless to say, if you do this, dynamic_cast won’t function correctly.


## 25.11 Printing inherited classes using operator<<

```c++
#include <iostream>

class Base
{
public:
	// Here's our overloaded operator<<
	friend std::ostream& operator<<(std::ostream& out, const Base& b)
	{
		// Delegate printing responsibility for printing to virtual member function print()
		return b.print(out);
	}

	// We'll rely on member function print() to do the actual printing
	// Because print() is a normal member function, it can be virtualized
	virtual std::ostream& print(std::ostream& out) const
	{
		out << "Base";
		return out;
	}
};

// Some class or struct with an overloaded operator<<
struct Employee
{
	std::string name{};
	int id{};

	friend std::ostream& operator<<(std::ostream& out, const Employee& e)
	{
		out << "Employee(" << e.name << ", " << e.id << ")";
		return out;
	}
};

class Derived : public Base
{
private:
	Employee m_e{}; // Derived now has an Employee member

public:
	Derived(const Employee& e)
		: m_e{ e }
	{
	}

	// Here's our override print() function to handle the Derived case
	std::ostream& print(std::ostream& out) const override
	{
		out << "Derived: ";

		// Print the Employee member using the stream object
		out << m_e;

		return out;
	}
};

int main()
{
	Base b{};
	std::cout << b << '\n';

	Derived d{ Employee{"Jim", 4}};
	std::cout << d << '\n'; // note that this works even with no operator<< that explicitly handles Derived objects

	Base& bref{ d };
	std::cout << bref << '\n';

	return 0;
}
```


## Summary

C++ allows you to set base class pointers and references to a derived object. This is useful when we want to write a function or array that can work with any type of object derived from a base class.

Without virtual functions, base class pointers and references to a derived class will only have access to base class member variables and versions of functions.

A virtual function is a special type of function that resolves to the most-derived version of the function (called an override) that exists between the base and derived class. To be considered an override, the derived class function must have the same signature and return type as the virtual base class function. The one exception is for covariant return types, which allow an override to return a pointer or reference to a derived class if the base class function returns a pointer or reference to the base class.

A function that is intended to be an override should use the override specifier to ensure that it is actually an override.

The final specifier can be used to prevent overrides of a function or inheritance from a class.

If you intend to use inheritance, you should make your destructor virtual, so the proper destructor is called if a pointer to the base class is deleted.

You can ignore virtual resolution by using the scope resolution operator to directly specify which class’s version of the function you want: e.g. base.Base::getName().

Early binding occurs when the compiler encounters a direct function call. The compiler or linker can resolve these function calls directly. Late binding occurs when a function pointer is called. In these cases, which function will be called can not be resolved until runtime. Virtual functions use late binding and a virtual table to determine which version of the function to call.

Using virtual functions has a cost: virtual functions take longer to call, and the necessity of the virtual table increases the size of every object containing a virtual function by one pointer.

A virtual function can be made pure virtual/abstract by adding “= 0” to the end of the virtual function prototype. A class containing a pure virtual function is called an abstract class, and can not be instantiated. A class that inherits pure virtual functions must concretely define them or it will also be considered abstract. Pure virtual functions can have a body, but they are still considered abstract.

An interface class is one with no member variables and all pure virtual functions. These are often named starting with a capital I.

A virtual base class is a base class that is only included once, no matter how many times it is inherited by an object.

When a derived class is assigned to a base class object, the base class only receives a copy of the base portion of the derived class. This is called object slicing.

Dynamic casting can be used to convert a pointer to a base class object into a pointer to a derived class object. This is called downcasting. A failed conversion will return a null pointer.

The easiest way to overload operator<< for inherited classes is to write an overloaded operator<< for the most-base class, and then call a virtual member function to do the printing.