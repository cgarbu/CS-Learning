// Put the MonsterType enumeration inside a namespace. Then, create a main() function and instantiate a troll. The program should compile.

#include <iostream>

namespace Monster
{
    enum MonsterType
    {
        orc,
        goblin,
        troll,
        ogre,
        skeleton,
    };
}

int main()
{
    [[maybe_unused]] Monster::MonsterType troll{ Monster::troll };

    return 0;
}