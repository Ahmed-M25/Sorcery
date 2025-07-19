#include "../include/Game.h"
#include "../include/GameDisplay.h"
#include <iostream>
#include <fstream>
#include <sstream>

Game::Game(int argc, char** argv) : turn{1}, gameOver{false}, testingMode{false}, deck1File{"default.deck"}, deck2File{"default.deck"} {
  parseCommandLineArgs(argc, argv);

  // Create players with default names for now
  player1 = std::make_unique<Player>("Player1");
  player2 = std::make_unique<Player>("Player2");
  currentPlayer = player1.get();

  // Create command parser
  parser = std::make_unique<CommandParser>();
}

void Game::parseCommandLineArgs(int argc, char** argv) {
  for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];

    if (arg == "-deck1" && i + 1 < argc) {
      deck1File = argv[++i];
    }
    else if (arg == "-deck2" && i + 1 < argc) {
      deck2File = argv[++i];
    }
    else if (arg == "-init" && i + 1 < argc) {
      initFile = argv[++i];
    }
    else if (arg == "-testing") {
      testingMode = true;
    }
  }
}

void Game::startGame() {
  std::cout << "Welcome to Sorcery!" << std::endl;

  // Get player names
  std::string name1, name2;
  std::cout << "Player 1, enter your name: ";
  std::cin >> name1;
  std::cout << "Player 2, enter your name: ";
  std::cin >> name2;

  player1 = std::make_unique<Player>(name1);
  player2 = std::make_unique<Player>(name2);
  currentPlayer = player1.get();

  // Load decks from files
  std::cout << "\nLoading decks..." << std::endl;
  player1->loadDeck(deck1File);
  player2->loadDeck(deck2File);

  // Shuffle decks (if not in testing mode)
  if (!testingMode) {
    player1->shuffleDeck();
    player2->shuffleDeck();
  }

  // Deal starting hands
  std::cout << "\nDealing starting hands..." << std::endl;
  for (int i = 0; i < 5; i++) {
    player1->drawCard();
    player2->drawCard();
  }

  // Show starting status
  std::cout << "\n=== GAME START ===" << std::endl;
  std::cout << player1->getName() << " hand: ";
  player1->getHand().display();
  std::cout << player2->getName() << " hand: ";
  player2->getHand().display();

  std::cout << currentPlayer->getName() << "'s turn." << std::endl;
  std::cout << "Enter commands (type 'quit' to exit):" << std::endl;

  std::string command;
  while (!gameOver && std::getline(std::cin, command)) {
    if (command.empty()) continue;

    if (command == "quit") {
      gameOver = true;
      std::cout << "Game ended by player." << std::endl;
      break;
    }

    processCommand(command);
  }
}

Player* Game::getActivePlayer() {
  return currentPlayer;
}

Player* Game::getInactivePlayer() {
  return (currentPlayer == player1.get()) ? player2.get() : player1.get();
}

void Game::nextTurn() {
  currentPlayer->endTurn();
  currentPlayer = (currentPlayer == player1.get()) ? player2.get() : player1.get();
  turn++;
  currentPlayer->startTurn();

  checkWinCondition();
  if (!gameOver) {
    displayBoard();
  }
}

void Game::displayBoard() {
  // Will fix to ASCII later
  std::cout << "\n=== BOARD STATE ===" << std::endl;
  std::cout << player1->getName() << " (Life: " << player1->getLife() << ", Magic: " << player1->getMagic() << ")" << std::endl;
  player1->getBoard().display();

  std::cout << player2->getName() << " (Life: " << player2->getLife() << ", Magic: " << player2->getMagic() << ")" << std::endl;
  player2->getBoard().display();
  std::cout << "===================" << std::endl;
}

void Game::checkWinCondition() {
  if (player1->isDead()) {
    std::cout << player2->getName() << "wins!" << std::endl;
    gameOver = true;
  }
  else if (player2->isDead()) {
    std::cout << player1->getName() << " wins!" << std::endl;
    gameOver = true;
  }
}

bool Game::isGameOver() const {
  return gameOver;
}

void Game::processCommand(const std::string& command) {
  parser->execute(command, this);
}
