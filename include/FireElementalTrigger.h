#ifndef FIRE_ELEMENTAL_TRIGGER_H
#define FIRE_ELEMENTAL_TRIGGER_H

#include "TriggeredAbility.h"

class Minion;

class FireElementalTrigger : public TriggeredAbility {
private:
  Minion* source;  // The Fire Elemental itself

public:
  FireElementalTrigger(Minion* src);
  
  std::unique_ptr<TriggeredAbility> clone() const override;
  void execute(Game* game) override;
};

#endif
