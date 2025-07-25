#include "../include/AuraPowerTrigger.h"
#include "../include/Player.h"
#include "../include/Ritual.h"
#include "../include/Minion.h"
#include "../include/Game.h"
#include <iostream>

AuraPowerTrigger::AuraPowerTrigger(Ritual* ritual) : TriggeredAbility("Whenever a minion enters play under your control, it gains +1/+1", 1, "minionenters"), owner(ritual->getOwner()), ritual(ritual) {}

void AuraPowerTrigger::execute(Game* game) {
  // This will be called by the trigger manager
  // For now, just a placeholder - the actual logic will be in the overloaded version
  std::cout << "[DEBUG] AuraPowerTrigger::execute() called without minion parameter" << std::endl;
}

void AuraPowerTrigger::execute(Game* game, Minion* enteringMinion) {
  if (!ritual || !owner || !enteringMinion) return;
  
  // Check if the minion belongs to this ritual's owner
  if (enteringMinion->getOwner() != owner) return;
  
  if (ritual->canActivate()) {
    // For now, we'll just print the effect since we haven't implemented minion stat modification yet
    ritual->useCharges(1);
    std::cout << owner->getName() << "'s Aura of Power triggers! " << enteringMinion->getName() << " would gain +1/+1. " << ritual->getCharges() << " charges remaining." << std::endl;
  } 
  else {
    std::cout << owner->getName() << "'s Aura of Power has insufficient charges." << std::endl;
  }
}

std::unique_ptr<TriggeredAbility> AuraPowerTrigger::clone() const {
  return std::make_unique<AuraPowerTrigger>(ritual);
}
