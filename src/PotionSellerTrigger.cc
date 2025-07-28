#include "../include/PotionSellerTrigger.h"
#include "../include/Minion.h"
#include "../include/Game.h"
#include "../include/Player.h"
#include <iostream>

PotionSellerTrigger::PotionSellerTrigger(Minion* src)
  : TriggeredAbility("At the end of your turn, all your minions gain +0/+1.", 0, "end"),
    source(src) {}

std::unique_ptr<TriggeredAbility> PotionSellerTrigger::clone() const {
  return std::make_unique<PotionSellerTrigger>(source);
}

void PotionSellerTrigger::execute(Game* game) {
  if (!source) return;
  
  // Check if it's the owner's turn ending
  Player* owner = source->getOwner();
  if (!owner || game->getActivePlayer() != owner) return;
  
  // Give all owner's minions +0/+1
  std::vector<Minion*> minions = owner->getBoard().getMinions();
  
  if (minions.empty()) return;
  
  std::cout << source->getName() << " grants all your minions +0/+1. Potion Seller trigger!" << std::endl;
  
  for (Minion* minion : minions) {
    int newDefence = minion->getDefence() + 1;
    minion->setDefence(newDefence);
    std::cout << "  " << minion->getName() << " gains +0/+1 (" << minion->getAttack() << "/" << newDefence << ")" << std::endl;
  }
}
