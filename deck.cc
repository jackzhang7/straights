#include <algorithm>    // std::shuffle
#include <random>       // std::default_random_engine
#include "deck.h"

std::vector<CardInfo> cardsOnTable[4];
const CardType CT[4] = { CardType::C, CardType::D, CardType::H, CardType::S };

Deck::Deck(int seed) :
		seed { seed } {

	for (const auto &t : CTYPES) {
		for (int j = 0; j < 13; j++) {
			CardInfo cInfo;
			cInfo.type = t;
			cInfo.num = j + 1;
			deck.push_back(cInfo);
		}
	}
	// Initialize seed
	srand(seed);
}

void Deck::shuffle() {
	std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));

}

std::vector<CardInfo> Deck::getDeal(size_t id) {
	std::vector<CardInfo> cInfo;
	if (id > 4)
		return cInfo;
	for (int i = 0; i < 13; i++) {
		cInfo.push_back(deck.at(id * 13 + i));
	}
	return cInfo;
}

CardInfo Deck::stringToCardInfo(std::string str) {
	CardInfo cInfo;
	if (str.empty())
		return cInfo;

	char c = str.at(0);
	switch (c) {
	case 'A':
		cInfo.num = 1;
		break;
	case 'T':
		cInfo.num = 10;
		break;
	case 'J':
		cInfo.num = 11;
		break;
	case 'Q':
		cInfo.num = 12;
		break;
	case 'K':
		cInfo.num = 13;
		break;
	default:
		if (c > '0' && c <= '9') {
			std::stringstream ss;
			ss << c;
			int x;
			ss >> x;
			cInfo.num = x;
		} else {
			cInfo.type = CardType::ERROR;
			return cInfo;
		}
	}
	c = str.at(1);
	switch (c) {
	case 'C':
		cInfo.type = CardType::C;
		break;
	case 'D':
		cInfo.type = CardType::D;
		break;
	case 'H':
		cInfo.type = CardType::H;
		break;
	case 'S':
		cInfo.type = CardType::S;
		break;
	default:
		//throw;
		cInfo.type = CardType::ERROR;
	}
	return cInfo;

}

std::string Deck::cardInfoToString(CardInfo cInfo) {
	std::stringstream ss;

	switch (cInfo.num) {
	case 1:
		ss << "A";
		break;
	case 10:
		ss << "T";
		break;
	case 11:
		ss << "J";
		break;
	case 12:
		ss << "Q";
		break;
	case 13:
		ss << "K";
		break;
	default:
		ss << cInfo.num;
	}

	switch (cInfo.type) {
	case CardType::C:
		ss << "C";
		break;
	case CardType::D:
		ss << "D";
		break;
	case CardType::H:
		ss << "H";
		break;
	case CardType::S:
		ss << "S";
		break;
	default:
		throw;
	}
	return ss.str();

}

std::string Deck::cardNumToString(CardInfo cInfo) {
	std::stringstream ss;

	switch (cInfo.num) {
	case 1:
		ss << "A";
		break;
	case 10:
		ss << "T";
		break;
	case 11:
		ss << "J";
		break;
	case 12:
		ss << "Q";
		break;
	case 13:
		ss << "K";
		break;
	default:
		ss << std::to_string(cInfo.num);
	}
	return ss.str();
}

std::string Deck::allDeckStr() {
	int j = 1;
	std::stringstream ss("");
	for (int i = 0; i < NUM_CARDS; i++) {
		ss << cardInfoToString(deck.at(i));
		if (j == PER_PLAYER) {
			j = 1;
			ss << std::endl;
		} else {
			ss << " ";
			j++;
		}
	}
	return ss.str();
}

std::vector<CardInfo> Deck::getValidCards() {
	std::vector<CardInfo> vCard;
	CardInfo cInfo;
	for (int i = 0; i < 4; i++) {
		if (cardsOnTable[i].size() == 0) {
			cInfo.num = 7;
			cInfo.type = CT[i];
			vCard.push_back(cInfo);
			continue;
		}
		//Check low
		if (cardsOnTable[i].at(0).num > 0) {
			cInfo.num = cardsOnTable[i].at(0).num - 1;
			cInfo.type = cardsOnTable[i].at(0).type;
			vCard.push_back(cInfo);
		}
		//Check high
		if (cardsOnTable[i].at(0).num < 13) {
			cInfo.num = cardsOnTable[i].at(cardsOnTable[i].size() - 1).num + 1;
			cInfo.type = cardsOnTable[i].at(cardsOnTable[i].size() - 1).type;
			vCard.push_back(cInfo);
		}
	}

	return vCard;
}

bool Deck::isCardIncluded(std::vector<CardInfo> vCard, CardInfo cInfo) {
	for (auto ci : vCard) {
		if (ci.num == cInfo.num && ci.type == cInfo.type) {
			return true;
		}
	}
	return false;
}

std::string getCardsOnTable() {

	std::string typeStr[4] = { "Clubs:", "Diamonds:", "Hearts:", "Spades:" };
	int i = 0;
	std::stringstream ss("");
	ss << "Cards on the table:" << std::endl;
	for (i = 0; i < 4; i++) {
		ss << typeStr[i];
		for (auto cInfo : cardsOnTable[i]) {
			ss << Deck::cardNumToString(cInfo);
		}
		ss << std::endl;
	}
	return ss.str();
}

void Deck::addcardToTable(CardInfo cInfo) {
	for (int i = 0; i < 4; i++) {
		if (CT[i] == cInfo.type) {
			cardsOnTable[i].push_back(cInfo);
			std::sort(cardsOnTable[i].begin(), cardsOnTable[i].end(),
					std::less<CardInfo>());

			break;
		}
	}
}

