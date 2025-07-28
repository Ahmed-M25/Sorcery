#ifndef MINION_H
#define MINION_H

#include "Card.h"
#include "Target.h"
#include <vector>
#include <memory>


class Game;
class Player;
class EnchantmentDecorator;

class Minion : public Card {
protected:
  int baseAttack;
  int baseDefence;
  int currentActions;
  std::unique_ptr<class EnchantmentList> enchantments;

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

  // Getters
  virtual int getAttack() const;
  virtual int getDefence() const;

  // Setters
  void setAttack(int att);
  void setDefence(int def);
  void setActions(int act)

  // Enchantment management
  void addEnchantment(std::unique_ptr<EnchantmentDecorator> enchantment);
  void removeTopEnchantment();
  bool hasEnchantments() const;
  const std::vector<std::unique_ptr<EnchantmentDecorator>>& getEnchantments() const;
};

#endif