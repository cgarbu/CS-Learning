## 20.1 Function Pointers

1. When a function is referred to by name (without parenthesis), C++ converts the function into a function pointer (holding the address of the function). Then operator<< tries to print the function pointer, which it fails at because operator<< does not know how to print function pointers. The standard says that in this case, if the pointer is non-null, then the function pointer should be converted to a bool (which operator<< does know how to print). And if the function pointer is a non-null pointer, it should always evaluate to Boolean true.

2. The syntax for creating a non-const function pointer is one of the ugliest things you will ever see in C++:
```// fcnPtr is a pointer to a function that takes no arguments and returns an integer```
```int (*fcnPtr)();```

To make a const function pointer, the const goes after the asterisk:
```int (*const fcnPtr)();```

If you put the const before the int, then that would indicate the function being pointed to would return a const int.

Function pointers can be initialized with a function (and non-const function pointers can be assigned a function). Like with pointers to variables, we can also use &foo to get a function pointer to foo:
```int (*fcnPtr)(){ &foo }; // fcnPtr points to function foo```
```fcnPtr = &goo; // fcnPtr now points to function goo```

Unlike fundamental types, C++ will implicitly convert a function into a function pointer if needed (so you don’t need to use the address-of operator (&) to get the function’s address). However, function pointers will not convert to void pointers, or vice-versa (though some compilers like Visual Studio may allow this anyway).

Function pointers can also be initialized or assigned the value nullptr.

The other primary thing you can do with a function pointer is use it to actually call the function. There are two ways to do this. The first is via explicit dereference.
```int (*fcnPtr)(int){ &foo }; // Initialize fcnPtr with function foo```
```(*fcnPtr)(5); // call function foo(5) through fcnPtr.```

