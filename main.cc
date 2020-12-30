#include <iostream>
#include <string>
#include "game.h"
#include "deck.h"

using namespace std;

#define DEFAULT_SEED 100

int main(int argc, char *argv[]) {
	int seed;
	// Check the number of parameters
	if (argc < 2) {
		std::cerr << "No seed input, use default seed 100." << std::endl;
		seed = DEFAULT_SEED;
	} else {

		try {
			seed = std::stoi(argv[1]);
		} catch (std::invalid_argument &e) {
			std::cerr << "The seed input (" << argv[1] << ") is not a integer, use default seed 100." << std::endl;
			seed = DEFAULT_SEED;
		}
	}
	try {
		int nPlayers = NUM_PLAYERS;
		cin.exceptions(ios::eofbit | ios::failbit);
		std::shared_ptr<Game> game(new Game(seed, nPlayers));

		game->initGame();
		game->playGame();
	} catch (q &i) {
		return EXIT_SUCCESS;
	}
} // main
