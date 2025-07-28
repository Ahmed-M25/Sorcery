#ifndef SILENCE_H
#define SILENCE_H

#include "Enchantment.h"
#include "EnchantmentDecorator.h"

class Silence : public Enchantment {
public:
  Silence();
  std::unique_ptr<Card> clone() const override;
  void play(Target target, Game* game) override;
};

class SilenceDecorator : public EnchantmentDecorator {
public:
  SilenceDecorator();
  int getModifiedAttack(int baseAttack) const override;
  int getModifiedDefence(int baseDefence) const override;
  int getModifiedActions(int baseActions) const override;
  int getModifiedAbilityCost(int baseCost) const override;
  bool isAbilitySilenced() const override;
  std::string getName() const override;
};

#endif 