#include "../include/Blizzard.h"
#include "../include/Game.h"
#include "../include/Player.h"
#include <iostream>

Blizzard::Blizzard(const std::string& name, int cost, const std::string& desc)
  : Spell(name, cost, desc)
{}

std::unique_ptr<Card> Blizzard::clone() const {
  return std::make_unique<Blizzard>(getName(), getCost(), getDescription());
}

void Blizzard::play(Target, Game* game) {
  std::cout << "Blizzard deals 2 damage to all minions!\n";

  for (Player* p : {game->getActivePlayer(), game->getInactivePlayer()}) {
    for (auto m : p->getBoard().getMinions()) {
      m->takeDamage(2, game);
    }
  }
}
