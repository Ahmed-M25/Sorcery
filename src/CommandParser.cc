#include "../include/CommandParser.h"
#include "../include/Game.h"
#include <iostream>
#include <sstream>
#include <string>

CommandParser::CommandParser() {}

void CommandParser::execute(const std::string&command, Game* game){
  std::istringstream iss(command);
  std::vector<std::string> tokens;
  std::string token;

  // Split command into tokens
  while (iss >> token) {
    tokens.push_back(token);
  }

  if (tokens.empty()) return; 

  std::string cmd = tokens[0];
  Player* activePlayer = game->getActivePlayer();

  if (cmd == "help") {
    showHelp();
  }
  else if (cmd == "hand") {
    activePlayer->getHand().display();
  }
  else if (cmd == "board") {
    game->displayBoard();
  }
  else if (cmd == "play" && tokens.size() >= 2) {
    try {
      int cardIndex = std::stoi(tokens[1]);
      Target target; // Empty target for now (no targeting implemented yet)
      activePlayer->playCard(cardIndex, target, game);
    }
    catch (const std::exception& e) {
      std::cout << "Invlaid card number!" << std::endl;
    }
  }
  else if (cmd == "attack" && tokens.size() >= 2) {
    try {
      int minionIndex = std::stoi(tokens[1]);
      int index = minionIndex - 1; // Conver to 0-indexed

      Minion* minion = activePlayer->getBoard().getMinion(index);
      if (minion && minion->hasActions()) {
        Player* opponent = game->getInactivePlayer();
        minion->attackPlayer(opponent, game);
        // TODO: Subtract action and apply damage
      }
      else {
        std::cout << "Invalid minion or no actions remaining!" << std::endl;
      }
    }
    catch (const std::exception& e) {
      std::cout << "Invalid minion number!" << std::endl;
    }
  }
  else if (cmd == "end") {
    game->nextTurn();
  }
  else {
    std::cout << "Unknown command: " << command << std::endl;
    std::cout << "Type 'help' for available commands." << std::endl;
  }
}

void CommandParser::showHelp() {
  std::cout << R"(Commands: help -- Display this message.
  end  -- End the current player's turn.
  quit -- End the game.
  attack minion other-minion -- Orders minion to attack other-minion.
  attack minion -- Orders minion to attack the opponent.
  play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player.
  use minion [target-player target-card] -- Use minion's special ability, optionally targeting target-card owned by target-player.
  inspect minion -- View a minion's card and all enchantments on that minion.
  hand -- Describe all cards in your hand.
  board -- Describe all cards on the board.
)" << std::endl;
}

