#include "../include/StandstillTrigger.h"
#include "../include/Player.h"
#include "../include/Ritual.h"
#include "../include/Minion.h"
#include "../include/Game.h"
#include <iostream>

StandstillTrigger::StandstillTrigger(Ritual* ritual) : TriggeredAbility("Whenever a minion enters play, destroy it", 2, "minionenters"), owner(ritual->getOwner()), ritual(ritual) {}

void StandstillTrigger::execute(Game* game) {
  // This will be called by the trigger manager
  // For now, just a placeholder - the actual logic will be in the overloaded version
  std::cout << "[DEBUG] StandstillTrigger::execute() called without minion parameter" << std::endl;
}

void StandstillTrigger::execute(Game* game, Minion* enteringMinion) {
  if (!ritual || !owner || !enteringMinion) { return; }
  
  if (ritual->canActivate()) {
    ritual->useCharges(2);
    std::cout << owner->getName() << "'s Standstill triggers! " << enteringMinion->getName() << " is destroyed. " << ritual->getCharges() << " charges remaining." << std::endl;
    enteringMinion->die(game);
  } 
  else {
    std::cout << owner->getName() << "'s Standstill has insufficient charges." << std::endl;
  }
}

std::unique_ptr<TriggeredAbility> StandstillTrigger::clone() const {
  return std::make_unique<StandstillTrigger>(ritual);
}
