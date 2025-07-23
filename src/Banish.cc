#include "../include/Banish.h"
#include "../include/Game.h"
#include "../include/Player.h"
#include <iostream>

Banish::Banish(const std::string& name, int cost, const std::string& desc)
  : Spell(name, cost, desc)
{}

std::unique_ptr<Card> Banish::clone() const {
  return std::make_unique<Banish>(getName(), getCost(), getDescription());
}

void Banish::play(Target target, Game* game) {
  if (!target.isValidTarget(game)) {
    std::cout << "Invalid target for Banish.\n";
    return;
  }

  Player* owner = (target.getPlayerNum() == 1 ? game->getPlayer1() : game->getPlayer2());

  if (target.Ritual()) {
    owner->setRitual(nullptr);
    std::cout << "Banish destroys " << owner->getName() << "'s ritual.\n";
  } else {
    Minion* m = owner->getBoard().getMinion(target.getPosition());
    if (m) {
      m->die(game);
      std::cout << "Banish destroys " << m->getName() << ".\n";
    }
  }
}
