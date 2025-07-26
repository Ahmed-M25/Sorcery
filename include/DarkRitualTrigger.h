#ifndef DARK_RITUAL_TRIGGER_H
#define DARK_RITUAL_TRIGGER_H

#include "TriggeredAbility.h"

class Player;
class Ritual;

class DarkRitualTrigger : public TriggeredAbility {
private:
  Player* owner;
  Ritual* ritual;

public:
  DarkRitualTrigger(Ritual* ritual);
    
  void execute(Game* game) override;
  Ritual* getRitual() const override { return ritual; }
  std::unique_ptr<TriggeredAbility> clone() const override;
};

#endif
