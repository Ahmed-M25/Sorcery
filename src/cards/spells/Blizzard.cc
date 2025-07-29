#include "cards/spells/Blizzard.h"
#include "core/Game.h"
#include "core/Player.h"
#include <iostream>

Blizzard::Blizzard(const std::string& name, int cost, const std::string& desc)
  : Spell(name, cost, desc)
{}

std::unique_ptr<Card> Blizzard::clone() const {
  return std::make_unique<Blizzard>(getName(), getCost(), getDescription());
}

bool Blizzard::requiresTarget() const {
  return false; // Blizzard affects all minions, no targeting required
}

void Blizzard::play(Target, Game* game) {
  std::cout << "Blizzard deals 2 damage to all minions!\n";

  for (Player* p : {game->getActivePlayer(), game->getInactivePlayer()}) {
    for (auto m : p->getBoard().getMinions()) {
      m->takeDamage(2, game);
    }
  }
}
