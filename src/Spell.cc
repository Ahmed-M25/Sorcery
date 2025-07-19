#include "../include/Spell.h"
#include "../include/Game.h"
#include <iostream>

Spell::Spell(const std::string& name, int cost, const std::string& desc) : Card {name, cost, desc} {}

void Spell::play(Target target, Game* game) {
  std::cout << "Playing spell: " << name << " (placeholder effect)" << std::endl;
  // TODO: Implement specific spell effects later
}

std::unique_ptr<Card> Spell::clone() const {
  return std::make_unique<Spell>(name, cost, description);
}

std::string Spell::getType() const {
  return "Spell";
}
