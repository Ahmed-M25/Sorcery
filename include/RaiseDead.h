#ifndef RAISE_DEAD_H
#define RAISE_DEAD_H

#include "Spell.h"

class RaiseDead : public Spell {
public:
  RaiseDead(const std::string& name, int cost, const std::string& desc);
  std::unique_ptr<Card> clone() const override;
  void play(Target target, Game* game) override;
};

#endif 