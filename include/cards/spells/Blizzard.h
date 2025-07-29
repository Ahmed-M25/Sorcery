#ifndef BLIZZARD_H
#define BLIZZARD_H

#include "cards/base/Spell.h"

class Blizzard : public Spell {
public:
  Blizzard(const std::string& name, int cost, const std::string& desc);
  std::unique_ptr<Card> clone() const override;
  void play(Target target, Game* game) override;
  bool requiresTarget() const override;
};

#endif 