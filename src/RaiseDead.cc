#include "../include/RaiseDead.h"
#include "../include/Graveyard.h"
#include "../include/Game.h"
#include "../include/Player.h"
#include <iostream>

RaiseDead::RaiseDead(const std::string& name, int cost, const std::string& desc)
  : Spell(name, cost, desc)
{}

std::unique_ptr<Card> RaiseDead::clone() const {
  return std::make_unique<RaiseDead>(getName(), getCost(), getDescription());
}

void RaiseDead::play(Target, Game* game) {
  Player* me = game->getActivePlayer();
  auto& graveyard = me->getGraveyard();
  if (graveyard.isEmpty()) {
    std::cout << "No minions in graveyard to resurrect." << std::endl;
    return;
  }
  if (me->getBoard().isFull()) {
    std::cout << "Cannot play Raise Dead: board is full.\n";
    return;
  }
  std::unique_ptr<Minion> minionPtr = graveyard.removeTop();
  minionPtr->setDefence(1);
  me->getBoard().addMinion(std::move(minionPtr));
  std::cout << "Resurrected a minion from the graveyard and set its defence to 1." << std::endl;
}
