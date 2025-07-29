#ifndef DISENCHANT_H
#define DISENCHANT_H

#include "cards/base/Spell.h"

class Disenchant : public Spell {
public:
  Disenchant(const std::string& name, int cost, const std::string& desc);
  std::unique_ptr<Card> clone() const override;
  void play(Target target, Game* game) override;
};

#endif 