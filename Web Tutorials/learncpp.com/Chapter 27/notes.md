## 27.2 Basic exception handling

In C++, a throw statement is used to signal that an exception or error case has occurred (think of throwing a penalty flag). Signaling that an exception has occurred is also commonly called raising an exception.

Here are some examples:
```c++
throw -1; // throw a literal integer value
throw ENUM_INVALID_INDEX; // throw an enum value
throw "Can not take square root of negative number"; // throw a literal C-style (const char*) string
throw dX; // throw a double variable that was previously defined
throw MyException("Fatal Error"); // Throw an object of class MyException
```

In C++, we use the try keyword to define a block of statements (called a try block). The try block acts as an observer, looking for any exceptions that are thrown by any of the statements within the try block.

Here’s an example of a try block:
```c++
try
{
    // Statements that may throw exceptions you want to handle go here
    throw -1; // here's a trivial throw statement
}
```

Actually handling exceptions is the job of the catch block(s). The catch keyword is used to define a block of code (called a catch block) that handles exceptions for a single data type.

Here’s an example of a catch block that will catch integer exceptions:
```c++
catch (int x)
{
    // Handle an exception of type int here
    std::cerr << "We caught an int exception with value" << x << '\n';
}
```

Try blocks and catch blocks work together -- a try block detects any exceptions that are thrown by statements within the try block, and routes them to a catch block with a matching type for handling. A try block must have at least one catch block immediately following it, but may have multiple catch blocks listed in sequence.

Here’s a full program that uses throw, try, and multiple catch blocks:
```c++
#include <iostream>
#include <string>

int main()
{
    try
    {
        // Statements that may throw exceptions you want to handle go here
        throw -1; // here's a trivial example
    }
    catch (double) // no variable name since we don't use the exception itself in the catch block below
    {
        // Any exceptions of type double thrown within the above try block get sent here
        std::cerr << "We caught an exception of type double\n";
    }
    catch (int x)
    {
        // Any exceptions of type int thrown within the above try block get sent here
        std::cerr << "We caught an int exception with value: " << x << '\n';
    }
    catch (const std::string&) // catch classes by const reference
    {
        // Any exceptions of type std::string thrown within the above try block get sent here
        std::cerr << "We caught an exception of type std::string\n";
    }

    // Execution continues here after the exception has been handled by any of the above catch blocks
    std::cout << "Continuing on our merry way\n";

    return 0;
}
```

When an exception is raised (using throw), the running program finds the nearest enclosing try block (propagating up the stack if necessary to find an enclosing try block) to see if any of the catch handlers attached to the try block can handle that type of exception. If so, execution jumps to the top of the catch block, the exception is considered handled.

If no appropriate catch handlers exist in the nearest enclosing try block, the program continues to look at subsequent enclosing try blocks for a catch handler. If no appropriate catch handlers can be found before the end of the program, the program will fail with a runtime exception error.

If an exception is routed to a catch block, it is considered “handled” even if the catch block is empty. However, typically you’ll want your catch blocks to do something useful. There are four common things that catch blocks do when they catch an exception:

First, catch blocks may print an error (either to the console, or a log file) and then allow the function to proceed.

Second, catch blocks may return a value or error code back to the caller.

Third, a catch block may throw another exception. Because the catch block is outside of the try block, the newly thrown exception in this case is not handled by the preceding try block -- it’s handled by the next enclosing try block.

Fourth, a catch block in main() may be used to catch fatal errors and terminate the program in a clean way.

To find an exception-handler, the stack may unwind in reverse order of calling to the very first try-catch. Along the way, objects will be destroyed.


## 27.4 Uncaught exceptions and catch-all handlers

The call stack may or may not be unwound if an exception is unhandled.

If the stack is not unwound, local variables will not be destroyed, which may cause problems if those variables have non-trivial destructors.

Fortunately, C++ also provides us with a mechanism to catch all types of exceptions. This is known as a catch-all handler. A catch-all handler works just like a normal catch block, except that instead of using a specific type to catch, it uses the ellipses operator (…) as the type to catch. For this reason, the catch-all handler is also sometimes called an “ellipsis catch handler”

```c++
#include <iostream>

int main()
{
	try
	{
		throw 5; // throw an int exception
	}
	catch (double x)
	{
		std::cout << "We caught an exception of type double: " << x << '\n';
	}
	catch (...) // catch-all handler
	{
		std::cout << "We caught an exception of an undetermined type\n";
	}
}
```

This will catch any unanticipated exceptions, ensuring that stack unwinding occurs up to this point and preventing the program from terminating, but does no specific error handling.

