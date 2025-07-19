#ifndef GAMEDISPLAY_H
#define GAMEDISPLAY_H

#include <string>

class Player;
class Card;
class Minion;

class GameDisplay {
public:
  static void displayBoard(Player* p1, Player* p2);
  static void displayHand(Player* player);
  static void displayCard(Card* card);
  static void displayMinion(Minion* minion);
  static void displayHelp();
  static void displayGameOver(const std::string& reason);
  static std::string cardToString(Card* card);
  static void loadAsciiArt();
};

#endif