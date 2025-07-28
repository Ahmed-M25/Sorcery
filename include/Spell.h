#ifndef SPELL_H
#define SPELL_H

#include "Card.h"
#include "Target.h"

class Game;

class Spell : public Card {
public:
  Spell(const std::string& name, int cost, const std::string& desc);
  virtual ~Spell() = default;

  virtual void play(Target target, Game* game) = 0;
  std::unique_ptr<Card> clone() const = 0;
  std::string getType() const {
    return "Spell";
  }
  virtual bool requiresTarget() const { return true; } // Default for spells is to require targeting

};

#endif
