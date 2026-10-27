// A prime number is a natural number greater than 1 that is evenly divisible (with no remainder) only by 1 and itself.

// Complete the following program by writing the isPrime() function using a for-loop. When successful, the program will print “Success!”.

// Make sure that assert triggers even if we compile in release mode
#undef NDEBUG

#include <cassert> // for assert
#include <iostream>

// Non-optimized version
bool isPrime(int x)
{
    if (x <= 1) // if x is negative, 0, or 1 then the number is not prime
        return false;

    for (int test{ 2 }; test < x; ++test)
    {
        if (x % test == 0) // if x is evenly divisible
            return false;  // then this number isn't prime
    }

    return true; // if we didn't find any divisors, then x must be prime
}

int main()
{
    assert(!isPrime(0));
    assert(!isPrime(1));
    assert(isPrime(2));
    assert(isPrime(3));
    assert(!isPrime(4));
    assert(isPrime(5));
    assert(isPrime(7));
    assert(!isPrime(9));
    assert(isPrime(11));
    assert(isPrime(13));
    assert(!isPrime(15));
    assert(!isPrime(16));
    assert(isPrime(17));
    assert(isPrime(19));
    assert(isPrime(97));
    assert(!isPrime(99));
    assert(isPrime(13417));

    std::cout << "Success!\n";

    return 0;
}