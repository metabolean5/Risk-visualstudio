#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <iterator>
#include <iostream>
#include "cards.h"
#include "player.h"
#include "lib1.h"



using namespace std;

Deck::Deck(int nb){
	
	for (int i = 0 ; i < nb ; i++)
		countries.emplace_back();
	
}

Card::Card(const Card &oldCard) {
	this->name = oldCard.name;
	this->type = oldCard.type;
}

Card Deck::draw() {
	//vector<Card> countries;
	//generate random number between 1 and the number of countries
	srand(int(time(NULL)));
	int cardDrawn = rand() % Deck::countries.size();
	Card drawnCard = countries.at(cardDrawn);
	countries.erase(countries.begin() + cardDrawn);
	return drawnCard;
}
int Deck::getSize() {
	return countries.size();
}

Card::Card(string newName, int newType) : name(newName),type(newType){
	
}
Card::Card() {}

Card Deck::getCountry(int i) {
	return countries.at(i);
}

string Card::getName() {
	return name;
}

int Card::getType() {
	if (type == 0){
		return 0;
	}
	else if (type == 1) {
		return 1;
	}
	else {
		return 2;
	}
}
Hand::Hand() {

}
Hand::Hand(vector<Card> newHand) {
	playerHand = newHand;
}

Card Hand::getAt(int i) {
	return playerHand.at(i);
}

void Deck::insertCard(Card newCard) {
	//put new card somewhere in the deck
	countries.push_back(newCard);
	cout << "deck size " << countries.size() << endl;

}


//keeps track of how many armies are being given out.
int Sets::calculateArmies() {
	if (numberOfSets == 0) {
		numberOfSets++;
		return 4;
	}else if (numberOfSets <= 5) {
		numberOfSets++;
		return 2* numberOfSets +2;
	}
	else if (numberOfSets == 5) {
		numberOfSets++;
		return 15;
	}
	else{
		numberOfSets++;
		return 5* numberOfSets -10;
	}
}

int Hand::exchange(Deck deck1) {
	int infantry = 0;
	int cavalry = 0;
	int artillery = 0;
	vector<Card> *PHPointer;
	PHPointer = &playerHand;

	if (playerHand.size() < 3) {
		return 0;
	}
	//counts the number of each card
	for (int i = 0; i<int(PHPointer->size()); i++) {
		if (PHPointer->at(i).getType() == 0) {
			infantry++;
		}
		else if (int(PHPointer->at(i).getType()) == 1) {
			cavalry++;
		}
		else if (PHPointer->at(i).getType() == 2) {
			artillery++;
		}
	}
	//finds sets to trade in
	if (infantry>=3) {
		int handedIn = 0;
		for (int i = 0; i<int(PHPointer->size())&&handedIn < 3; i++) {
			if (PHPointer->at(i).getType() == 0) {

				deck1.insertCard(Card(PHPointer->at(i)));
				PHPointer->erase(PHPointer->begin() + i);
				i--;
				handedIn++;
			}
		}
		return Sets::calculateArmies();
	}
	else if (cavalry >= 3) {
		int handedIn = 0;
		for (int i = 0; i<int(PHPointer->size()) && handedIn < 3; i++) {
			if (PHPointer->at(i).getType() == 1) {

				deck1.insertCard(Card(PHPointer->at(i)));
				PHPointer->erase(PHPointer->begin() + i);
				i--;
				handedIn++;
			}
		}
		return Sets::calculateArmies();
	}
	else if (artillery >= 3) {
		int handedIn = 0;
		for (int i = 0; i<int(PHPointer->size()) && handedIn < 3; i++) {
			if (PHPointer->at(i).getType() == 2) {
				deck1.insertCard(Card(PHPointer->at(i)));
				PHPointer->erase(PHPointer->begin() + i);
				i--;
				handedIn++;
			}
		}
		return Sets::calculateArmies();
	}
	else if (infantry >= 1 && cavalry >= 1 && artillery >= 1) {
		for (int i = 0; i<int(PHPointer->size()); i++) {
			if (PHPointer->at(i).getType() == 0) {
				deck1.insertCard(Card(PHPointer->at(i)));
				PHPointer->erase(PHPointer->begin() + i);
				break;
			}
		}for (int i = 0; i<int(PHPointer->size()); i++) {
			if (PHPointer->at(i).getType() == 1) {
				deck1.insertCard(Card(PHPointer->at(i)));
				PHPointer->erase(PHPointer->begin() + i);
				break;
			}
		}for (int i = 0; i<int(PHPointer->size()); i++) {
			if (PHPointer->at(i).getType() == 2) {
				deck1.insertCard(Card(PHPointer->at(i)));
				PHPointer->erase(PHPointer->begin() + i);
				break;
			}
		}
		return Sets::calculateArmies();
	}
	return 0;
}

void Hand::addCardToHand(Card newCard) {
	playerHand.push_back(newCard);
}

int Hand::getHandSize() {
	return playerHand.size();
}