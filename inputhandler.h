
#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

#include <iostream>
#include <string>
#include "command.h"
//#include "game.h"

class InputHandler
{
  std::shared_ptr<Command> play;
  std::shared_ptr<Command> discard;
  std::shared_ptr<Command> rageQuit;
  std::shared_ptr<Command> quit;
  std::shared_ptr<Command> deck;


public:
  InputHandler();
  //bool isCommand(std::string);

  PlayInfo parseInputCmd();

  Command* handleInput(Player *player);



};


#endif /* INPUTHANDLER_H_ */
