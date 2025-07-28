#ifndef ACTIVATEDABILITY_H
#define ACTIVATEDABILITY_H

#include "AbilityCommand.h"
#include <functional>

class ActivatedAbility : public AbilityCommand {
private:
  std::function<void(Target, Game*)> abilityFunction;

public:
  ActivatedAbility(const std::string& desc, int cost, std::function<void(Target target, Game* game)> func);

  void execute(Target target, Game* game) override;
  std::unique_ptr<AbilityCommand> clone() const override;
};

#endif
