#include <iostream>
#include <ctime>
#include <string>

using namespace std;

int getRandomNumber(int min, int max);

class Creature
{
protected:
    string name;
    int health;
    int damage;
    int gold;

public:
    Creature(string name, int health, int damage, int gold)
        : name(name), health(health), damage(damage), gold(gold) {}

    const string& getName()
    { 
        return name; 
    }

    int getHealth()
    { 
        return health; 
    }

    int getDamage()
    {
        return damage; 
    }

    int getGold()
    { 
        return gold; 
    }

    void reduceHealth(int health)
    {
        this->health -= health;
    }

    bool isDead()
    {
        return health <= 0;
    }

    void addGold(int gold)
    {
        this->gold += gold;
    }
};

class Player : public Creature
{
private:
    int level = 1;

public:
    Player(string name)
        : Creature(name, 10, 1, 0) {}

    void levelUp()
    {
        ++level;
        ++damage;
        ++health;
    }

    int getLevel()
    { 
        return level;
    }

    bool hasWon()
    { 
        return level >= 20; 
    }
};

class Monster : public Creature
{
private:
    enum Type
    {
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
    Monster(Type type)
        : Creature(monsterData[type].name, monsterData[type].health, monsterData[type].damage, monsterData[type].gold) {}
   
    Monster(string name, int health, int damage, int gold) 
        : Creature(name, health, damage, gold) {}

    static Monster getRandomMonster()
    {
        int num = getRandomNumber(0, MAX_TYPES - 1);
        return Monster(static_cast<Type>(num));
    }
};

Monster::MonsterData Monster::monsterData[Monster::MAX_TYPES]
{
    {"Василиск",20,10,100},
    {"Гуль",5,4,25},
    {"Утопец",2,1,10},
    {"Призрак",3,2,15},
    {"Виверна",10,8,50}
};

void attackPlayer(Player& p, Monster& m);
void attackMonster(Monster& m, Player& p);
void fightMonster(Player& p);
void healthDamage(Player& p);
void quest(Player& p);
char inputQuest();
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

        while (!player.isDead() && !player.hasWon())
            fightMonster(player);

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

int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

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
        cout << "В кошельке: " << m.getGold() << " крон.\n";
        p.addGold(m.getGold());
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

void fightMonster(Player& p)
{
    Monster m = Monster::getRandomMonster();

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

void healthDamage(Player& p)
{
    cout << "Здоровье: " << p.getHealth() << ". Урон: " << p.getDamage() << "." << endl;
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