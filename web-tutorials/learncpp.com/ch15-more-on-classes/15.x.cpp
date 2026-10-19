#include <iostream>
#include <string>
#include <string_view> 

class Monster
{
private:
    enum Type : int; 

    Type m_type{ };
    std::string m_name{ "???" };
    std::string m_roar{ "???" };
    int m_hitPoints{ };

public: 
    enum Type : int  
    {
        dragon,
        goblin,
        ogre,
        orc,
        skeleton,
        troll,
        vampire,
        zombie,
        maxMonsterTypes,
    };

    Monster(Type type, std::string_view name, std::string_view roar, int hitPoints)
        : m_type{ type }
        , m_name{ name }
        , m_roar{ roar }
        , m_hitPoints{ hitPoints }
    {
    }
};

int main()
{
	Monster skeleton{ Monster::skeleton, "Bones", "*rattle*", 4 };
	Monster vampire{ Monster::vampire, "Nibblez", "*hiss*", 0 };

	return 0;
}

