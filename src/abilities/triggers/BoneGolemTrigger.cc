#include "abilities/triggers/BoneGolemTrigger.h"
#include "cards/base/Minion.h"
#include "core/Game.h"
#include <iostream>

BoneGolemTrigger::BoneGolemTrigger(Minion* src) : TriggeredAbility("Gain +1/+1 whenever a minion leaves play.", 0, "minionleaves"), source{src} {}

std::unique_ptr<TriggeredAbility> BoneGolemTrigger::clone() const {
  return std::make_unique<BoneGolemTrigger>(source);
}

void BoneGolemTrigger::execute(Game* game) {
  if (!source) return;
  
  // Gain +1/+1
  int newAttack = source->getAttack() + 1;
  int newDefence = source->getDefence() + 1;
  
  source->setAttack(newAttack);
  source->setDefence(newDefence);
  
  std::cout << source->getName() << " gains +1/+1 (" << newAttack << "/" << newDefence << "). Bone Golem trigger!" << std::endl;
}