The second way is via implicit dereference (just don't use the function pointer syntax for the part where you call the function via the function pointer).

3. Default arguments don’t work for functions called through function pointers, because default arguments are resolved at compile-time, while function pointers are resolved at runtime.

4. One of the most useful things to do with function pointers is pass a function as an argument to another function. Functions used as arguments to another function are sometimes called callback functions. Here’s a full example of a selection sort that uses a function pointer parameter to do a user-defined comparison, along with an example of how to call it:

```c++
#include <utility> // for std::swap
#include <iostream>

// Note our user-defined comparison is the third parameter
void selectionSort(int* array, int size, bool (*comparisonFcn)(int, int))
{
    if (!array || !comparisonFcn)
        return;

    // Step through each element of the array
    for (int startIndex{ 0 }; startIndex < (size - 1); ++startIndex)
    {
        // bestIndex is the index of the smallest/largest element we've encountered so far.
        int bestIndex{ startIndex };

        // Look for smallest/largest element remaining in the array (starting at startIndex+1)
        for (int currentIndex{ startIndex + 1 }; currentIndex < size; ++currentIndex)
        {
            // If the current element is smaller/larger than our previously found smallest
            if (comparisonFcn(array[bestIndex], array[currentIndex])) // COMPARISON DONE HERE
            {
                // This is the new smallest/largest number for this iteration
                bestIndex = currentIndex;
            }
        }

        // Swap our start element with our smallest/largest element
        std::swap(array[startIndex], array[bestIndex]);
    }
}

// Here is a comparison function that sorts in ascending order
// (Note: it's exactly the same as the previous ascending() function)
bool ascending(int x, int y)
{
    return x > y; // swap if the first element is greater than the second
}

// Here is a comparison function that sorts in descending order
bool descending(int x, int y)
{
    return x < y; // swap if the second element is greater than the first
}

// This function prints out the values in the array
void printArray(int* array, int size)
{
    if (!array)
        return;

    for (int index{ 0 }; index < size; ++index)
    {
        std::cout << array[index] << ' ';
    }

    std::cout << '\n';
}

int main()
{
    int array[9]{ 3, 7, 9, 5, 6, 1, 8, 2, 4 };

    // Sort the array in descending order using the descending() function
    selectionSort(array, 9, descending);
    printArray(array, 9);

    // Sort the array in ascending order using the ascending() function
    selectionSort(array, 9, ascending);
    printArray(array, 9);

    return 0;
}
```

This program produces the result:
$$
9 8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8 9
$$

You can even set one of these as a default parameter:

```c++
// Default the sort to ascending sort
void selectionSort(int* array, int size, bool (*comparisonFcn)(int, int) = ascending);
```

5. Type aliases can be used to make pointers to functions look more like regular variables:
```c++
using ValidateFunction = bool(*)(int, int);
```

Now instead of doing this:
```c++
bool validate(int x, int y, bool (*fcnPtr)(int, int)); // ugly
```

You can do this:
```c++
bool validate(int x, int y, ValidateFunction pfcn) // clean
```

6. An alternate method of defining and storing function pointers is to use std::function, which is part of the standard library <functional> header. To define a function pointer using this method, declare a std::function object like so:
```c++
#include <functional>
bool validate(int x, int y, std::function<bool(int, int)> fcn); // std::function method that returns a bool and takes two int parameters
```

7. Much like the auto keyword can be used to infer the type of normal variables, the auto keyword can also infer the type of a function pointer.

8. Function pointers are useful primarily when you want to store functions in an array (or other structure), or when you need to pass a function to another function. Because the native syntax to declare function pointers is ugly and error prone, we recommend using std::function. In places where a function pointer type is only used once (e.g. a single parameter or return value), std::function can be used directly. In places where a function pointer type is used multiple times, a type alias to a std::function is a better choice (to prevent repeating yourself).


## 20.2 The stack and the heap

1. The memory that a program uses is typically divided into a few different areas, called segments:
* The code segment (also called a text segment), where the compiled program sits in memory. The code segment is typically read-only.
* The bss segment (also called the uninitialized data segment), where zero-initialized global and static variables are stored.
* The data segment (also called the initialized data segment), where initialized global and static variables are stored.
* The heap, where dynamically allocated variables are allocated from.
* The call stack, where function parameters, local variables, and other function-related information are stored. 

2. The heap segment (also known as the “free store”) keeps track of memory used for dynamic memory allocation. In C++, when you use the new operator to allocate memory, this memory is allocated in the application’s heap segment.

When a dynamically allocated variable is deleted, the memory is “returned” to the heap and can then be reassigned as future allocation requests are received. Remember that deleting a pointer does not delete the variable, it just returns the memory at the associated address back to the operating system. 

The heap has advantages and disadvantages:
* Allocating memory on the heap is comparatively slow.
* Allocated memory stays allocated until it is specifically deallocated (beware memory leaks) or the application ends (at which point the OS should clean it up).
* Dynamically allocated memory must be accessed through a pointer. Dereferencing a pointer is slower than accessing a variable directly.
* Because the heap is a big pool of memory, large arrays, structures, or classes can be allocated here.

3. The call stack (usually referred to as “the stack”) has a much more interesting role to play. The call stack keeps track of all the active functions (those that have been called but have not yet terminated) from the start of the program to the current point of execution, and handles allocation of all function parameters and local variables.

The call stack is implemented as a stack data structure. So before we can talk about how the call stack works, we need to understand what a stack data structure is.

A data structure is a programming mechanism for organizing data so that it can be used efficiently. You’ve already seen several types of data structures, such as arrays and structs. Both of these data structures provide mechanisms for storing data and accessing that data in an efficient way.

A stack is a last-in, first-out (LIFO) structure. The last item pushed onto the stack will be the first item popped off. 

4. The call stack segment holds the memory used for the call stack. 

5. When a function call is encountered, the function is pushed onto the call stack. When the current function ends, that function is popped off the call stack (this process is sometimes called unwinding the stack). Thus, by looking at the functions that are currently on the call stack, we can see all of the functions that were called to get to the current point of execution.

Stack frames are "items" we push (place onto) and pop (remove) from the stack.

The “marker” is a register (a piece of memory in the CPU) known as the stack pointer (abbreviated “SP”). The stack pointer keeps track of where the top of the call stack currently is. 

6. When we pop an item off the call stack, we only have to move the stack pointer down -- we don’t have to clean up or zero the memory used by the popped stack frame. This memory is no longer considered to be “on the stack” (the stack pointer will be at or below this address), so it won’t be accessed. If we later push a new stack frame to this same memory, it will overwrite the old value we never cleaned up.

7.  Stack overflow happens when all the memory in the stack has been allocated -- in that case, further allocations begin overflowing into other sections of memory. Stack overflow is generally the result of allocating too many variables on the stack, and/or making too many nested function calls (where function A calls function B calls function C calls function D etc…) On modern operating systems, overflowing the stack will generally cause your OS to issue an access violation and terminate the program.


## 20.3 Recursion

1. A recursive function in C++ is a function that calls itself.

A recursive termination is a condition that, when met, will cause the recursive function to stop calling itself. Recursive termination generally involves using an if statement:

```c++
#include <iostream>

void countDown(int count)
{
    std::cout << "push " << count << '\n';

    if (count > 1) // termination condition
        countDown(count-1);

    std::cout << "pop " << count << '\n';
}

int main()
{
    countDown(5);
    return 0;
}
```

Now when we run our program, countDown() will start by outputting the following:
$$
push 5
push 4
push 3
push 2
push 1
$$

If you were to look at the call stack at this point, you would see the following:

$$
countDown(1)
countDown(2)
countDown(3)
countDown(4)
countDown(5)
main()
$$

A more useful example:

```c++
// return the sum of all the integers between 1 (inclusive) and sumto (inclusive)
// returns 0 for negative numbers
int sumTo(int sumto)
{
    if (sumto <= 0)
        return 0; // base case (termination condition) when user passed in an unexpected argument (0 or negative)
    if (sumto == 1)
        return 1; // normal base case (termination condition)

    return sumTo(sumto - 1) + sumto; // recursive function call
}
```

Inputs for which a recursive algorithm trivially produces an output is called a base case. Base cases act as termination conditions for the algorithm. Base cases can often be identified by considering the output for an input of 0, 1, “”, ”, or null.

2. There are techniques that can be used to reduce the number of recursive calls necessary. 

One technique, called memoization, caches the results of expensive function calls so the result can be returned when the same input occurs again.

Here’s a memoized version of a recursive Fibonacci algorithm:

```c++
#include <iostream>
#include <vector>

// h/t to potterman28wxcv for a variant of this code
// count is now a std::size_t to make indexing the std::vector easier
int fibonacci(std::size_t count)
{
	// We'll use a static std::vector to cache calculated results
	static std::vector results{ 0, 1 };

	// If we've already seen this count, then use the cache'd result
	if (count < std::size(results))
		return results[count];

	// Otherwise calculate the new result and add it
	results.push_back(fibonacci(count - 1) + fibonacci(count - 2));
	return results[count];
}

// And a main program to display the first 13 Fibonacci numbers
int main()
{
	for (int count { 0 }; count < 13; ++count)
		std::cout << fibonacci(static_cast<std::size_t>(count)) << ' ';

	return 0;
}
```

In general, recursion is a good choice when most of the following are true:
* The recursive code is much simpler to implement than a loop.
* The recursion depth can be limited (e.g. there’s no way to provide an input that will cause it to recurse down 100,000 levels).
* The iterative version of the algorithm requires managing a stack of data.
* This isn’t a performance-critical section of code.
However, if the recursive algorithm is simpler to implement, it may make sense to start recursively and then optimize to an iterative algorithm later.


## 20.4 Command line arguments

1. Command line arguments are optional string arguments that are passed by the operating system to the program when it is launched. The program can then use them as input (or ignore them). Much like function parameters provide a way for a function to provide inputs to another function, command line arguments provide a way for people or programs to provide inputs to a program.

Executable programs can be run on the command line by invoking them by name. For example, to run the executable file “WordCount” that is located in the current directory of a Windows machine, you could type:
$$
WordCount
$$

The equivalent command line on a Unix-based OS would be:
$$
./WordCount
$$

In order to pass command line arguments to WordCount, we simply list the command line arguments after the executable name:
$$
WordCount Myfile.txt
$$

Now when WordCount is executed, Myfile.txt will be provided as a command line argument. A program can have multiple command line arguments, separated by spaces:
$$
WordCount Myfile.txt Myotherfile.txt
$$

2. Now that we know how to provide command line arguments to a program, the next step is to access them from within our C++ program. To do that, we use a different form of main() than we’ve seen before. This new form of main() takes two arguments (named argc and argv by convention) as follows:
```c++
int main(int argc, char* argv[])
```

You will sometimes also see it written as:
```c++
int main(int argc, char** argv)
```

argc is an integer parameter containing a count of the number of arguments passed to the program (think: argc = argument count). argc will always be at least 1, because the first argument is always the name of the program itself. Each command line argument the user provides will cause argc to increase by 1.

argv is where the actual argument values are stored (think: argv = argument values, though the proper name is “argument vectors”). Although the declaration of argv looks intimidating, argv is really just a C-style array of char pointers (each of which points to a C-style string). The length of this array is argc.

Let’s write a short program named “MyArgs” to print the value of all the command line parameters:

```c++
// Program: MyArgs
#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << "There are " << argc << " arguments:\n";

    // Loop through each argument and print its number and value
    for (int count{ 0 }; count < argc; ++count)
    {
        std::cout << count << ' ' << argv[count] << '\n';
    }

    return 0;
}
```

2. Command line arguments are always passed as strings, even if the value provided is numeric in nature. To use a command line argument as a number, you must convert it from a string to a number. Unfortunately, C++ makes this a little more difficult than it should be.

The C++ way to do this follows:

#include <iostream>
#include <sstream> // for std::stringstream
#include <string>

```c++
int main(int argc, char* argv[])
{
	if (argc <= 1)
	{
		// On some operating systems, argv[0] can end up as an empty string instead of the program's name.
		// We'll conditionalize our response on whether argv[0] is empty or not.
		if (argv[0])
			std::cout << "Usage: " << argv[0] << " <number>" << '\n';
		else
			std::cout << "Usage: <program name> <number>" << '\n';

		return 1;
	}

	std::stringstream convert{ argv[1] }; // set up a stringstream variable named convert, initialized with the input from argv[1]

	int myint{};
	if (!(convert >> myint)) // do the conversion
		myint = 0; // if conversion fails, set myint to a default value

	std::cout << "Got integer: " << myint << '\n';

	return 0;
}
```

3. The OS parses command line arguments first. 


## 20.5 Ellipsis 

1. The best way to learn about ellipsis is by example. So let’s write a simple program that uses ellipsis. Let’s say we want to write a function that calculates the average of a bunch of integers. We’d do it like this:

```c++
#include <iostream>
#include <cstdarg> // needed to use ellipsis

// The ellipsis must be the last parameter
// count is how many additional arguments we're passing
double findAverage(int count, ...)
{
    int sum{ 0 };

    // We access the ellipsis through a va_list, so let's declare one
    std::va_list list;

    // We initialize the va_list using va_start.  The first argument is
    // the list to initialize.  The second argument is the last non-ellipsis
    // parameter.
    va_start(list, count);

    // Loop through all the ellipsis values
    for (int arg{ 0 }; arg < count; ++arg)
    {
         // We use va_arg to get values out of our ellipsis
         // The first argument is the va_list we're using
         // The second argument is the type of the value
         sum += va_arg(list, int);
    }

    // Cleanup the va_list when we're done.
    va_end(list);

    return static_cast<double>(sum) / count;
}

int main()
{
    std::cout << findAverage(5, 1, 2, 3, 4, 5) << '\n';
    std::cout << findAverage(6, 1, 2, 3, 4, 5, 6) << '\n';

    return 0;
}
```

As you can see, this function takes a variable number of parameters! 

2. Why ellipsis are dangerous: Type checking is suspended. Ellipsis offer the programmer a lot of flexibility to implement functions that can take a variable number of parameters. However, this flexibility comes with some downsides. If the actual parameter type doesn’t match the expected parameter type, bad things will usually happen. 

Not only do the ellipsis throw away the type of the parameters, it also throws away the number of parameters in the ellipsis. This means we have to devise our own solution for keeping track of the number of parameters passed into the ellipsis. Typically, this is done in one of three ways:
* Method 1: Pass a length parameter
* Method 2: Use a sentinel value (a special value that is used to terminate a loop when it is encountered)
* Method 3: Use a decoder string


## 20.6 Introduction to lambdas (anonymous functions)

1. A lambda expression (also called a lambda or closure) allows us to define an anonymous function inside another function. The nesting is important, as it allows us both to avoid namespace naming pollution, and to define the function as close to where it is used as possible (providing additional context).

The syntax for lambdas is one of the weirder things in C++, and takes a bit of getting used to. Lambdas take the form:

[ captureClause ] ( parameters ) -> returnType
{
    statements;
}

* The capture clause can be empty if no captures are needed.
* The parameter list can be empty if no parameters are required. It can also be omitted entirely unless a return type is specified.
* The return type is optional, and if omitted, auto will be assumed (thus using type deduction used to determine the return type). While we previously noted that type deduction for function return types should be avoided, in this context, it’s fine to use (because these functions are typically so trivial).

Also note that lambdas (being anonymous) have no name, so we don’t need to provide one.

This means a trivial lambda definition looks like this:

```c++
#include <iostream>

int main()
{
  [] {}; // a lambda with an omitted return type, no captures, and omitted parameters.

  return 0;
}
```

2. An example:

```c++
#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>

// Our function will return true if the element matches
bool containsNut(std::string_view str)
{
    // std::string_view::find returns std::string_view::npos if it doesn't find
    // the substring. Otherwise it returns the index where the substring occurs
    // in str.
    return str.find("nut") != std::string_view::npos;
}

int main()
{
    constexpr std::array<std::string_view, 4> arr{ "apple", "banana", "walnut", "lemon" };

    // Scan our array to see if any elements contain the "nut" substring
    auto found{ std::find_if(arr.begin(), arr.end(), containsNut) };

    if (found == arr.end())
    {
        std::cout << "No nuts\n";
    }
    else
    {
        std::cout << "Found " << *found << '\n';
    }

    return 0;
}
```

Becomes:

```c++
#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>

int main()
{
  constexpr std::array<std::string_view, 4> arr{ "apple", "banana", "walnut", "lemon" };

  // Define the function right where we use it.
  auto found{ std::find_if(arr.begin(), arr.end(),
                           [](std::string_view str) // here's our lambda, no capture clause
                           {
                             return str.find("nut") != std::string_view::npos;
                           }) };

  if (found == arr.end())
  {
    std::cout << "No nuts\n";
  }
  else
  {
    std::cout << "Found " << *found << '\n';
  }

  return 0;
}
```

Lambdas are preferred over normal functions when we need a trivial, one-off function to pass as an argument to some other function.

3. In the above example, we defined a lambda right where it was needed. This use of a lambda is sometimes called a function literal. For example, in the following snippet, we’re using std::all_of to check if all elements of an array are even:

```c++
// Bad: We have to read the lambda to understand what's happening.
return std::all_of(array.begin(), array.end(), [](int i){ return ((i % 2) == 0); });
```

We can improve the readability of this as follows:

```c++
// Good: Instead, we can store the lambda in a named variable and pass it to the function.
auto isEven{
  [](int i)
  {
    return (i % 2) == 0;
  }
};

return std::all_of(array.begin(), array.end(), isEven);
```

4. As it turns out, lambdas don’t have a type that we can explicitly use. When we write a lambda, the compiler generates a unique type just for the lambda that is not exposed to us. In actuality, lambdas aren’t functions (which is part of how they avoid the limitation of C++ not supporting nested functions). They’re a special kind of object called a functor. Functors are objects that contain an overloaded operator() that make them callable like a function.

5. Although we don’t know the type of a lambda, there are several ways of storing a lambda for use post-definition. If the lambda has an empty capture clause (nothing between the hard brackets []), we can use a regular function pointer. std::function or type deduction via the auto keyword will also work (even if the lambda has a non-empty capture).

```c++
#include <functional>

int main()
{
  // A regular function pointer. Only works with an empty capture clause (empty []).
  double (*addNumbers1)(double, double){
    [](double a, double b) {
      return a + b;
    }
  };

  addNumbers1(1, 2);

  // Using std::function. The lambda could have a non-empty capture clause (discussed next lesson).
  std::function addNumbers2{ // note: pre-C++17, use std::function<double(double, double)> instead
    [](double a, double b) {
      return a + b;
    }
  };

  addNumbers2(3, 4);

  // Using auto. Stores the lambda with its real type.
  auto addNumbers3{
    [](double a, double b) {
      return a + b;
    }
  };

  addNumbers3(5, 6);

  return 0;
}
```

What if we want to pass a lambda to a function? There are 4 options:

```c++
#include <functional>
#include <iostream>

// Case 1: use a `std::function` parameter
void repeat1(int repetitions, const std::function<void(int)>& fn)
{
    for (int i{ 0 }; i < repetitions; ++i)
        fn(i);
}

// Case 2: use a function template with a type template parameter
template <typename T>
void repeat2(int repetitions, const T& fn)
{
    for (int i{ 0 }; i < repetitions; ++i)
        fn(i);
}

// Case 3: use the abbreviated function template syntax (C++20)
void repeat3(int repetitions, const auto& fn)
{
    for (int i{ 0 }; i < repetitions; ++i)
        fn(i);
}

// Case 4: use function pointer (only for lambda with no captures)
void repeat4(int repetitions, void (*fn)(int))
{
    for (int i{ 0 }; i < repetitions; ++i)
        fn(i);
}

int main()
{
    auto lambda = [](int i)
    {
        std::cout << i << '\n';
    };

    repeat1(3, lambda);
    repeat2(3, lambda);
    repeat3(3, lambda);
    repeat4(3, lambda);

    return 0;
}
```

When storing a lambda in a variable, use auto as the variable’s type.

6. Because lambdas with one or more auto parameter can potentially work with a wide variety of types, they are called generic lambdas. 

As of C++17, lambdas are implicitly constexpr if the result satisfies the requirements of a constant expression. This generally requires two things:
* The lambda must either have no captures, or all captures must be constexpr.
* The functions called by the lambda must be constexpr. 

Note that if the generic lambda uses static duration variables, those variables are not shared between the generated lambdas.


## 20.7 Lambda captures

1. Lambdas can only access certain kinds of objects that have been defined outside the lambda. This includes:
* Objects with static (or thread local) storage duration (this includes global variables and static locals)
* Objects that are constexpr (explicitly or implicitly)

2. The capture clause is used to (indirectly) give a lambda access to variables available in the surrounding scope that it normally would not have access to. All we need to do is list the entities we want to access from within the lambda as part of the capture clause. In this case, we want to give our lambda access to the value of variable search, so we add it to the capture clause:

```c++
#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>
#include <string>

int main()
{
  std::array<std::string_view, 4> arr{ "apple", "banana", "walnut", "lemon" };

  std::cout << "search for: ";

  std::string search{};
  std::cin >> search;

  // Capture @search                                vvvvvv
  auto found{ std::find_if(arr.begin(), arr.end(), [search](std::string_view str) {
    return str.find(search) != std::string_view::npos;
  }) };

  if (found == arr.end())
  {
    std::cout << "Not found\n";
  }
  else
  {
    std::cout << "Found " << *found << '\n';
  }

  return 0;
}
```

When a lambda definition is executed, for each variable that the lambda captures, a clone of that variable is made (with an identical name) inside the lambda. These cloned variables are initialized from the outer scope variables of the same name at this point. 

The captured variables of a lambda are copies of the outer scope variables, not the actual variables.

When a lambda is called, operator() is invoked. By default, this operator() treats captures as const, meaning the lambda is not allowed to modify those captures.

To allow modifications of variables that were captured, we can mark the lambda as mutable:

```c++
#include <iostream>

int main()
{
  int ammo{ 10 };

  auto shoot{
    [ammo]() mutable { // now mutable
      // We're allowed to modify ammo now
      --ammo;

      std::cout << "Pew! " << ammo << " shot(s) left.\n";
    }
  };

  shoot();
  shoot();

  std::cout << ammo << " shot(s) left\n";

  return 0;
}
```

Because captured variables are members of the lambda object, their values are persisted across multiple calls to the lambda!

Much like functions can change the value of arguments passed by reference, we can also capture variables by reference to allow our lambda to affect the value of the argument.

Multiple variables can be captured by separating them with a comma. This can include a mix of variables captured by value or by reference:
```c++
int health{ 33 };
int armor{ 100 };
std::vector<CEnemy> enemies{};

// Capture health and armor by value, and enemies by reference.
[health, armor, &enemies](){};
```

A default capture (also called a capture-default) captures all variables that are mentioned in the lambda. Variables not mentioned in the lambda are not captured if a default capture is used.
* To capture all used variables by value, use a capture value of =.
* To capture all used variables by reference, use a capture value of &.

Default captures can be mixed with normal captures. We can capture some variables by value and others by reference, but each variable can only be captured once.
```c++
int health{ 33 };
int armor{ 100 };
std::vector<CEnemy> enemies{};

// Capture health and armor by value, and enemies by reference.
[health, armor, &enemies](){};

// Capture enemies by reference and everything else by value.
[=, &enemies](){};

// Capture armor by value and everything else by reference.
[&, armor](){};

// Illegal, we already said we want to capture everything by reference.
[&, &armor](){};

// Illegal, we already said we want to capture everything by value.
[=, armor](){};

// Illegal, armor appears twice.
[armor, &health, &armor](){};

// Illegal, the default capture has to be the first element in the capture group.
[armor, &](){};
```

Sometimes we want to capture a variable with a slight modification or declare a new variable that is only visible in the scope of the lambda. We can do so by defining a variable in the lambda-capture without specifying its type.

Variables are captured at the point where the lambda is defined. If a capture by reference dies before the lambda, the lambda will be holding a dangling reference.

3. Try to avoid mutable lambdas. 

4. Although lambdas look like functions, they’re actually objects that can be called like functions -- these are called functors. When the compiler encounters a lambda definition, it creates a custom object definition for the lambda. Each captured variable becomes a data member of the object. At runtime, when the lambda definition is encountered, the lambda object is instantiated, and the members of the lambda are initialized at that point.