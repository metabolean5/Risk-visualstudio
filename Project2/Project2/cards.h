#pragma once


#include <vector>
#include <string>


namespace Sets {
	int calculateArmies();
	static int numberOfSets;
}



using namespace std;




class Card {
public:
	Card(const Card &oldCard);
	Card();
	Card(string newName, int newType);
	string getName();
	int getType();
private:
	string name;
	int type; //0 - infantry, 1 - cavalry, 2 - artillery
};

class Deck {
public:
	Deck(int nb);
	Card draw();
	int getSize();
	void insertCard(Card newCard);
	Card getCountry(int i);
private:
	vector<Card> countries;

};

class Hand {
public:
	Hand();
	Hand(vector<Card> newHand);
	int exchange(Deck deck1); //tries to exchange cards for troops
	void addCardToHand(Card newCard); //put a card in the player hand
	int getHandSize();
	Card getAt(int i);
private:
	vector<Card> playerHand;
};