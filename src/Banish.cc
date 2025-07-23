#include "../include/Banish.h"
#include "../include/Game.h"
#include "../include/Player.h"
#include <iostream>

Banish::Banish()
  : Spell("Banish", 2, "Destroy target minion or ritual")
{}

std::unique_ptr<Card> Banish::clone() const {
  return std::make_unique<Banish>(*this);
}

void Banish::play(Target target, Game* game) {
  if (!target.isValidTarget(game)) {
    std::cout << "Invalid target for Banish.\n";
    return;
  }
  Player* owner = game->getActivePlayer();
  if (target.isRitual()) {
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
