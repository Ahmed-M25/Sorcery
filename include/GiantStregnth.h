#ifndef GIANT_STRENGTH_H
#define GIANT_STRENGTH_H

#include "Enchantment.h"

class GiantStrength : public Enchantment {
public:
  GiantStrength();
  std::unique_ptr<Card> clone() const override;
  void play(Target target, Game* game) override;
  EnchantmentDecorator* createDecorator(Minion* target) const override;
};
