#include <iostream>
#include <ctime>
#include <windows.h>
#include "Creature.h"
#include "Player.h"
#include "Monster.h"
#include "RandomNumber.h"
#include "Menu.h"

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

int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(0));
    rand();
    SetConsoleTitle(L"The Witcher");

    Menu menu;
    menu.menuInteraction();
    menu.consoleCursorVisible(true, 10);

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

        int ch;
        if (player.isDead())
        {
            cout << "\nХолера. ТЫ умер! Заработал " << player.getGold() << " крон.\n";
            cout << "Жаль, что ТЫ не можешь забрать это с собой!" << endl;
            ch = _getch();
            system("CLS");
        }
        else
        {
            cout << "\nТЫ убил всех монстров и заработал " << player.getGold() << " крон!" << endl;
            ch = _getch();
            system("CLS");
        }

    } while (menu.menuInteraction());

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
        cout << "ТЫ убил: " << m.getName() << ".\n";
        p.levelUp();
        cout << "\nТеперь ТВОЙ уровень: " << p.getLevel() << ". Здоровье: " << p.getHealth() << ". Урон: " << p.getDamage() << ".\n";
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
    cout << "\nТЫ встретил: " << m.getName() << ". Здоровье: " << m.getHealth() << ". Урон: " << m.getDamage() << endl;

    while (!m.isDead() && !p.isDead())
    {
        cout << "(r)БЕЖАТЬ / (f)СРАЖАТЬСЯ: ";
        char input;
        cin >> input;
        cin.ignore(32767, '\n');

        if (input == 'r')
        {
            if (getRandomNumber(1, 2) == 1)
            {
                cout << "Удалось сбежать.\n";
                return;
            }
            else
            {
                cout << "ТЕБЯ настигли.\n";
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

void healthDamage(Player& p)
{
    cout << "Здоровье: " << p.getHealth() << ". Урон: " << p.getDamage() << "." << endl;
}

void saveTheCiri(Player& p, int& count)
{
    if (getRandomNumber(1, 5) == 2)
    {
        cout << "\nСПАСИ ЦИРИ!";
        Monster m("Дикая охота", 20, 10, 100);
        while (!p.isDead() && !m.isDead())
            fightMonster(p, m);
        
        ++count;
    }
}

char inputQuest()
{
    cout << "\nЛютику требуется ТВОЯ помощь!!!\n";

    char input;
    do {
        cout << "Помочь? (y)ОХ УЖ ЭТОТ ЛЮТИК / (n)НИ ЗА ЧТО: ";
        cin >> input;
        cin.ignore(32767, '\n');
    } while (input != 'y' && input != 'n');

    return input;
}

void quest(Player& p)
{
    inputQuest();

    cout << p.getName() << " решил помочь!\n";
    cout << "Помоги завоевать сердце принцессы. Убей Короля.\n" << endl;
    Monster king("Король", 50, 7, 0);

    while (!p.isDead() && !king.isDead())
    {
        attackPlayer(p, king);
        attackMonster(king, p);

        if (king.getHealth() <= 10)
        {
            cout << '\n' << p.getName() << " давай договоримся. " <<
                    king.getName() << " протягивает 1000 крон." << endl;

            if (takeTheKingMoney() == 'y')
            {
                cout << "\nТЫ взял деньги.\n";
                p.addGold(1000);
                cout << "Лютик огорчен.\n";
                return;
            }
            else
            {
                cout << "\nКолдун еб***й. " << king.getName() << " использовал магию и сбежал.\n" <<
                        "Как сказать Лютику, что это была не принцесса?..." << endl;
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
        cin.ignore(32767, '\n');
    } while (input != 'y' && input != 'n');

    return input;
}