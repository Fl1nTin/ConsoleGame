#pragma once
#include <string>
#include "Creature.h"

using namespace std;

class Player : public Creature
{
private:
    int level = 1;

public:
    Player(string name);

    void levelUp();

    int getLevel();

    bool hasWon();
};

