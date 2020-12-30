
#ifndef DECK_H_
#define DECK_H_
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include "info.h"

#define NUM_CARDS 52
#define PER_PLAYER 13

class Deck {
	//
	std::vector<CardInfo> deck;
	//Value for determining shuffle
	int seed;
public:
	//Creates the initial, unshuffled deck and initializes seed
	Deck(int seed);
	//Shuffles deck
	void shuffle();
	//Deals 13 cards from the deck to the player with the given id
	std::vector<CardInfo> getDeal(size_t playerId);
	//Prints out all the cards in the deck
	std::string allDeckStr();
	//Converts the string attributes of a card to CardInfo form
	CardInfo static stringToCardInfo(std::string str);
	//Converts the CardInfo attributes of a card to string form
	static std::string cardInfoToString(CardInfo cInfo);
	//Converts the card number of a card from CardInfo form to string form
	static std::string cardNumToString(CardInfo cInfo);
	//Finds and stores the valid card plays by checking each of the suits of the cards currently on the table
	static std::vector<CardInfo> getValidCards();
	//Returns true if given card CardInfo can be found in the vector of cards
	static bool isCardIncluded(std::vector<CardInfo>, CardInfo);
	//Inserts a card to its respective suit of cards already on the table in order
	static void addcardToTable(CardInfo);

};

#endif /* DECK_H_ */
