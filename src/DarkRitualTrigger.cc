#include "../include/DarkRitualTrigger.h"
#include "../include/Player.h"
#include "../include/Ritual.h"
#include "../include/Game.h"
#include <iostream>

DarkRitualTrigger::DarkRitualTrigger(Ritual* ritual) : TriggeredAbility{"At the start of your turn, gain 1 magic", 1, "start"}, owner{ritual->getOwner()}, ritual{ritual} {}

void DarkRitualTrigger::execute(Game* game) {
  if (!ritual || !owner) { return; } 

  if (game->getActivePlayer() != owner) { return; }
    
  if (ritual->canActivate()) {
    owner->gainMagic(1);
    ritual->useCharges(1);
    std::cout << owner->getName() << "'s Dark Ritual grants 1 magic. " << ritual->getCharges() << " charges remaining." << std::endl;
    } 
    else {
      std::cout << owner->getName() << "'s Dark Ritual has insufficient charges." << std::endl;
    }
}

std::unique_ptr<TriggeredAbility> DarkRitualTrigger::clone() const {
  return std::make_unique<DarkRitualTrigger>(ritual);
}
