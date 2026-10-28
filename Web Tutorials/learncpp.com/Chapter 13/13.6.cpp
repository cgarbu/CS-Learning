// Define an enum class named Animal that contains the following animals: pig, chicken, goat, cat, dog, duck.

// Write a function named getAnimalName() that takes an Animal parameter and uses a switch statement to return the name for that animal as a std::string_view (or std::string if you’re using C++14).

// Write another function named printNumberOfLegs() that uses a switch statement to print the number of legs each animal walks on.

// Make sure both functions have a default case that prints an error message. Call printNumberOfLegs() from main() with a cat and a chicken. Your output should look like this:
// A cat has 4 legs.
// A chicken has 2 legs.

#include <iostream>
#include <string_view>

enum class Animal
{
    pig,
    chicken,
    goat,
    cat,
    dog,
    duck,
};

std::string_view getAnimalName(Animal animalEnumerator)
{
    using enum Animal;

    switch (animalEnumerator)
    {
    case pig:
        return "pig";
    case chicken:
        return "chicken";
    case goat:
        return "goat";
    case cat:
        return "cat";
    case dog:
        return "dog";
    case duck:
        return "duck";
    default:
        std::cerr << "Invalid animal.\n";
        return "";
    }
}

void printNumberOfLegs(Animal animalEnumerator)
{
    using enum Animal;

    switch (animalEnumerator)
    {
    case pig:
        std::cout << "A " << getAnimalName(animalEnumerator) << " has 4 legs.\n";
        break;
    case chicken:
        std::cout << "A " << getAnimalName(animalEnumerator) << " has 2 legs.\n";
        break;
    case goat:
        std::cout << "A " << getAnimalName(animalEnumerator) << " has 4 legs.\n";
        break;
    case cat:
        std::cout << "A " << getAnimalName(animalEnumerator) << " has 4 legs.\n";
        break;
    case dog:
        std::cout << "A " << getAnimalName(animalEnumerator) << " has 4 legs.\n";
        break;
    case duck:
        std::cout << "A " << getAnimalName(animalEnumerator) << " has 2 legs.\n";
        break;
    default:
        std::cerr << "Invalid animal.\n";
    }
}

int main()
{
    using enum Animal;

    printNumberOfLegs(cat);
    printNumberOfLegs(chicken);

    return 0;
}