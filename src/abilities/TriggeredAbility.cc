#include "../include/abilities/TriggeredAbility.h"

TriggeredAbility::TriggeredAbility(const std::string &desc, int cost, const std::string &triggerType)
  : TriggerObserver(desc, cost, triggerType)
{}

void TriggeredAbility::notify(const std::string &event, Game* game) {
  if (matchesTrigger(event)) {
    execute(game);
  }
}
