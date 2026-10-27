// In designing a game, we decide we want to have monsters, because everyone likes fighting monsters. Declare a struct that represents your monster. The monster should have a type that can be one of the following: an ogre, a dragon, an orc, a giant spider, or a slime.

// Each individual monster should also have a name (use a std::string), as well as an amount of health that represents how much damage they can take before they die. Print out all of the struct’s members. Instantiate an ogre and a slime, initialize them using an initializer list. 

// Your program should produce the following output:

// This Ogre is named Torg and has 145 health.
// This Slime is named Blurp and has 23 health.

#include <iostream>

struct Monster
{
    std::string monsterType{ };
    std::string monsterName{ };
    int monsterHealth{ };
};

std::ostream& operator<<(std::ostream& out, const Monster& monster)
{
    out << "This " << monster.monsterType << " is named " << monster.monsterName << " and has " << monster.monsterHealth << " health."; 
    return out; 
}

int main()
{
    Monster monsterOgreTorg{ "Ogre", "Torg", 145 };
    Monster monsterSlimeBlurp{ "Slime", "Blurp", 23};

    std::cout << monsterOgreTorg << std::endl; 
    std::cout << monsterSlimeBlurp << std::endl; 

    return 0;
}