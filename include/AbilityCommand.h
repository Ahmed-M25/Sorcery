#ifndef ABILITYCOMMAND_H
#define ABILITYCOMMAND_H

#include <string>
#include <memory>
#include "Target.h"

class Game;

class AbilityCommand {
protected:
  std::string description;
  int cost;

public:
  AbilityCommand(const std::string& desc, int cost);
  virtual ~AbilityCommand() = default;

  virtual void execute(Target target, Game* game) = 0;
  virtual std::unique_ptr<AbilityCommand> clone() const = 0;

  int getCost() const { return cost; }
  const std::string& getDescription() const { return description; }
};

#endif