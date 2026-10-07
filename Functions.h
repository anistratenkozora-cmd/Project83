#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Structs.h"

void recruitHero(PartyList& party, Character newHero);
int findHeroIndex(const PartyList& party, const char* searchName);
Character getHeroByName(const PartyList& party, const char* searchName);
void printParty(const PartyList& party);
bool levelUp(PartyList& party, const char* searchName);
bool equipWeapon(PartyList& party, const char* searchName, Item newweapon);
bool damageHero(PartyList& party, const char* searchName, int amount);
bool healHero(PartyList& party, const char* searchName, int amount);
void savePartyToFile(const PartyList& party, const char* filename);
void loadPartyFromFile(PartyList& party, const char* filename);

#endif