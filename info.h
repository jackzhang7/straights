#ifndef _INFO_H
#define _INFO_H

#include <cstddef>
#include <vector>

// State of the cell i.e. either dead or alive.
enum class PlayerType { Computer, Human, Senior, Principal };
enum class PlayType { Play, Discard, RageQuit, Quit, Deck, ERROR};
enum class CardType {C, D ,H ,S, ERROR};

// Information for the cell to return i.e. its state (Alive/Dead) and position in grid.
#define MAX_SCORE 80
#define NUM_PLAYERS 4


struct PlayerInfo {
	PlayerType playerType;
    size_t id;
    int curScores;
    std::vector<int> preScores;
};

struct CardInfo {
	CardType type;
    size_t num;
    bool operator <(const CardInfo & ci) const {
    	return (num < ci.num);
    }
    bool operator ==(const CardInfo & ci) const {
        return (num == ci.num && type == ci.type);
    }
    bool operator >(const CardInfo & ci) const {
    	return (num > ci.num);
    }

};

const CardType CTYPES[] = {CardType::C, CardType::D, CardType::H, CardType::S};


struct PlayInfo {
	PlayType playType;
	CardInfo cInfo;

};
extern std::vector<CardInfo> cardsOnTable[NUM_PLAYERS];

struct Results {
	int id;
	int score;

	bool operator <(const Results & rl) const {
	    return (score < rl.score);
	}
};

//To handle quit exception
class q {};

#endif
