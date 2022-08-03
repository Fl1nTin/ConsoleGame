#include "Creature.h"

Creature::Creature(string name, int health, int damage, int gold) 
	: name(name), health(health), damage(damage), gold(gold) {}

const string& Creature::getName()
{
    return name;
}

int Creature::getHealth()
{
    return health;
}

int Creature::getDamage()
{
    return damage;
}

int Creature::getGold()
{
    return gold;
}

void Creature::reduceHealth(int health)
{
    this->health -= health;
}

bool Creature::isDead()
{
    return health <= 0;
}

void Creature::addGold(int gold)
{
    this->gold += gold;
}