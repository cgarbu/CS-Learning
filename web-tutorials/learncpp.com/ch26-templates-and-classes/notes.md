## 26.2 Template non-type parameters

A template non-type parameter is a template parameter where the type of the parameter is predefined and is substituted for a constexpr value passed in as an argument.

A non-type parameter can be any of the following types:
An integral type
An enumeration type
A pointer or reference to a class object
A pointer or reference to a function
A pointer or reference to a class member function
std::nullptr_t
A floating point type (since C++20)

In the following example, we create a non-dynamic (static) array class that uses both a type parameter and a non-type parameter. The type parameter controls the data type of the static array, and the integral non-type parameter controls how large the static array is.
```c++
#include <iostream>

template <typename T, int size> // size is an integral non-type parameter
class StaticArray
{
private:
    // The non-type parameter controls the size of the array
    T m_array[size] {};

public:
    T* getArray();

    T& operator[](int index)
    {
        return m_array[index];
    }
};

// Showing how a function for a class with a non-type parameter is defined outside of the class
template <typename T, int size>
T* StaticArray<T, size>::getArray()
{
    return m_array;
}

int main()
{
    // declare an integer array with room for 12 integers
    StaticArray<int, 12> intArray;

    // Fill it up in order, then print it backwards
    for (int count { 0 }; count < 12; ++count)
        intArray[count] = count;

    for (int count { 11 }; count >= 0; --count)
        std::cout << intArray[count] << ' ';
    std::cout << '\n';

    // declare a double buffer with room for 4 doubles
    StaticArray<double, 4> doubleArray;

    for (int count { 0 }; count < 4; ++count)
        doubleArray[count] = 4.4 + 0.1 * count;

    for (int count { 0 }; count < 4; ++count)
        std::cout << doubleArray[count] << ' ';

    return 0;
}
```


## 26.3 Function template specialization


When instantiating a function template for a given type, the compiler stencils out a copy of the templated function and replaces the template type parameters with the actual types used in the variable declaration. This means a particular function will have the same implementation details for each instanced type (just using different types). While most of the time this is exactly what you want, occasionally there are cases where it is useful to implement a templated function slightly differently for a specific data type.

Another way to achieve a similar result is to use explicit template specialization. Explicit template specialization (often shortened to template specialization) is a feature that allows us to explicitly define different implementations of a template for specific types or values. When all of the template parameters are specialized, it is called a full specialization. When only some of the template parameters are specialized, it is called a partial specialization.

Let’s create a specialization of print<T> when T is a double:

```c++
#include <iostream>

// Here's our primary template (must come first)
template <typename T>
void print(const T& t)
{
    std::cout << t << '\n';
}

// A full specialization of primary template print<T> for type double
// Full specializations are not implicitly inline, so make this inline if put in header file
template<>                          // template parameter declaration containing no template parameters
void print<double>(const double& d) // specialized for type double
{
    std::cout << std::scientific << d << '\n';
}

int main()
{
    print(5);
    print(6.7);

    return 0;
}
```

Full specializations are not implicitly inline (partial specializations are implicitly inline). If you put a full specialization in a header file, it should be marked as inline so that it does not cause ODR violations when included into multiple translation units.


## 26.4 Class template specialization

Class template specialization allows us to specialize a template class for a particular data type (or data types, if there are multiple template parameters). In this case, we’re going to use class template specialization to write a customized version of Storage8<bool> that will take precedence over the generic Storage8<T> class.

Class template specializations are treated as completely independent classes, even though they are instantiated in the same way as the templated class. This means that we can change anything and everything about our specialization class, including the way it’s implemented and even the functions it makes public, just as if it were an independent class.

Just like all templates, the compiler must be able to see the full definition of a specialization to use it. Also, defining a class template specialization requires the non-specialized class to be defined first.

Here’s an example of a specialized Storage8<bool> class:

