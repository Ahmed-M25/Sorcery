#ifndef MAGIC_FATIGUE_H
#define MAGIC_FATIGUE_H

#include "cards/base/Enchantment.h"
#include "cards/enchantments/system/EnchantmentDecorator.h"

class MagicFatigue : public Enchantment {
public:
  MagicFatigue();
  std::unique_ptr<Card> clone() const override;
  void play(Target target, Game* game) override;
};

class MagicFatigueDecorator : public EnchantmentDecorator {
public:
  MagicFatigueDecorator();
  int getModifiedAttack(int baseAttack) const override;
  int getModifiedDefence(int baseDefence) const override;
  int getModifiedActions(int baseActions) const override;
  int getModifiedAbilityCost(int baseCost) const override;
  bool isAbilitySilenced() const override;
  std::string getName() const override;
};

#endif 