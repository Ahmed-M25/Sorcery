#ifndef GIANT_STRENGTH_H
#define GIANT_STRENGTH_H

#include "Enchantment.h"
#include "EnchantmentDecorator.h"

class GiantStrength : public Enchantment {
public:
  GiantStrength();
  std::unique_ptr<Card> clone() const override;
  void play(Target target, Game* game) override;
};

class GiantStrengthDecorator : public EnchantmentDecorator {
public:
  GiantStrengthDecorator();
  int getModifiedAttack(int baseAttack) const override;
  int getModifiedDefence(int baseDefence) const override;
  int getModifiedActions(int baseActions) const override;
  int getModifiedAbilityCost(int baseCost) const override;
  bool isAbilitySilenced() const override;
  std::string getName() const override;
};

#endif 