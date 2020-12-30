#include "player.h"

void Player::initCardInfoInHand(std::vector<CardInfo> vCardInfo) {
	cardsInHand.empty();
	for (CardInfo cInfo : vCardInfo) {
		cardsInHand.push_back(cInfo);
	}
}

Player::Player(PlayerType pType, size_t idx) {
	info.id = idx;
	info.playerType = pType;
	info.curScores = 0;
}
std::vector<CardInfo> Player::getCardsInHand() {
	return cardsInHand;
}

void Player::removeCardIHand(CardInfo cInfo) {
	//Remove card from cards in Hand
	int i = 0;
	for (auto ci : cardsInHand) {
		if (ci == cInfo) {
			cardsInHand.erase(cardsInHand.begin() + i);
		}
		i++;
	}
}
void Player::autoPlay() {
	switch (info.playerType) {
	case PlayerType::Senior:
		seniorPlay();
		break;
	case PlayerType::Principal:
		principalPlay();
		break;
	default:
		//Computer play
		std::vector<CardInfo> validCards = Deck::getValidCards();
		for (auto cInfo : cardsInHand) {
			if (Deck::isCardIncluded(validCards, cInfo)) {
				play(cInfo);
				return;
			}
		}
		if (!cardsInHand.empty()) {
			discard(cardsInHand.at(0));
		}
	}
}

void Player::play(CardInfo cInfo) {
	//Remove card from cards in Hand
	removeCardIHand(cInfo);
	//Add cards into cards on table
	Deck::addcardToTable(cInfo);
	std::cout << "Player" << info.id + 1 << " plays " << Deck::cardInfoToString(cInfo) << "." << std::endl;
}
void Player::discard(CardInfo cInfo) {
	//Remove card from cards in Hand
	removeCardIHand(cInfo);
	//Add cards to discard
	cardsDiscarded.push_back(cInfo);
	std::sort(cardsDiscarded.begin(), cardsDiscarded.end(),
			std::less<CardInfo>());
	std::cout << "Player" << info.id + 1 << " discards " << Deck::cardInfoToString(cInfo) << "." << std::endl;
}
void Player::rageQuit() {
	info.playerType = PlayerType::Computer;
	std::cout << "Player" << info.id + 1 << " ragequits. A computer will take over now. " << std::endl;
}
std::string Player::deckPrint() {
	return deck->allDeckStr();

}
//void notify();
size_t Player::getId() {
	return info.id;
}

void Player::setDeckPtr(Deck *_deck) {
	deck = _deck;
}

bool Player::isValidPlay(PlayInfo pInfo) {
	std::vector<CardInfo> validCards = Deck::getValidCards();
	std::vector<CardInfo> vCards = getLegalCardsInHand();
	switch (pInfo.playType) {
	case PlayType::Play:



		if (Deck::isCardIncluded(vCards, pInfo.cInfo)) {
			return true;
		}
		break;
	case PlayType::Discard:
		if (Deck::isCardIncluded(cardsInHand, pInfo.cInfo)) {
			return true;
		}
		break;
	case PlayType::Deck:
	case PlayType::RageQuit:
	case PlayType::Quit:
		return true;
	default:
		throw;
	}

	return false;
}
bool Player::has7S() {
	for (CardInfo cInfo : cardsInHand) {
		if (cInfo.num == 7 && cInfo.type == CardType::S) {
			return true;
		}
	}
	return false;
}

bool Player::isComputer() {
	if (info.playerType != PlayerType::Human) {
		return true;
	}
	return false;
}

std::string Player::getPlayerInfo() {
	std::stringstream ss("");
	ss << "Id: " << info.id;
	ss << " Type:";
	if (info.playerType == PlayerType::Human) {
		ss << "Human";
	} else {
		ss << "Computer";
	}
	ss << " Score: " << info.curScores << std::endl;
	ss << "In Hand: ";
	for (auto cInfo : cardsInHand) {
		ss << Deck::cardInfoToString(cInfo) << " ";
	}
	ss << std::endl << "Discarded :";
	for (auto cInfo : cardsDiscarded) {
		ss << Deck::cardInfoToString(cInfo) << " ";
	}
	ss << std::endl;
	return ss.str();
}

