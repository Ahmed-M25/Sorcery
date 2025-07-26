#ifndef EnchantmentDecorator_H
#define EnchantmentDecorator_H

#include "Minion.h"

class EnchantmentDecorator : public Minion {
protected:
  int baseAttack;
  int baseDefence;
public:
  EnchantmentDecorator(Minion* minion);
  ~EnchantmentDecorator();

  std::string getType() const override { return "Minion"; }
  
  void attackPlayer(Player* target, Game* gane) override;
  void attackMinion(Minion* target, Game* game) override;
  void takeDamage(int damage, Game* game) override;
  void die(Game* game) override;
  void restoreActions();
  bool hasActions() const;

  virtual int getAttack() const override = 0;
  virtual int getDefence() const override = 0;

  virtual void applyEnchantment()  {}
  virtual void removeEnchantment() {}

};

#endif