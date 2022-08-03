#pragma once
#include <string>

using namespace std;

class Creature
{
protected:
    string name;
    int health;
    int damage;
    int gold;

public:
    Creature(string name, int health, int damage, int gold);

    const string& getName();

    int getHealth();

    int getDamage();

    int getGold();

    void reduceHealth(int health);

    bool isDead();

    void addGold(int gold);
};

