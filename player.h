/*
 * player.h
 *
 *  Observer
 *
 */

#ifndef PLAYER_H_
#define PLAYER_H_
#include <set>
#include <vector>
#include <sstream>

//#include "deck.h"
#include "info.h"
#include "deck.h"

// The Player class has actual play operations. It plays
// the role of a receiver: all commands end up delegating
// execution to the player's methods.

class Player {

	PlayerInfo info;
	std::vector<CardInfo> cardsInHand;
	std::vector<CardInfo> cardsDiscarded;
	Deck *deck;
	void removeCardIHand(CardInfo cInfo);
public:
	//Constructor
	Player(PlayerType, size_t idx);
	//
	void initCardInfoInHand(std::vector<CardInfo>);
	//Returns the player's hand cards
	std::vector<CardInfo> getCardsInHand();
	//Returns the cards in a player's hand and their valid plays
	std::string prePlay();
	//Removes a card from the player's hand and adds it to cardsOnTable and outputs the corresponding message
	void play(CardInfo cardInfo);
	//Removed card from player's hand and pushes it to cardsDiscarded
	void discard (CardInfo cardInfo);
	//Plays for the players that are not human
	void autoPlay();
	//Changes player type to computer and outputs appropriate message
	void rageQuit();
	//Prints the cards in the deck
	std::string deckPrint();
	//Returns player's id
	size_t getId();
	//Returns true if player is a computer
	bool isComputer();
	//Returns true if a given play is valid
	bool isValidPlay(PlayInfo);
	//Returns true if the player has 7 of Spades in their hand
	bool has7S();
	//Returns true if the player still has hand cards
	bool hasCardsLeft();
	//Sets deck to shared_ptr _deck
	void setDeckPtr(Deck * deck);
	//Returns information about current player, including hand cards, discarded cards, score, type
	std::string getPlayerInfo();
	//Returns the total score of the current player
	int getScores();
	//Sets curScore to the number of cards that were just discarded
	void setCurScores();
	//Sets presScore to given int value
	void setPreScores(int);
	//Initiates a new round
	void newRound();
	//Prints the player's score
	std::string printResults();
	//Returns true if the player has at least one legal play
	bool hasLegalPlays();
	//Plays largest legal card and deletes smallest card in hand
	void principalPlay();
	//Plays largest legal card
	void seniorPlay();
	//Returns a vector of the player's legal plays
	std::vector<CardInfo> getLegalCardsInHand();
};

#endif /* PLAYER_H_ */
