#include <iostream>
#include <ctime>
#include "Creature.h"
#include "Player.h"
#include "Monster.h"
#include "RandomNumber.h"

using namespace std;

void attackPlayer(Player& p, Monster& m);
void attackMonster(Monster& m, Player& p);
void randomMonsterAndFight(Player& p);
void fightMonster(Player& p, Monster& m);
void saveTheCiri(Player& p, int& count);
void healthDamage(Player& p);
char inputQuest();
void quest(Player& p);
char takeTheKingMoney();
char reset();

int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(0));
    rand();

    do {
        Player player("Геральд");
        cout << "Привет, " << player.getName() << '!' << endl;
        healthDamage(player);

        int count = 0;
        while (!player.isDead() && !player.hasWon())
        {
            randomMonsterAndFight(player);

            if (count < 1)
            {
                if (player.getLevel() >= 10 && player.getLevel() < 20)
                    saveTheCiri(player, count);
            }
        }

        if (player.getLevel() == 20)
            quest(player);

        if (player.isDead())
        {
            cout << "\nТЫ умер! Заработал " << player.getGold() << " крон.\n";
            cout << "Жаль, что ты не можешь забрать это с собой!" << endl;
        }
        else
        {
            cout << "\nТы убил всех монстров и заработал " << player.getGold() << " крон!" << endl;
        }   
    } while (reset());

    cin.get();
    return 0;
}

Monster::MonsterData Monster::monsterData[Monster::MAX_TYPES]
{
    {"Волк",1,2,10},
    {"Василиск",15,10,70},
    {"Гуль",5,5,25},
    {"Утопец",2,2,15},
    {"Призрак",4,3,20},
    {"Виверна",10,8,50}
};

void attackPlayer(Player& p, Monster& m)
{
    if (p.isDead())
        return;

    cout << "Удар отнял здоровья: " << p.getDamage() << '\n';

    m.reduceHealth(p.getDamage());

    if (m.isDead())
    {
        cout << "Ты убил: " << m.getName() << ".\n";
        p.levelUp();
        cout << "\nТеперь твой уровень: " << p.getLevel() << ". Здоровье: " << p.getHealth() << ". Урон: " << p.getDamage() << ".\n";
        p.addGold(m.getGold());
        cout << "В кошельке: " << p.getGold() << " крон.\n";
    }
}

void attackMonster(Monster& m, Player& p)
{
    if (m.isDead())
        return;

    p.reduceHealth(m.getDamage());

    cout << m.getName() << " отнял здоровья: " << m.getDamage() << " Осталось: ";

    if (p.getHealth() <= 0)
        cout << 0 << '\n';
    else
        cout << p.getHealth() << '\n';
}

void randomMonsterAndFight(Player& p)
{
    Monster m = Monster::getRandomMonster();

    fightMonster(p, m);
}

void fightMonster(Player& p, Monster& m)
{
    cout << "\nТы встретил: " << m.getName() << ". Здоровье: " << m.getHealth() << ". Урон: " << m.getDamage() << endl;

    while (!m.isDead() && !p.isDead())
    {
        cout << "(r)БЕЖАТЬ / (f)СРАЖАТЬСЯ: ";
        char input;
        cin >> input;

        if (input == 'r')
        {
            if (getRandomNumber(1, 2) == 1)
            {
                cout << "Удалось сбежать.\n";
                return;
            }
            else
            {
                cout << "Тебя настигли.\n";
                attackMonster(m, p);
                continue;
            }
        }

        if (input == 'f')
        {
            attackPlayer(p, m);
            attackMonster(m, p);
        }
    }
}

void saveTheCiri(Player& p, int& count)
{
    if (getRandomNumber(1, 5) == 2)
    {
        cout << "\nСпаси Цири!";
        Monster m("Дикая охота", 20, 10, 100);
        while (!p.isDead() && !m.isDead())
        {
            fightMonster(p, m);
        }

        ++count;
    }
}

void healthDamage(Player& p)
{
    cout << "Здоровье: " << p.getHealth() << ". Урон: " << p.getDamage() << "." << endl;
}

char inputQuest()
{
    cout << "\nЛютику требуется твоя помощь!!!\n";

    char input;
    do {
        cout << "Помочь? (y)ОХ УЖ ЭТОТ ЛЮТИК / (n)НИ ЗА ЧТО: ";
        cin >> input;
    } while (input != 'y' && input != 'n');

    return input;
}

void quest(Player& p)
{
    inputQuest();

    cout << p.getName() << " решил помочь!\n";
    cout << "Помоги завоевать сердце принцессы. Убей Короля.\n" << endl;
    Monster king("Король", 50, 10, 0);

    while (!p.isDead() && !king.isDead())
    {
        attackPlayer(p, king);
        attackMonster(king, p);

        if (king.getHealth() <= 10)
        {
            cout << '\n' << p.getName() << " давай договоримся. ";
            cout << king.getName() << " протягивает 100 крон." << endl;

            if (takeTheKingMoney() == 'y')
            {
                cout << "\nТы взял деньги.\n";
                p.addGold(100);
                cout << "Лютик огорчен.\n";
                return;
            }
            else
            {
                cout << '\n' << king.getName() << " использовал магию и сбежал" << endl;
                return;
            }
        }
    }
}

char takeTheKingMoney()
{
    char input;
    do {
        cout << "Принять? (y)ДА / (n)НЕТ: ";
        cin >> input;
    } while (input != 'y' && input != 'n');

    return input;
}

char reset()
{
    char input;
    do {
        cout << "Сыграем еще? (y)ДА / (n)НЕТ: ";
        cin >> input;
    } while (input != 'y' && input != 'n');

    cout << "____________________________________________" << endl;

    return (input == 'y');
}