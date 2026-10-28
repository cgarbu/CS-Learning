// Write a program that asks the user to input a number between 0 and 255. Print this number as an 8-bit binary number (of the form #### ####). 

// Don’t use any bitwise operators. Don’t use std::bitset.

#include <iostream>

void printBinary(int input)
{
    // Left nibble (half-byte)
    (input / 128) % 2 == 0 ? std::cout << 0 : std::cout << 1;    // Position 7 
    (input / 64) % 2 == 0 ? std::cout << 0 : std::cout << 1;     // Position 6 
    (input / 32) % 2 == 0 ? std::cout << 0 : std::cout << 1;     // Position 5 
    (input / 16) % 2 == 0 ? std::cout << 0 : std::cout << 1;     // Position 4 

    // Right nibble (half-byte)
    (input / 8) % 2 == 0 ? std::cout << 0 : std::cout << 1;      // Position 3 
    (input / 4) % 2 == 0 ? std::cout << 0 : std::cout << 1;      // Position 2 
    (input / 2) % 2 == 0 ? std::cout << 0 : std::cout << 1;      // Position 1 
    (input / 1) % 2 == 0 ? std::cout << 0 : std::cout << 1;      // Position 0 
}

int getNumber()
{
    std::cout << "Input a number between 0 and 255: ";
    int input{ };
    std::cin >> input;

    return input; 
}

int main()
{
    printBinary(getNumber());
    
    return 0; 
}

