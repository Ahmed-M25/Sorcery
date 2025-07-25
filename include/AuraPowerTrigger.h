#ifndef AURA_POWER_TRIGGER_H
#define AURA_POWER_TRIGGER_H

#include "TriggeredAbility.h"

class Player;
class Ritual;
class Minion;

class AuraPowerTrigger : public TriggeredAbility {
private:
  Player* owner;
  Ritual* ritual;

public:
  AuraPowerTrigger(Ritual* ritual);
    
  void execute(Game* game) override;
  void execute(Game* game, Minion* enteringMinion);
  std::unique_ptr<TriggeredAbility> clone() const override;
};

#endif
