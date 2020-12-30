#include <memory>
#include <iostream>
#include <sstream>
#include <string>
#include "inputhandler.h"
#include "deck.h"
#include <exception>

using namespace std;

InputHandler::InputHandler() {
	play = std::make_shared<PlayCard>();
	discard = std::make_shared<DiscardCard>();
	rageQuit = std::make_shared<RageQuit>();
	deck = std::make_shared<DeckPrint>();

}

PlayInfo InputHandler::parseInputCmd() {
	PlayInfo info;
	string playType;
	string card;

	std::cin >> playType;

	if (!playType.empty()) {
		if (playType.compare("play") == 0) {
			std::cin >> card;
			info.playType = PlayType::Play;
			info.cInfo = Deck::stringToCardInfo(card);
		} else if (playType.compare("discard") == 0) {
			std::cin >> card;
			info.playType = PlayType::Discard;
			info.cInfo = Deck::stringToCardInfo(card);
		} else if (playType.compare("ragequit") == 0) {
			info.playType = PlayType::RageQuit;
		} else if (playType.compare("quit") == 0) {
			info.playType = PlayType::Quit;
			throw q{};
		} else if (playType.compare("deck") == 0) {
			info.playType = PlayType::Deck;
		} else {
			info.playType = PlayType::ERROR;
			std::cout << "PlayType::ERROR\n";
		}
	}
	return info;

}
std::string getPlayInfo(PlayInfo pi) {
	stringstream ss;
	if (pi.playType == PlayType::Play) {
		ss << "play ";
	}
	ss << Deck::cardInfoToString(pi.cInfo);
	return ss.str();
}

Command* InputHandler::handleInput(Player *player) {

	std::string input;
	PlayInfo playInfo;
	try {
		while (true) {
			try {
				playInfo = parseInputCmd();
				if (playInfo.playType == PlayType::ERROR || playInfo.cInfo.type == CardType::ERROR) {
					std::cout << "Not a legal play." << std::endl;
					continue;
				}
				if (player->hasLegalPlays() && playInfo.playType == PlayType::Discard) {
					std::cout << "You have a legal play. You may not discard." << std::endl;
					continue;
				}
				if (player->isValidPlay(playInfo)) {
					break;
				} else {
					//This is not a legal play.
					std::cout << "This is not a legal play." << std::endl;
				}
			} catch (exception &e) {

				cout << e.what() << '\n';
			}
		}
	} catch (ios::failure &e) {
		std::cerr << e.what() << std::endl;
	}

	try {
		switch (playInfo.playType) {
		case PlayType::Play:
			play->setCardInfo(playInfo.cInfo);
			return play.get();
			break;
		case PlayType::Discard:
			discard->setCardInfo(playInfo.cInfo);
			return discard.get();
			break;
		case PlayType::RageQuit:
			return rageQuit.get();
			break;
		case PlayType::Deck:
			return deck.get();
			break;
		case PlayType::Quit:
			throw q{};
			break;
		default:
			return nullptr;
		}
	} catch (exception &e) {
		std::cerr << e.what() << std::endl;
	}

	// Nothing get, so do nothing.
	return nullptr;;
}
