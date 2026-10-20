// Write a program that:

// Asks the user how many names they wish to enter.
// Dynamically allocates a std::string array.
// Asks the user to enter each name.
// Calls std::sort to sort the names (See 18.1 -- Sorting an array using selection sort and 17.9 -- Pointer arithmetic and subscripting)
// Prints the sorted list of names.
// std::string supports comparing strings via the comparison operators < and >. You don’t need to implement string comparison by hand.

// Your output should match this:

// How many names would you like to enter? 5
// Enter name #1: Jason
// Enter name #2: Mark
// Enter name #3: Alex
// Enter name #4: Chris
// Enter name #5: John

// Here is your sorted list:
// Name #1: Alex
// Name #2: Chris
// Name #3: Jason
// Name #4: John
// Name #5: Mark

#include <iostream>
#include <algorithm> 
#include <string>

void sortNamesAndPrint(std::string* names, std::size_t numNames) // Could be split into two functions.
{
    std::sort(names, names + numNames);

    std::cout << "Here is your sorted list:\n";
    for (std::size_t i{ 0 }; i < numNames; ++i)
    {
        std::cout << "Name #" << i + 1 << ": " << names[i] << '\n';
    }
}

void getInputAndCallSort() 
{
    std::cout << "How many names would you like to enter? ";
    std::size_t numNames{};
    std::cin >> numNames;

    // std::size_t is unsigned, so it cannot represent negative numbers. I am assuming the user will not enter a negative number. 
    std::string* names{ new std::string[numNames] };
    for (std::size_t i{ 0 }; i < numNames; ++i)
    {
        std::cout << "Enter name #" << i + 1 << ": ";
        std::cin >> names[i];
    }

    sortNamesAndPrint(names, numNames);
    delete[] names; 
}

int main()
{
    getInputAndCallSort();

    return 0;
}