#include "../include/CommandParser.h"
#include "../include/Game.h"
#include "../include/GameDisplay.h"
#include <iostream>
#include <sstream>
#include <string>

CommandParser::CommandParser() {}

void CommandParser::execute(const std::string&command, Game* game) {
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
    GameDisplay::displayHelp();
  }
  else if (cmd == "hand") {
    GameDisplay::displayHand(activePlayer);
  }
  else if (cmd == "board") {
    game->displayBoard();
  }
  else if (cmd == "play") {
    if (tokens.size() < 2) {
      std::cout << "Invalid play command. Use: play i or play i p t" << std::endl;
      return;
    }

    try {
      int cardIndex = std::stoi(tokens[1]);
      Card* card = activePlayer->getHand().getCard(cardIndex - 1);
      
      if (!card) {
        std::cout << "Invalid card index!" << std::endl;
        return;
      }

      // Check if card requires targeting
      if (card->requiresTarget()) {
        // Card requires targeting - need 4 tokens: play i p t
        if (tokens.size() < 4) {
          std::cout << card->getName() << " requires a target. Use: play " << cardIndex << " p t" << std::endl;
          return;
        }

        int playerNum = std::stoi(tokens[2]);
        Target target;
        
        if (tokens[3] == "r") {
          // Targeting ritual
          target = Target(playerNum, 0, true);
        } else {
          // Targeting minion
          int targetPosition = std::stoi(tokens[3]);
          target = Target(playerNum, targetPosition - 1, false); 
        }
        
        activePlayer->playCard(cardIndex, target, game);
      } else {
        // Card doesn't require targeting - use 2 tokens: play i
        if (tokens.size() > 2) {
          std::cout << card->getName() << " doesn't require a target. Use: play " << cardIndex << std::endl;
          return;
        }

        Target target; // Empty target
        activePlayer->playCard(cardIndex, target, game);
      }
    } catch (const std::exception& e) {
      std::cout << "Invalid play command format!" << std::endl;
    }
  }
  else if (cmd == "attack") {
    // Attacking player
    if (tokens.size() == 2) {
      int i = std::stoi(tokens[1]);
      Player* attacker = game->getActivePlayer();
      Player* target = game->getInactivePlayer();

      int index = i - 1;

      Minion* minion = attacker->getBoard().getMinion(index);
      if (!minion) {
            std::cout << "No minion at position " << i << ".\n";
            return;
      }

      // Check if attacking minion has actions
      if (!minion->hasActions()) {
        std::cout << minion->getName() << " has no actions remaining!\n";;
        return;
      }

      minion->attackPlayer(target, game);
      minion->useAction();
      game->checkWinCondition();
    }
    // Attacking a minion
    else if (tokens.size() == 3) {
      try {
        int attackerIndex = std::stoi(tokens[1]);
        int defenderIndex = std::stoi(tokens[2]);

        Player* attacker = game->getActivePlayer();
        Player* defender = game->getInactivePlayer();

        // Convert to 0-indexed
        int attackerPos = attackerIndex - 1;
        int defenderPos = defenderIndex - 1;

        Minion* attackingMinion = attacker->getBoard().getMinion(attackerPos);
        Minion* defendingMinion = defender->getBoard().getMinion(defenderPos);

        if (!attackingMinion) {
          std::cout << "No minion at position " << attackerIndex << ".\n";
          return;
        }
        if (!defendingMinion) {
          std::cout << "No enemy minion at position " << defenderIndex << ".\n";
          return;
        }

        // Check if attacking minion has actions
        if (!attackingMinion->hasActions()) {
          std::cout << attackingMinion->getName() << " has no actions remaining!\n";;
          return;
        }

        attackingMinion->attackMinion(defendingMinion, game);
        attackingMinion->useAction();
      }
      catch (const std::exception& e) {
        std::cout << "Invalid minion numbers!\n";
      }
    }
  }
  else if (cmd == "use") {
      // Use minion target-player target-card
    if (tokens.size() >= 4) {
      try {
        int minionIndex = std::stoi(tokens[1]);
        int playerNum = std::stoi(tokens[2]);

        Target target;

        // Targeting ritual
        if (tokens[3] == "r") {
          target = Target(playerNum, 0, true);
        }
        // Targeting minion
        else {
          int targetPosition = std::stoi(tokens[3]);
          target = Target(playerNum, targetPosition - 1, false);
        }

        // Get minion from active player's board
        Player* activePlayer = game->getActivePlayer();
        Minion* minion = activePlayer->getBoard().getMinion(minionIndex - 1); // Convert to 0-indexed

        if (!minion) {
          std::cout << "No minion at position " << minionIndex << std::endl;
          return;
        }

        if (!minion->hasActivatedAbility()) {
          std::cout << minion->getName() << " has no activated ability!" << std::endl;
          return;
        }

        minion->useAbility(target, game);
      }
      catch (const std::exception& e) {
        std::cout << "Invalid use command format!" << std::endl;
      }
    }
    // Use minion (no target)
    else if (tokens.size() == 2) {
      try {
        int minionIndex = std::stoi(tokens[1]);

        Player* activePlayer = game->getActivePlayer();
        Minion* minion = activePlayer->getBoard().getMinion(minionIndex - 1);

        if (!minion) {
          std::cout << "No minion at position " << minionIndex << std::endl;
          return;
        }

        if (!minion->hasActivatedAbility()) {
          std::cout << minion->getName() << " has no activated ability!" << std::endl;
          return;
        }

        Target noTarget;
        minion->useAbility(noTarget, game);
      }
      catch (const std::exception& e) {
        std::cout << "Invalid minion number!" << std::endl;
      }
    }
    else {
      std::cout << "Invalid use command format!" << std::endl;
      std::cout << "Usage: use minion [target-player target-card]" << std::endl;
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
