#include "../include/FireElementalTrigger.h"
#include "../include/Minion.h"
#include "../include/Game.h"
#include "../include/Player.h"
#include <iostream>

FireElementalTrigger::FireElementalTrigger(Minion* src)
  : TriggeredAbility("Whenever an opponent's minion enters play, deal 1 damage to it", 0, "minionenters"),
    source(src) {}

std::unique_ptr<TriggeredAbility> FireElementalTrigger::clone() const {
  return std::make_unique<FireElementalTrigger>(source);
}

void FireElementalTrigger::execute(Game* game) {
  if (!source) return;
  
  // Get the entering minion from TriggerManager context
  Minion* enteringMinion = game->getTriggerManager().getCurrentEnteringMinion();
  if (!enteringMinion) return;
  
  // Check if it's an opponent's minion
  if (enteringMinion->getOwner() == source->getOwner()) return;
  
  // Deal 1 damage to the entering minion
  enteringMinion->takeDamage(1, game);
  std::cout << source->getName() << " deals 1 damage to " << enteringMinion->getName() << ". Fire Elemental trigger!" << std::endl;
}