std::string Player::prePlay() {
	std::stringstream ss("");
	ss << "Your hand:";
	for (auto cInfo : cardsInHand) {
		ss << " " << Deck::cardInfoToString(cInfo);
	}
	ss << std::endl;
	ss << "Legal plays:";

	for (auto cInfo : cardsInHand) {
		PlayInfo pInfo;
		pInfo.playType = PlayType::Play;
		pInfo.cInfo = cInfo;
		isValidPlay(pInfo);
		if (this->isValidPlay(pInfo)) {
			ss << " " << Deck::cardInfoToString(cInfo);
		}
	}
	ss << std::endl;
	setCurScores();
	return ss.str();
}

bool Player::hasCardsLeft() {
	return !cardsInHand.empty();
}

int Player::getScores() {
	int sum = 0;
	for (auto i : info.preScores) {
		sum += i;
	}
	setCurScores();
	return sum + info.curScores;
}

void Player::setCurScores() {
	info.curScores = 0;
	for (auto cInfo: cardsDiscarded) {
		info.curScores += cInfo.num;
	}
}


void Player::newRound() {
	int sum = 0;
	for (CardInfo ci : cardsDiscarded) {
		sum += ci.num;
	}
	info.preScores.push_back(sum);
	info.curScores = 0;
	cardsDiscarded.clear();
	cardsInHand.clear();
}

std::string Player::printResults() {
	std::stringstream ss("");
	ss << "Player" << info.id + 1 << "'s discards: ";

	for (auto cInfo : cardsDiscarded) {
		ss << Deck::cardInfoToString(cInfo) << " ";
	}
    ss << std::endl;
    ss << "Player" << info.id + 1 << "'s score: ";
    int sum = 0;
    for (auto ps : info.preScores) {
    	ss << ps << " + ";
    	sum += ps;
    }
    sum += info.curScores;
	ss << info.curScores << " = " << sum << std::endl;
	return ss.str();
}

bool Player::hasLegalPlays() {
	for (CardInfo cInfo : cardsInHand) {
		if (Deck::isCardIncluded(Deck::getValidCards(), cInfo)) {
			return true;
		}
	}
	return false;
}

void Player::seniorPlay() {
	std::vector < CardInfo > validCards = Deck::getValidCards();
	std::vector < CardInfo > legalCards;
	for (auto cInfo : cardsInHand) {
		if (Deck::isCardIncluded(validCards, cInfo)) {
			legalCards.push_back(cInfo);
		}
	}
	if (!legalCards.empty()) {
		std::sort(legalCards.begin(), legalCards.end(), std::greater<CardInfo>());
		play(legalCards.at(0));

	} else {
		if (!cardsInHand.empty()) {
			discard(cardsInHand.at(0));
		}
	}

}

void Player::principalPlay() {
	std::vector < CardInfo > validCards = Deck::getValidCards();
	std::vector < CardInfo > legalCards;
	legalCards.clear();
	for (auto cInfo : cardsInHand) {
		if (Deck::isCardIncluded(validCards, cInfo)) {
			legalCards.push_back(cInfo);
		}
	}
	if (!legalCards.empty()) {
		std::sort(legalCards.begin(), legalCards.end(), std::greater<CardInfo>());
		play(legalCards.at(0));

	} else {
		if (!cardsInHand.empty()) {
			std::vector < CardInfo > vCard = this->getCardsInHand();
			std::sort(vCard.begin(), vCard.end(), std::less<CardInfo>());
			discard(vCard.at(0));
		}
	}

}

std::vector<CardInfo> Player::getLegalCardsInHand() {
	std::vector<CardInfo> lCards = Deck::getValidCards();
	std::vector<CardInfo> vCards;
	for (auto cInfo : cardsInHand) {
			if (Deck::isCardIncluded(lCards, cInfo)) {
				vCards.push_back(cInfo);
			}
		}
	return vCards;
}
