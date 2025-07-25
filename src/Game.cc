#include "../include/Game.h"
#include "../include/GameDisplay.h"
#include <iostream>
#include <fstream>
#include <sstream>

Game::Game(int argc, char** argv) : turn{1}, gameOver{false}, testingMode{false}, deck1File{"default.deck"}, deck2File{"default.deck"}, initFile{""} {
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

  if (!initFile.empty()) {
    std::ifstream initStream(initFile);
    std::string line;

    // First two lines are expected to be names
    std::getline(initStream, line);
    player1 = std::make_unique<Player>(line);

    std::getline(initStream, line);
    player2 = std::make_unique<Player>(line);

    currentPlayer = player1.get();

    std::cout << "Names loaded from init file: " << player1->getName() << " vs " << player2->getName() << "\n";
  } else {
    // Get player names
    std::string name1, name2;
    std::cout << "Player 1, enter your name: ";
    std::cin >> name1;
    std::cout << "Player 2, enter your name: ";
    std::cin >> name2;

    player1 = std::make_unique<Player>(name1);
    player2 = std::make_unique<Player>(name2);
    currentPlayer = player1.get();
  }

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
  // std::cout << "\nDealing starting hands..." << std::endl;
  for (int i = 0; i < 5; i++) {
    player1->drawCard();
    player2->drawCard();
  }

  currentPlayer->startTurn();

  if (!initFile.empty()) {
    std::ifstream initStream(initFile);
    std::string line;
    std::getline(initStream, line);
    std::getline(initStream, line);

    while (std::getline(initStream, line)) {
      if (line.empty()) continue;
      processCommand(line);
      if (gameOver) return;
    }
  }

  // Show starting status
  std::cout << "\n=== GAME START ===" << std::endl;
  // std::cout << player1->getName() << " hand: ";
  // player1->getHand().display();
  // std::cout << player2->getName() << " hand: ";
  // player2->getHand().display();

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
  triggerManager.notifyEndOfTurn(currentPlayer, this);
  currentPlayer->endTurn();
  currentPlayer = (currentPlayer == player1.get()) ? player2.get() : player1.get();
  turn++;
  currentPlayer->startTurn();
  triggerManager.notifyStartOfTurn(currentPlayer, this);

  checkWinCondition();
  if (!gameOver) {
    displayBoard();
  }
}

void Game::displayBoard() {
  // Will fix to ASCII later
  std::cout << "\n=== BOARD STATE ===" << std::endl;
  
  // Player 1
  std::cout << player1->getName() << " (Life: " << player1->getLife() << ", Magic: " << player1->getMagic() << ")" << std::endl;
  if (player1->getRitual()) {
    std::cout << "Ritual: " << player1->getRitual()->getName() << " (" << player1->getRitual()->getCharges() << " charges)" << std::endl;
  } else {
    std::cout << "Ritual: [None]" << std::endl;
  }
  player1->getBoard().display();
  
  std::cout << std::endl;
  
  // Player 2
  std::cout << player2->getName() << " (Life: " << player2->getLife() << ", Magic: " << player2->getMagic() << ")" << std::endl;
  if (player2->getRitual()) {
    std::cout << "Ritual: " << player2->getRitual()->getName() << " (" << player2->getRitual()->getCharges() << " charges)" << std::endl;
  } else {
    std::cout << "Ritual: [None]" << std::endl;
  }
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
