#include <vector>
#include "player.h"
#include "cards.h"
#include "lib1.h"




	Player::Player() {
		//Countries.push_back(Country("Canada"));
    	Hand.push_back(Card());
		Dice = dice(6);
  }
	int Player::getSides() {
		int n = Dice.getS();
		return n;
	}
	
	int Player::getCountrynb() {
		int n = Countries.size();
		return n;
	}
	
	string Player::get1stCountryName() {
		string n = Countries.at(0).name;
		return n;
	}
	
	
	int Player::getHandnb() {
		int n = Hand.size();
		return n;
	}
	void Player::addCountry(Country c) {
		Countries.push_back(Country(c.name));
	}

