#include "../include/Unsummon.h"
#include "../include/Game.h"
#include "../include/Player.h"
#include <iostream>

Unsummon::Unsummon(const std::string& name, int cost, const std::string& desc)
  : Spell(name, cost, desc)
{}

std::unique_ptr<Card> Unsummon::clone() const {
  return std::make_unique<Unsummon>(getName(), getCost(), getDescription());
}

void Unsummon::play(Target target, Game* game) {
  if (!target.isValidTarget(game) || target.Ritual()) {
    std::cout << "Invalid target for Unsummon.\n";
    return;
  }

  Player* owner = (target.getPlayerNum() == 1 ? game->getPlayer1() : game->getPlayer2());

  int pos = target.getPosition();

  // Get minion to trigger event
  Minion* minionPtr = owner->getBoard().getMinion(pos);
  if (!minionPtr) {
    std::cout << "No minion at that position.\n";
    return;
  }

  // Notify that minion is leaving play BEFORE removing it
  game->getTriggerManager().notifyMinionLeaves(minionPtr, game);

  // Remove minion from board
  std::unique_ptr<Minion> minion = owner->getBoard().removeMinion(pos);

  // Return it to the owner’s hand
  owner->getHand().addCard(std::move(minion));
  std::cout << "Unsummon returns "  << owner->getHand().getCard(owner->getHand().size() - 1)->getName() << " to " << owner->getName() << "'s hand.\n";
}