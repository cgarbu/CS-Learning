// > Step #1
// Let’s say you’re writing a game where the player can hold 3 types of items: health potions, torches, and arrows.
// Define an unscoped enum in a namespace to identify the different types of items. Define an std::vector to store the number of each item type the player is carrying. The player should start with 1 health potion, 5 torches, and 10 arrows. Assert to make sure the array has the correct number of initializers.
// Hint: Define a count enumerator and use it inside the assert.
// The program should output the following:
// You have 16 total items

// > Step #2
// Modify your program from the prior step so it now outputs:
// You have 1 health potion
// You have 5 torches
// You have 10 arrows
// You have 16 total items
// Use a loop to print out the number of items and the item names for each inventory item. Handle proper pluralization of the names.

#include <iostream>
#undef NDEBUG
#include <cassert> 
#include <vector>

namespace ItemType
{
    enum Type : int 
    {
        healthPotion,
        torch,
        arrow,
        maxItems,
    };
};

std::size_t summateItems(const std::vector<int>& inventory)
{
    int sum{ 0 };
    for (const auto& item : inventory)
        sum += item;
    return sum; 
}

int main()
{
    std::vector inventory{ 1, 5, 10 };

    assert((inventory.size() == static_cast<std::size_t>(ItemType::maxItems)));

    std::cout << "You have " << summateItems(inventory) << " total items";

    return 0;
}