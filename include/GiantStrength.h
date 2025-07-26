#ifndef GIANT_STRENGTH_H
#define GIANT_STRENGTH_H

#include "Enchantment.h"
#include "EnchantmentDecorator.h"

class GiantStrength : public Enchantment {
public:
  GiantStrength();
  std::unique_ptr<Card> clone() const override;
  void play(Target target, Game* game) override;
  EnchantmentDecorator* createDecorator(Minion* target) const override;
};

class GiantStrengthDecorator : public EnchantmentDecorator {
public:
  GiantStrengthDecorator(Minion* minion);
  int getAttack() const override;
  int getDefence() const override;
};

#endif 