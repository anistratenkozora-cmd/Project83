#ifndef TYPES_H
#define TYPES_H

struct Stats {
    int strength;
    int agility;
    int intelligence;
};

struct Item {
    char name[50];
    int power;
};

struct Character {
    char name[100];
    char classType[50];
    int level;
    int hp;
    Stats stats;
    Item weapon;
};

struct PartyList {
    Character* heroes = nullptr;
    int size = 0;
};

#endif