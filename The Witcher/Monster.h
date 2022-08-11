#pragma once
#include <string>
#include "Creature.h"
#include "RandomNumber.h"

using namespace std;

class Monster : public Creature
{
private:
    enum Type
    {
        WOLF,
        BASILISK,
        GHUL,
        DROWNER,
        GHOST,
        WYVERN,
        MAX_TYPES
    };

    struct MonsterData
    {
        string name;
        int health;
        int damage;
        int gold;
    };

    static MonsterData monsterData[MAX_TYPES];
    Type type;

public:
    Monster(Type type);

    Monster(string name, int health, int damage, int gold);

    static Monster getRandomMonster();
};

