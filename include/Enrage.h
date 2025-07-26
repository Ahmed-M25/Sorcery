#ifndef ENRAGE_H
#define ENRAGE_H

#include "Enchantment.h"
#include "EnchantmentDecorator.h"

class Enrage : public Enchantment {
public:
  Enrage();
  std::unique_ptr<Card> clone() const override;
  void play(Target target, Game* game) override;
  EnchantmentDecorator* createDecorator(Minion* target) const override;
};

class EnrageDecorator : public EnchantmentDecorator {
public:
  EnrageDecorator(Minion* minion);
  int getAttack() const override;
  int getDefence() const override;
};

#endif 