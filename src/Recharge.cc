#include "../include/Recharge.h"
#include "../include/Game.h"
#include "../include/Player.h"
#include "../include/Ritual.h"
#include <iostream>

Recharge::Recharge(const std::string& name, int cost, const std::string& desc)
  : Spell(name, cost, desc)
{}

std::unique_ptr<Card> Recharge::clone() const {
  return std::make_unique<Recharge>(getName(), getCost(), getDescription());
}

bool Recharge::requiresTarget() const {
  return false; // Recharge affects your own ritual, no targeting required
}

void Recharge::play(Target, Game* game) {
  Player* me = game->getActivePlayer();
  Ritual* r = me->getRitual();

  if (!r) {
    std::cout << "Cannot play Recharge: you have no ritual in play.\n";
    return;
  }

  r->addCharges(3);

  std::cout << "Recharge adds 3 charges to " << r->getName() << "(now at" << r->getCharges() << " charges).\n";

}