One use for the catch-all handler is to wrap the contents of main():
```c++
#include <iostream>

struct GameSession
{
    // Game session data here
};

void runGame(GameSession&)
{
    throw 1;
}

void saveGame(GameSession&)
{
    // Save user's game here
}

int main()
{
    GameSession session{};

    try
    {
        runGame(session);
    }
    catch(...)
    {
        std::cerr << "Abnormal termination\n";
    }

    saveGame(session); // save the user's game (even if catch-all handler was hit)

    return 0;
}
```

Exceptions of a fundamental type can be caught by value since they are cheap to copy.

Exceptions of a class type should be caught by (const) reference to prevent expensive copying and slicing.

Many of the classes and operators in the standard library throw exception classes on failure. For example, operator new can throw std::bad_alloc if it is unable to allocate enough memory. A failed dynamic_cast will throw std::bad_cast. And so on. As of C++20, there are 28 different exception classes that can be thrown, with more being added in each subsequent language standard.

The good news is that all of these exception classes are derived from a single class called std::exception (defined in the <exception> header). std::exception is a small interface class designed to serve as a base class to any exception thrown by the C++ standard library.

Much of the time, when an exception is thrown by the standard library, we won’t care whether it’s a bad allocation, a bad cast, or something else. We just care that something catastrophic went wrong and now our program is exploding. Thanks to std::exception, we can set up an exception handler to catch exceptions of type std::exception, and we’ll end up catching std::exception and all of the derived exceptions together in one place. Easy!
```c++
#include <cstddef> // for std::size_t
#include <exception> // for std::exception
#include <iostream>
#include <limits>
#include <string> // for this example

int main()
{
    try
    {
        // Your code using standard library goes here
        // We'll trigger one of these exceptions intentionally for the sake of the example
        std::string s;
        s.resize(std::numeric_limits<std::size_t>::max()); // will trigger a std::length_error or allocation exception
    }
    // This handler will catch std::exception and all the derived exceptions too
    catch (const std::exception& exception)
    {
        std::cerr << "Standard exception: " << exception.what() << '\n';
    }

    return 0;
}
```

Exception objects need to be copyable.


## 27.6 Rethrowing exceptions

C++ provides a way to rethrow the exact same exception as the one that was just caught. To do so, simply use the throw keyword from within the catch block (with no associated variable), like so:
```c++
#include <iostream>
class Base
{
public:
    Base() {}
    virtual void print() { std::cout << "Base"; }
};

class Derived: public Base
{
public:
    Derived() {}
    void print() override { std::cout << "Derived"; }
};

int main()
{
    try
    {
        try
        {
            throw Derived{};
        }
        catch (Base& b)
        {
            std::cout << "Caught Base b, which is actually a ";
            b.print();
            std::cout << '\n';
            throw; // note: We're now rethrowing the object here
        }
    }
    catch (Base& b)
    {
        std::cout << "Caught Base b, which is actually a ";
        b.print();
        std::cout << '\n';
    }

    return 0;
}
```


## 27.7 Function try blocks

Function try blocks are designed to allow you to establish an exception handler around the body of an entire function, rather than around a block of code.

The syntax for function try blocks is a little hard to describe, so we’ll show by example:

```c++
#include <iostream>

class A
{
private:
	int m_x;
public:
	A(int x) : m_x{x}
	{
		if (x <= 0)
			throw 1; // Exception thrown here
	}
};

class B : public A
{
public:
	B(int x) try : A{x} // note addition of try keyword here
	{
	}
	catch (...) // note this is at same level of indentation as the function itself
	{
                // Exceptions from member initializer list or
                // from constructor body are caught here

                std::cerr << "Exception caught\n";

                throw; // rethrow the existing exception
	}
};

int main()
{
	try
	{
		B b{0};
	}
	catch (int)
	{
		std::cout << "Oops\n";
	}
}
```

Use function try blocks when you need a constructor to handle an exception thrown in the member initializer list.

Function try blocks can catch both base and the current class exceptions. 


## 27.9 Exception specifications and noexcept

In C++, all functions are classified as either non-throwing or potentially throwing. A non-throwing function is one that promises not to throw exceptions that are visible to the caller. A potentially throwing function may throw exceptions that are visible to the caller.

To define a function as non-throwing, we can use the noexcept specifier. To do so, we use the noexcept keyword in the function declaration, placed to the right of the function parameter list:

```c++
void doSomething() noexcept; // this function is specified as non-throwing
```

The promise that a noexcept function makes to not throw exceptions that are visible to the caller is a contractual promise, not a promise enforced by the compiler. So while calling a noexcept function should be safe, any exception handling bugs in the noexcept function that cause the contract to be broken will result in termination of the program! This shouldn’t happen, but neither should bugs.

The following program illustrates the behavior of noexcept functions and exceptions in various cases:

