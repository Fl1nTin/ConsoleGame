#include "Player.h"

Player::Player(string name) : Creature(name, 10, 1, 0) {}

void Player::levelUp()
{
    ++level;
    ++damage;
    ++health;
}

int Player::getLevel()
{
    return level;
}

bool Player::hasWon()
{
    return level >= 20;
}