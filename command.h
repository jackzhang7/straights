/*
 * cmd.h
 *
 *  Using command design pattern
 *
 */


#ifndef COMMAND_H_
#define COMMAND_H_
#include <string>
#include "player.h"
//#include "game.h"


class Command
{
	bool next;
	CardInfo cardInfo;
public:
  virtual ~Command() {}
  virtual void execute(Player *) = 0;
  virtual void setCardInfo(CardInfo);
  virtual CardInfo getCardInfo();
  bool getNext();
  void setNext(bool);

};

class PlayCard : public Command
{
	//bool next;
public:
	virtual void execute(Player * actor);
};

class DiscardCard : public Command
{
public:
  virtual void execute(Player *actor);
};


class RageQuit : public Command
{
public:
  virtual void execute(Player *actor);
};

class DeckPrint : public Command
{
public:
  virtual void execute(Player *actor);
};


#endif /* COMMAND_H_ */
