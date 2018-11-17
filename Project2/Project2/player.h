#pragma once
#include <vector>
#include "dice.h"
#include "cards.h"
#include "lib1.h"





class Player
{
public:
	void reinforce();
	void attack();
	void fortify();
	Player();
	int getSides();
	int getCountrynb();
	string get1stCountryName();
	int getHandnb();
	void addCountry(Country c);

private:
	vector<Country> Countries;
	vector<Card> Hand;
	dice Dice;
};