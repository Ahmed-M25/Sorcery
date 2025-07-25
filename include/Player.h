#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Hand.h"
#include "Deck.h"
#include "Board.h"
#include "Graveyard.h"
#include "Ritual.h"

class Game;
class Target;

class Player {
private:
  std::string name;
  int life;
  int magic;
  Hand hand;
  Deck deck;
  Board board;
  Graveyard graveyard;
  std::unique_ptr<Ritual> ritual;

public:
  Player(const std::string& name);
  
  const std::string& getName() const;

  // Deck and Hand management
  void drawCard();
  void loadDeck(const std::string& filename);
  void shuffleDeck();
  void playCard(int index, Target target, Game* game);

  // Combat and actions
  void takeDamage(int damage);
  void heal(int amount);
  bool isDead() const;
  void startTurn();
  void endTurn();
  void restoreMinionsActions();
  void setRitual(std::unique_ptr<Ritual> newRitual) {
    ritual = std::move(newRitual);
  }

  // Resource management
  void gainMagic(int amount);
  bool canAfford(int cost) const;
  void payMagic(int cost);

  // Basic getters for testing
  Hand& getHand() { return hand; }
  Deck& getDeck() { return deck; }
  Board& getBoard() { return board; }
  Graveyard& getGraveyard() { return graveyard; }
  Ritual* getRitual() const { return ritual.get(); }
  int getLife() const { return life; }
  int getMagic() const { return magic; }
};

#endif