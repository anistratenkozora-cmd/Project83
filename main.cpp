#include <iostream>
#include <windows.h>
#include "Functions.h"

using namespace std;

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    PartyList myParty;

    Character hero1 = { "Артас", "Воїн", 5, 100, {50, 30, 20}, { "Екскалібур", 150 } };
    recruitHero(myParty, hero1);

    cout << "--- Початковий стан табору ---" << endl;
    printParty(myParty);

    levelUp(myParty, "Артас");
    cout << "\n--- Після підвищення рівня ---" << endl;
    printParty(myParty);

    savePartyToFile(myParty, "camp_save.txt");

    delete[] myParty.heroes;
    myParty.heroes = nullptr;
    myParty.size = 0;

    PartyList loadedParty;
    loadPartyFromFile(loadedParty, "camp_save.txt");

    cout << "\n--- Завантажений табір із файлу ---" << endl;
    printParty(loadedParty);

    delete[] loadedParty.heroes;

    return 0;
}