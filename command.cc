#include "command.h"

void PlayCard::execute(Player * actor) {
	actor->play(this->getCardInfo());
	setNext(true);

}

void DiscardCard::execute(Player * actor) {
	actor->discard(this->getCardInfo());
	setNext(true);
}

void RageQuit::execute(Player *actor) {
	actor->rageQuit();
	setNext(false);

}

void DeckPrint::execute(Player *actor) {
	std::cout << actor->deckPrint();
	setNext(false);
}

void Command::setCardInfo(CardInfo cInfo) {
	cardInfo.num = cInfo.num;
	cardInfo.type = cInfo.type;
}

CardInfo Command::getCardInfo() {
	return cardInfo;
}

bool Command::getNext() {
	return next;
}

void Command::setNext(bool bb) {
	next = bb;
}
