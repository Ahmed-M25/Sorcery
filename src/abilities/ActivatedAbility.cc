#include "../include/abilities/ActivatedAbility.h"
#include "../include/core/Game.h"

ActivatedAbility::ActivatedAbility(const std::string& desc, int cost, std::function<void(Target, Game*)> func) : AbilityCommand{desc, cost}, abilityFunction{func} {}

void ActivatedAbility::execute(Target target, Game* game) {
  if (abilityFunction) {
    abilityFunction(target, game);
  }
}

std::unique_ptr<AbilityCommand> ActivatedAbility::clone() const {
  return std::make_unique<ActivatedAbility>(description, cost, abilityFunction);
}
