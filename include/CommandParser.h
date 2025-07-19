#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <string>
#include "Target.h"

class Game;


class CommandParser{
public:
  CommandParser();
  void execute(const std::string& command, Game* game);
  bool isValidCommand(const std::string& input, Game* game);
  void showHelp();
  void handleTestingCommands(const std::string& command, Game* game);
  Target parseTarget(const std::string& input);
};

#endif