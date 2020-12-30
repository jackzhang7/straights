/*
 * game.h
 *
 *  Using singleton design pattern for global properties
 *
 */

#ifndef GAME_H_
#define GAME_H_

#include <vector>
#include <memory>
#include "info.h"
#include "deck.h"
#include "inputhandler.h"

// The Game class sets up objects relations. It acts as a game controller (Sender)
// It gets actor's command from InputHandler, and creates a command object and executes it.

class Game {
	Player *actor;
	int initSeed;
	int rounds;
	int nPlayers;

	std::shared_ptr<Deck> deck;
	std::shared_ptr<InputHandler> inputHandler;

	//Log *log_;
	//TextPlayer *textPlayer_;
	//AudioPlayer *audioPlayer_;
	//GraphicsPlayer *graphicsPlayer_;

	std::vector<std::shared_ptr<Player>> players;

public:
	Game(int seed, int nPlayers);
	//
	void addPlayer(PlayerType, size_t idx);
	void initPlayers(size_t nPlayers);
	void initDealing();
	//Starts the game, initializing players, shuffling cards, and dealing out cards
	void initGame();
	//Starts a new round
	void newRound();
	//Starts the game
	void playGame();
	//Returns true if conditions for ending the game are met
	bool isGameOver();
	//Returns true if conditions for ending the round are met
	bool isRoundEnd();
	//Returns the first player, the player who has 7 of spades
	Player* getFirstPlayer();
	//Returns the next player whose turn is next
	Player* getNextPlayer();
	std::string getDeckStr();
	std::string getPlayersInfo();
	std::string getCardsOnTable();
	std::string gameResults();
	std::string roundResults();
	void firstPlayerPlay();
};

#endif /* GAME_H_ */
