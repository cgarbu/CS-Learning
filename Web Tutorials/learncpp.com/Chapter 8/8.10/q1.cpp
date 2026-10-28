// Write a for-loop that prints every even number from 0 to 20.

#include <iostream>

int main()
{
    for (int i{ 0 }; i <= 20; i += 2)
    {
        std::cout << i << ' '; 
    }

    return 0;
}