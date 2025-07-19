#ifndef SPELL_H
#define SPELL_H

#include "Card.h"
#include "Target.h"

class Game;

class Spell : public Card {
public:
  Spell(const std::string& name, int cost, const std::string& desc);
  ~Spell() = default;

  void play(Target target, Game* game) override;
  std::unique_ptr<Card> clone() const override;
  std::string getType() const override;
};

#endif
