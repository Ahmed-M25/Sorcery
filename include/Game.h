#ifndef GAME_H
#define GAME_H

#include <string>
#include <memory>
#include "Player.h"
#include "CommandParser.h"
#include "TriggerManager.h"


class Game {
private:
  std::unique_ptr<Player> player1;
  std::unique_ptr<Player> player2;
  Player* currentPlayer;
  int turn;
  bool gameOver;
  bool testingMode;
  std::string deck1File;
  std::string deck2File;
  std::string initFile;
  std::unique_ptr<CommandParser> parser;
  TriggerManager triggerManager;

public:
  Game(int argc, char** argv);
  ~Game() = default;

  // Core game flow
  void startGame();
  void nextTurn();
  void processCommand(const std::string& command);
  void checkWinCondition();
  bool isGameOver() const;
  void displayBoard();

  Player* getPlayer1() const {
    return player1.get();
  };
  Player* getPlayer2() const {
    return player2.get();
  };


  // Player access
  Player* getActivePlayer();
  Player* getInactivePlayer();

  // Setup
  void parseCommandLineArgs(int argc, char** argv);
};

#endif