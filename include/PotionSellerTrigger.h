#ifndef POTION_SELLER_TRIGGER_H
#define POTION_SELLER_TRIGGER_H

#include "TriggeredAbility.h"

class Minion;

class PotionSellerTrigger : public TriggeredAbility {
private:
  Minion* source;  // The Potion Seller itself

public:
  PotionSellerTrigger(Minion* src);
  
  std::unique_ptr<TriggeredAbility> clone() const override;
  void execute(Game* game) override;
};

#endif
