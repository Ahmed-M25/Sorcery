#ifndef Recharge_h
#define Recharge_h

#include "Spell.h"

class Recharge : public Spell {
public:
  Recharge(const std::string& name, int cost, const std::string& desc);
  std::unique_ptr<Card> clone() const override;
  void play(Target target, Game* game) override;
};

#endif 