#ifndef MINION_H
#define MINION_H

#include "Card.h"
#include "Target.h"
#include <vector>
#include <memory>

class Game;
class Player;
class AbilityCommand;

class Minion : public Card {
protected:
  int baseAttack;
  int baseDefence;
  int currentActions;
  std::unique_ptr<AbilityCommand> activatedAbility;

public:
  Minion(const std::string& name, int cost, int att, int def, const std::string& desc);
  ~Minion();
  Minion(const Minion&) = delete;
  Minion& operator=(const Minion&) = delete;


  virtual void play(Target target, Game* game) override;
  std::unique_ptr<Card> clone() const override;
  std::string getType() const override;

  // Combat and stats
  virtual void attackPlayer(Player* target, Game* game);
  virtual void attackMinion(Minion* target, Game* game);
  virtual void takeDamage(int damage, Game* game);
  virtual void die(Game* game);
  void restoreActions();
  bool hasActions() const;
  void useAction();

  // Ability management
  void setActivatedAbility(std::unique_ptr<AbilityCommand> ability);
  void useAbility(Target target, Game* game);
  bool hasActivatedAbility() const;
  int getAbilityCost(int abilityIndex) const;
  const std::string& getAbilityDescription(int abilityIndex) const;

  // Getters
  virtual int getAttack() const;
  virtual int getDefence() const;

  // Setters
  void setAttack(int att);
  void setDefence(int def);

};

#endif