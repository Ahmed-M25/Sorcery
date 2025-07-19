#ifndef MINION_H
#define MINION_H

#include "Card.h"
#include "Target.h"

class Game;
class Player;

class Minion : public Card {
protected:
  int baseAttack;
  int baseDefence;
  int currentActions;
  // TODO: Add ability vectors in later steps

public:
  Minion(const std::string& name, int cost, int att, int def, const std::string& desc);
  ~Minion() = default;

  virtual void play(Target target, Game* game) override;
  std::unique_ptr<Card> clone() const override;
  std::string getType() const override;

  // Combat and stats
  virtual void attackPlayer(Player* target, Game* game);
  virtual void attackMinion(Minion* target, Game* game);
  virtual void takeDamage(int damage, Game* game);
  void die(Game* game);
  void restoreActions();
  bool hasActions() const;

  // Getters
  virtual int getAttack() const;
  virtual int getDefence() const;
};

#endif