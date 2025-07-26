#ifndef STANDSTILL_TRIGGER_H
#define STANDSTILL_TRIGGER_H

#include "TriggeredAbility.h"

class Player;
class Ritual;
class Minion;

class StandstillTrigger : public TriggeredAbility {
private:
  Player* owner;
  Ritual* ritual;

public:
  StandstillTrigger(Ritual* ritual);
  
  void execute(Game* game) override;
  void execute(Game* game, Minion* enteringMinion);
  Ritual* getRitual() const override { return ritual; }
  std::unique_ptr<TriggeredAbility> clone() const override;
};

#endif
