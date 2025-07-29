#ifndef UNSUMMON_H
#define UNSUMMON_H

#include "cards/base/Spell.h"

class Unsummon : public Spell {
public:
  Unsummon(const std::string& name, int cost, const std::string& desc);
  std::unique_ptr<Card> clone() const override;
  void play(Target target, Game* game) override;
};

#endif 