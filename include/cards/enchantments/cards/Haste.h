#ifndef HASTE_H
#define HASTE_H

#include "cards/base/Enchantment.h"
#include "cards/enchantments/system/EnchantmentDecorator.h"

class Haste : public Enchantment {
public:
  Haste();
  std::unique_ptr<Card> clone() const override;
  void play(Target target, Game* game) override;
};

class HasteDecorator : public EnchantmentDecorator {
public:
  HasteDecorator();
  int getModifiedAttack(int baseAttack) const override;
  int getModifiedDefence(int baseDefence) const override;
  int getModifiedActions(int baseActions) const override;
  int getModifiedAbilityCost(int baseCost) const override;
  bool isAbilitySilenced() const override;
  std::string getName() const override;
};

#endif 