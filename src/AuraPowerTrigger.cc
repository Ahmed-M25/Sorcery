#include "../include/AuraPowerTrigger.h"
#include "../include/Player.h"
#include "../include/Ritual.h"
#include "../include/Minion.h"
#include "../include/Game.h"
#include <iostream>

AuraPowerTrigger::AuraPowerTrigger(Ritual* ritual) : TriggeredAbility("Whenever a minion enters play under your control, it gains +1/+1", 1, "minionenters"), owner(ritual->getOwner()), ritual(ritual) {}

void AuraPowerTrigger::execute(Game* game) {
  if (!ritual || !owner) return;
  
  // Get the entering minion from TriggerManager context
  Minion* enteringMinion = game->getTriggerManager().getCurrentEnteringMinion();
  if (!enteringMinion) return;
  
  // Check if the minion belongs to this ritual's owner
  if (enteringMinion->getOwner() != owner) return;
  
  if (ritual->canActivate()) {
    // Actually modify the minion's stats
    int newAttack = enteringMinion->getAttack() + 1;
    int newDefence = enteringMinion->getDefence() + 1;
    
    enteringMinion->setAttack(newAttack);
    enteringMinion->setDefence(newDefence);
    
    ritual->useCharges(1);
    std::cout << owner->getName() << "'s Aura of Power triggers! " << enteringMinion->getName() << " gains +1/+1 (" << newAttack << "/" << newDefence << "). " << ritual->getCharges() << " charges remaining." << std::endl;
  } 
  else {
    std::cout << owner->getName() << "'s Aura of Power has insufficient charges." << std::endl;
  }
}

std::unique_ptr<TriggeredAbility> AuraPowerTrigger::clone() const {
  return std::make_unique<AuraPowerTrigger>(ritual);
}
