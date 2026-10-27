// Write a program that asks for the name and age of two people, then prints which person is older.

// Here is the sample output from one run of the program:

// Enter the name of person #1: John Bacon
// Enter the age of John Bacon: 37
// Enter the name of person #2: David Jenkins
// Enter the age of David Jenkins: 44
// David Jenkins (age 44) is older than John Bacon (age 37).

#include <iostream>
#include <string>
#include <string_view>

void compareNameAndAge(std::string_view nameOne, int ageOne, std::string_view nameTwo, int ageTwo)
{
    if (ageOne > ageTwo)
        std::cout << nameOne << " (age " << ageOne << ") is older than " << nameTwo << " (age " << ageTwo << ").";
    else if (ageOne < ageTwo) 
        std::cout << nameTwo << " (age " << ageTwo << ") is older than " << nameOne << " (age " << ageOne << ").";
    else 
        std::cout << nameTwo << " and " << nameOne << " are the same age.";
}

std::string getName()
{
    std::string name{};
    std::getline(std::cin >> std::ws, name);
    return name;
}

int getAge()
{
    int age{};
    std::cin >> age; 
    return age; 
}

int main() 
{
    // Person #1 Name & Age
    std::cout << "Enter the name of person #1: ";
    const std::string nameOne{ getName() };
    std::cout << "Enter the age of " << nameOne << ": ";
    const int ageOne{ getAge() };

    // Person #2 Name & Age 
    std::cout << "Enter the name of person #2: ";
    const std::string nameTwo{ getName() };
    std::cout << "Enter the age of " << nameTwo << ": ";
    const int ageTwo{ getAge() };

    compareNameAndAge(nameOne, ageOne, nameTwo, ageTwo);

    return 0;
}