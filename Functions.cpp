#include <iostream>
#include <cstring>
#include <fstream>
#include "Functions.h"

using namespace std;

void recruitHero(PartyList& party, Character newHero) {
    Character* newHeroes = new Character[party.size + 1];
    for (int i = 0; i < party.size; i++) {
        newHeroes[i] = party.heroes[i];
    }
    newHeroes[party.size] = newHero;
    delete[] party.heroes;
    party.heroes = newHeroes;
    party.size = party.size + 1;
}

int findHeroIndex(const PartyList& party, const char* searchName) {
    for (int i = 0; i < party.size; i++) {
        if (strcmp(party.heroes[i].name, searchName) == 0) {
            return i;
        }
    }
    return -1;
}

Character getHeroByName(const PartyList& party, const char* searchName) {
    int index = findHeroIndex(party, searchName);
    if (index != -1) {
        return party.heroes[index];
    }
    else {
        Character emptyHero;
        emptyHero.level = -1;
        return emptyHero;
    }
}

void printParty(const PartyList& party) {
    for (int i = 0; i < party.size; i++) {
        cout << "Ім'я: " << party.heroes[i].name << endl;
        cout << "Клас: " << party.heroes[i].classType << endl;
        cout << "Рівень: " << party.heroes[i].level << endl;
        cout << "HP: " << party.heroes[i].hp << endl;
        cout << "Сила/Спритність/Інтелект: " << party.heroes[i].stats.strength << " / "
            << party.heroes[i].stats.agility << " / " << party.heroes[i].stats.intelligence << endl;
        cout << "Зброя: " << party.heroes[i].weapon.name << " (Сила: " << party.heroes[i].weapon.power << ")" << endl;
        cout << "-----------------------------------" << endl;
    }
}

bool levelUp(PartyList& party, const char* searchName) {
    int index = findHeroIndex(party, searchName);
    if (index != -1) {
        party.heroes[index].level += 1;
        party.heroes[index].hp += 10;
        return true;
    }
    return false;
}

bool equipWeapon(PartyList& party, const char* searchName, Item newweapon) {
    int index = findHeroIndex(party, searchName);
    if (index != -1) {
        party.heroes[index].weapon = newweapon;
        return true;
    }
    return false;
}

bool damageHero(PartyList& party, const char* searchName, int amount) {
    int index = findHeroIndex(party, searchName);
    if (index != -1) {
        party.heroes[index].hp -= amount;
        if (party.heroes[index].hp < 0) {
            party.heroes[index].hp = 0;
        }
        return true;
    }
    return false;
}

bool healHero(PartyList& party, const char* searchName, int amount) {
    int index = findHeroIndex(party, searchName);
    if (index != -1) {
        party.heroes[index].hp += amount;
        if (party.heroes[index].hp >= 100) {
            party.heroes[index].hp = 100;
        }
        return true;
    }
    return false;
}

void savePartyToFile(const PartyList& party, const char* filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cout << "Помилка відкриття файлу для збереження!" << endl;
        return;
    }

    outFile << party.size << endl;

    for (int i = 0; i < party.size; i++) {
        outFile << party.heroes[i].name << endl;
        outFile << party.heroes[i].classType << endl;
        outFile << party.heroes[i].level << endl;
        outFile << party.heroes[i].hp << endl;
        outFile << party.heroes[i].stats.strength << endl;
        outFile << party.heroes[i].stats.agility << endl;
        outFile << party.heroes[i].stats.intelligence << endl;
        outFile << party.heroes[i].weapon.name << endl;
        outFile << party.heroes[i].weapon.power << endl;
    }

    outFile.close();
    cout << "Табір успішно збережено у файл: " << filename << endl;
}

void loadPartyFromFile(PartyList& party, const char* filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "Файл не знайдено або не вдалося відкрити!" << endl;
        return;
    }

    delete[] party.heroes;
    party.heroes = nullptr;
    party.size = 0;

    int loadedSize = 0;
    inFile >> loadedSize;
    inFile.ignore();

    for (int i = 0; i < loadedSize; i++) {
        Character tempHero;

        inFile.getline(tempHero.name, 100);
        inFile.getline(tempHero.classType, 50);
        inFile >> tempHero.level >> tempHero.hp;
        inFile >> tempHero.stats.strength >> tempHero.stats.agility >> tempHero.stats.intelligence;
        inFile.ignore();
        inFile.getline(tempHero.weapon.name, 50);
        inFile >> tempHero.weapon.power;
        inFile.ignore();

        recruitHero(party, tempHero);
    }

    inFile.close();
    cout << "Табір успішно завантажено з файлу: " << filename << endl;
}