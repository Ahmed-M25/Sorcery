#ifndef GAMEDISPLAY_H
#define GAMEDISPLAY_H

#include <string>
#include <vector>
#include "../include/ascii_graphics.h"

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

private:
  static card_template_t getCardTemplate(Card* card);
  static void displayTopRow(Player* player);
  static void displayBottomRow(Player* player);
  static void displayMinionRow(Player* player);
  static void displayCenterGraphic();
  static void displayCardsHorizontally(const std::vector<card_template_t>& cards);
};

#endif