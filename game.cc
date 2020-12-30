#include <iostream>
#include <string>
#include "game.h"

Game::Game(int seed, int _nPlayers) {
	initSeed = seed;
	nPlayers = _nPlayers;
	deck = std::make_shared<Deck>(seed);
	inputHandler = std::make_shared<InputHandler>();
	rounds = 0;
}

void Game::initGame() {

	initPlayers(nPlayers);
	deck->shuffle();
	initDealing();
}

void Game::newRound() {
	int i = 0;
	for (i = 0; i < 4; i++) {
		cardsOnTable[i].clear();
	}
	for (auto pl : players) {
		pl->newRound();
	}
	deck->shuffle();
	initDealing();
}

void Game::playGame() {

	while (true) {
		if (isGameOver()) {
			//print winners
			std::cout << gameResults();
			break;
		} else {
			if (rounds > 0) {
			newRound();
			}
		}
		firstPlayerPlay();
		while (true) {
			if (isGameOver()) {
				break;
			}
			if (isRoundEnd()) {
				std::cout << roundResults();
				rounds++;
				break;
			}
			std::cout << getCardsOnTable();
			std::cout << actor->prePlay();
			if (actor->isComputer()) {
				// Computer player
				actor->autoPlay();
				actor = getNextPlayer();
				continue;
			} else {
				// Human player
				Command *cmd = inputHandler->handleInput(actor);
				cmd->execute(actor);

				if (cmd->getNext()) {
					actor = getNextPlayer();
				}
			}

		}
	}

}

void Game::initPlayers(size_t nPlayers) {
	size_t i = 0;

	char cc;
	while (i < nPlayers) {
		try {
			std::cout << "Is Player" << i + 1
					<< " a human (h) or a computer (c)?" << std::endl;
			std::cin >> cc;
			if (cc == 'h') {
				addPlayer(PlayerType::Human, i);
			} else if (cc == 'c') {
				addPlayer(PlayerType::Computer, i);
			} else if (cc == 's') {
				addPlayer(PlayerType::Senior, i);
			} else if (cc == 'p') {
				addPlayer(PlayerType::Principal, i);
			} else {

				//throw;
				std::cout << "This is not a legal player type. [human<h>|computer<x>|senior<s>|principal<p>]" << std::endl;
				continue;
			}
			i++;
		} catch (std::invalid_argument &e) {
			std::cerr << e.what() << std::endl;
		}
	}
}

void Game::addPlayer(PlayerType pType, size_t idx) {
	std::shared_ptr<Player> player(new Player(pType, idx));
	player->setDeckPtr(deck.get());
	players.push_back(player);

}
void Game::initDealing() {
	int id = 0;
	//deck->shuffle();
	for (std::shared_ptr<Player> player : players) {
		player->initCardInfoInHand(deck->getDeal(id));
		id++;
	}
}

Player* Game::getFirstPlayer() {
	for (std::shared_ptr<Player> player : players) {
		if (player->has7S()) {
			return player.get();
		}
	}
	return nullptr;
}

Player* Game::getNextPlayer() {
	int id = actor->getId();
	size_t nextId = (id == nPlayers - 1) ? 0 : id + 1;
	return players.at(nextId).get();
}

std::string Game::getPlayersInfo() {
	std::stringstream ss("");
	for (auto player : players) {
		ss << player->getPlayerInfo();
	}
	return ss.str();
}

std::string Game::getCardsOnTable() {

	std::string typeStr[4] = { "Clubs:", "Diamonds:", "Hearts:", "Spades:" };
	int i = 0;
	std::stringstream ss("");
	ss << "Cards on the table:" << std::endl;
	for (i = 0; i < 4; i++) {
		ss << typeStr[i];
		for (auto cInfo : cardsOnTable[i]) {
			ss << " " << Deck::cardNumToString(cInfo);
		}
		ss << std::endl;
	}
	return ss.str();
}

std::string Game::getDeckStr() {
	return deck->allDeckStr();
}

bool Game::isRoundEnd() {
	// no player has cards left
	for (auto player: players) {
		if (player->hasCardsLeft()) {
			return false;
		}
	}
	return true;
}

bool Game::isGameOver() {
	for (auto player: players) {
		if (player->getScores() >= 80 ) {
			return true;
		}
	}
	return false;
}

std::string Game::gameResults() {
	std::stringstream ss("");
	std::vector<Results> vResults;
	Results rl;
	for (auto player : players) {
		rl.score = player->getScores();
		rl.id = player->getId();
		vResults.push_back(rl);
		ss << player->printResults();
	}
	std::sort(vResults.begin(), vResults.end(), std::less<Results>());
	int winScore = vResults.at(0).score;
	ss << "Player" << vResults.at(0).id + 1 << " wins!" << std::endl;
	for (int i = 1; i < 4; i++) {
		if (vResults.at(i).score == winScore) {
			ss << "Player" << vResults.at(i).id + 1 << " wins!" << std::endl;
		}
	}
	return ss.str();
}

std::string Game::roundResults() {
	std::stringstream ss("");
	std::vector<Results> vResults;
	Results rl;
	for (auto player : players) {
		rl.score = player->getScores();
		rl.id = player->getId();
		vResults.push_back(rl);
		ss << player->printResults();
	}
	return ss.str();
}

void Game::firstPlayerPlay() {
	actor = getFirstPlayer();
	std::cout << "A new round begins. It’s Player" << actor->getId() + 1
			<< "’s turn to play." << std::endl;

	std::cout << getCardsOnTable();
	std::cout << actor->prePlay();

	CardInfo cInfo;
	cInfo.num = 7;
	cInfo.type = CardType::S;
	actor->play(cInfo);
	actor = getNextPlayer();

}
