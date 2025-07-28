#ifndef ENRAGE_H
#define ENRAGE_H

#include "Enchantment.h"
#include "EnchantmentDecorator.h"

class Enrage : public Enchantment {
public:
  Enrage();
  std::unique_ptr<Card> clone() const override;
  void play(Target target, Game* game) override;
};

class EnrageDecorator : public EnchantmentDecorator {
public:
  EnrageDecorator();
  int getModifiedAttack(int baseAttack) const override;
  int getModifiedDefence(int baseDefence) const override;
  int getModifiedActions(int baseActions) const override;
  std::string getName() const override;
};

#endif 