#include "Monster.h"

Monster::Monster(Type type)
    : Creature(monsterData[type].name, monsterData[type].health, monsterData[type].damage, monsterData[type].gold) {}

Monster::Monster(string name, int health, int damage, int gold)
    : Creature(name, health, damage, gold) {}

Monster Monster::getRandomMonster()
{
    int num = getRandomNumber(0, MAX_TYPES - 1);
    return Monster(static_cast<Type>(num));
}