#ifndef BANISH_H
#define BANISH_H

#include "Spell.h"

class Banish : public Spell {
public:
  Banish();
  std::unique_ptr<Card> clone() const override;
  void play(Target target, Game* game) override;
};

#endif 