```c++
// h/t to reader yellowEmu for the first draft of this program
#include <iostream>

class Doomed
{
public:
    ~Doomed()
    {
        std::cout << "Doomed destructed\n";
    }
};

void thrower()
{
    std::cout << "Throwing exception\n";
    throw 1;
}

void pt()
{
    std::cout << "pt (potentally throwing) called\n";
    //This object will be destroyed during stack unwinding (if it occurs)
    Doomed doomed{};
    thrower();
    std::cout << "This never prints\n";
}

void nt() noexcept
{
    std::cout << "nt (noexcept) called\n";
    //This object will be destroyed during stack unwinding (if it occurs)
    Doomed doomed{};
    thrower();
    std::cout << "this never prints\n";
}

void tester(int c) noexcept
{
    std::cout << "tester (noexcept) case " << c << " called\n";
    try
    {
        (c == 1) ? pt() : nt();
    }
    catch (...)
    {
        std::cout << "tester caught exception\n";
    }
}

int main()
{
    std::cout << std::unitbuf; // flush buffer after each insertion
    std::cout << std::boolalpha; // print boolean as true/false
    tester(1);
    std::cout << "Test successful\n\n";
    tester(2);
    std::cout << "Test successful\n";

    return 0;
}
```

For this reason, it’s best that noexcept functions don’t mess with exceptions at all, or call potentially throwing functions that could raise an exception. A noexcept function can’t have an exception handling bug if no exceptions can possibly be raised in the first place!

 What does noexcept do, and what happens if a noexcept function actually throws an exception? (Answer: It calls std::terminate()).

 std::terminate() does not perform automatic resource cleanup or stack unwinding. 

 The noexcept operator can also be used inside expressions. It takes an expression as an argument, and returns true or false if the compiler thinks it will throw an exception or not. The noexcept operator is checked statically at compile-time, and doesn’t actually evaluate the input expression.

```c++
void foo() {throw -1;}
void boo() {};
void goo() noexcept {};
struct S{};

constexpr bool b1{ noexcept(5 + 3) }; // true; ints are non-throwing
constexpr bool b2{ noexcept(foo()) }; // false; foo() throws an exception
constexpr bool b3{ noexcept(boo()) }; // false; boo() is implicitly noexcept(false)
constexpr bool b4{ noexcept(goo()) }; // true; goo() is explicitly noexcept(true)
constexpr bool b5{ noexcept(S{}) };   // true; a struct's default constructor is noexcept by default
```

The noexcept specifier has an optional Boolean parameter. noexcept(true) is equivalent to noexcept, meaning the function is non-throwing. noexcept(false) means the function is potentially throwing. These parameters are typically only used in template functions, so that a template function can be dynamically created as non-throwing or potentially throwing based on some parameterized value.

The noexcept operator can be used to conditionally execute code depending on whether it is potentially throwing or not. This is required to fulfill certain exception safety guarantees, which we’ll talk about in the next section.

An exception safety guarantee is a contractual guideline about how functions or classes will behave in the event an exception occurs. There are four levels of exception safety guarantees:
No guarantee -- There are no guarantees about what will happen if an exception is thrown (e.g. a class may be left in an unusable state)
Basic guarantee -- If an exception is thrown, no memory will be leaked and the object is still usable, but the program may be left in a modified state.
Strong guarantee -- If an exception is thrown, no memory will be leaked and the program state will not be changed. This means the function must either completely succeed or have no side effects if it fails. This is easy if the failure happens before anything is modified in the first place, but can also be achieved by rolling back any changes so the program is returned to the pre-failure state.
No throw / No fail guarantee -- The function will always succeed (no-fail) or fail without throwing an exception that is exposed to the caller (no-throw). Exceptions may be thrown internally if not exposed. The noexcept specifier maps to this level of exception safety guarantee.

Always make move constructors, move assignment, and swap functions noexcept.
Make copy constructors and copy assignment operators noexcept when you can.
Use noexcept on other functions to express a no-fail or no-throw guarantee.

The noexcept exception specifier can be used to denote that a function is no-throw/no-fail.

You should never throw an exception from a destructor.


## 27.10 std::move_if_noexcept

std::move_if_noexcept will return a movable r-value if the object has a noexcept move constructor, otherwise it will return a copyable l-value. We can use the noexcept specifier in conjunction with std::move_if_noexcept to use move semantics only when a strong exception guarantee exists (and use copy semantics otherwise).

If a type has both potentially throwing move semantics and deleted copy semantics (the copy constructor and copy assignment operator are unavailable), then std::move_if_noexcept will waive the strong guarantee and invoke move semantics. This conditional waiving of the strong guarantee is ubiquitous in the standard library container classes, since they use std::move_if_noexcept often.