```c++
#include <cstdint>

// First define our non-specialized class template
template <typename T>
class Storage8
{
private:
    T m_array[8];

public:
    void set(int index, const T& value)
    {
        m_array[index] = value;
    }

    const T& get(int index) const
    {
        return m_array[index];
    }
};

// Now define our specialized class template
template <> // the following is a template class with no templated parameters
class Storage8<bool> // we're specializing Storage8 for bool
{
// What follows is just standard class implementation details

private:
    std::uint8_t m_data{};

public:
    // Don't worry about the details of the implementation of these functions
    void set(int index, bool value)
    {
        // Figure out which bit we're setting/unsetting
        // This will put a 1 in the bit we're interested in turning on/off
        auto mask{ 1 << index };

        if (value)  // If we're setting a bit
            m_data |= mask;   // use bitwise-or to turn that bit on
        else  // if we're turning a bit off
            m_data &= ~mask;  // bitwise-and the inverse mask to turn that bit off
	}

    bool get(int index)
    {
        // Figure out which bit we're getting
        auto mask{ 1 << index };
        // bitwise-and to get the value of the bit we're interested in
        // Then implicit cast to boolean
        return (m_data & mask);
    }
};

// Same example as before
int main()
{
    // Define a Storage8 for integers (instantiates Storage8<T>, where T = int)
    Storage8<int> intStorage;

    for (int count{ 0 }; count < 8; ++count)
    {
        intStorage.set(count, count);
	}

    for (int count{ 0 }; count < 8; ++count)
    {
        std::cout << intStorage.get(count) << '\n';
    }

    // Define a Storage8 for bool  (instantiates Storage8<bool> specialization)
    Storage8<bool> boolStorage;

    for (int count{ 0 }; count < 8; ++count)
    {
        boolStorage.set(count, count & 3);
    }

	std::cout << std::boolalpha;

    for (int count{ 0 }; count < 8; ++count)
    {
        std::cout << boolStorage.get(count) << '\n';
    }

    return 0;
}
```

In order to use a specialization, the compiler must be able to see the full definition of both the non-specialized class and the specialized class. If the compiler can only see the definition of the non-specialized class, it will use that instead of the specialization.

For this reason, specialized classes and functions are often defined in a header file just below the definition of the non-specialized class, so that including a single header includes both the non-specialized class and any specializations. This ensures the specialization can always be seen whenever the non-specialized class can also be seen.

If a specialization is only required in a single translation unit, it can be defined in the source file for that translation unit. Because other translation units will not be able to see the definition of the specialization, they will continue to use the non-specialized version.

Be wary of putting a specialization in its own separate header file, with the intent of including the specialization’s header in any translation unit where the specialization is desired. It’s a bad idea to design code that transparently changes behavior based on the presence or absence of a header file. For example, if you intend to use the specialization but forget to include the header of the specialization, you may end up using the non-specialized version instead. If you intend to use the non-specialization, you may end up using the specialization anyway if some other header includes the specialization as a transitive include.


## 26.5  Partial template specialization

Recap:
1. Full template at top
```c++
template <typename T, typename U>
class Storage {
public:
    void print() { std::cout << "Generic implementation\n"; }
};
```
2. Full Specialization: you must explicitly declare template <> and define specific types for every argument inside the trailing angle brackets.
```c++
template <>
class Storage<int, double> {
public:
    void print() { std::cout << "Fully specialized for <int, double>\n"; }
};
```
3. You only specialize part of the template structure, such as locking in a single parameter or matching specific structural type variations (like pointers).
```c++
template <typename T> // T remains generic
class Storage<T, int> { // The second argument is fixed to int
public:
    void print() { std::cout << "Partially specialized for <T, int>\n"; }
};
```

and 

```c++
template <typename T, typename U>
class Storage<T*, U*> { // Triggers only when both inputs are pointers
public:
    void print() { std::cout << "Partially specialized for pointers\n"; }
};
```

Using partial template class specialization to create separate pointer and non-pointer implementations of a class is extremely useful when you want a class to handle both differently, but in a way that’s completely transparent to the end-user.


