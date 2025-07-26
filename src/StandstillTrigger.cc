#include "../include/StandstillTrigger.h"
#include "../include/Player.h"
#include "../include/Ritual.h"
#include "../include/Minion.h"
#include "../include/Game.h"
#include <iostream>

StandstillTrigger::StandstillTrigger(Ritual* ritual) : TriggeredAbility("Whenever a minion enters play, destroy it", 2, "minionenters"), owner(ritual->getOwner()), ritual(ritual) {}

void StandstillTrigger::execute(Game* game) {
  if (!ritual || !owner) return;
  
  // Get the entering minion from TriggerManager context
  Minion* enteringMinion = game->getTriggerManager().getCurrentEnteringMinion();
  if (!enteringMinion) return;
  
  if (ritual->canActivate()) {
    ritual->useCharges(2);
    std::cout << owner->getName() << "'s Standstill triggers! " << enteringMinion->getName() << " is destroyed. " << ritual->getCharges() << " charges remaining." << std::endl;
    
    // Destroy the minion
    enteringMinion->die(game);
  } 
  else {
    std::cout << owner->getName() << "'s Standstill has insufficient charges." << std::endl;
  }
}

std::unique_ptr<TriggeredAbility> StandstillTrigger::clone() const {
  return std::make_unique<StandstillTrigger>(ritual);
}
