#include "../include/TriggerManager.h"
#include "../include/TriggerObserver.h"
#include "../include/TriggeredAbility.h"
#include "../include/Game.h"
#include "../include/Player.h"
#include "../include/Minion.h"
#include <algorithm> 

TriggerManager::TriggerManager() {}

void TriggerManager::registerObserver(std::unique_ptr<TriggerObserver> observer) {
  allObservers.push_back(std::move(observer));
}

void TriggerManager::unregisterObserver(TriggerObserver* observer) {
  for (auto it = allObservers.begin(); it != allObservers.end(); ++it) {
    if (it->get() == observer) {
      allObservers.erase(it);
      break;
    }
  }
}

void TriggerManager::processInAPNAPOrder(const std::string& event, Game* game) {
  Player* activePlayer = game->getActivePlayer();
  Player* inactivePlayer = game->getInactivePlayer();
  
  if (!activePlayer || !inactivePlayer) return;
  
  // Active player's minions (left to right)
  std::vector<Minion*> activeMinions = activePlayer->getBoard().getMinions();
  for (Minion* minion : activeMinions) {
    if (minion->hasTriggeredAbility() && !minion->isAbilitySilenced()) {
      TriggeredAbility* trigger = minion->getTriggeredAbility();
      if (trigger && trigger->matchesTrigger(event)) {
        trigger->notify(event, game);
      }
    }
  } 
  
  // Active player's ritual
  for (const auto& observer : allObservers) {
    if (observer->matchesTrigger(event)) {
      Ritual* ritual = observer->getRitual();
      if (ritual && ritual->getOwner() == activePlayer) {
        observer->notify(event, game);
      }
    }
  }
  
  // Inactive player's minions (left to right)  
  std::vector<Minion*> inactiveMinions = inactivePlayer->getBoard().getMinions();
  for (Minion* minion : inactiveMinions) {
    if (minion and minion->hasTriggeredAbility() && !minion->isAbilitySilenced()) {
      TriggeredAbility* trigger = minion->getTriggeredAbility();
      if (trigger->matchesTrigger(event)) {
        trigger->notify(event, game);
      }
    }
  }
  
  // Inactive player's ritual
  for (const auto& observer : allObservers) {
    if (observer->matchesTrigger(event)) {
      Ritual* ritual = observer->getRitual();
      if (ritual && ritual->getOwner() == inactivePlayer) {
        observer->notify(event, game);
      }
    }
  }
}

void TriggerManager::notifyStartOfTurn(Player* player, Game* game) {
  processInAPNAPOrder("start", game);
}

void TriggerManager::notifyEndOfTurn(Player* player, Game* game) {
  processInAPNAPOrder("end", game);
}

void TriggerManager::notifyMinionEnters(Minion* minion, Game* game) {
  currentEnteringMinion = minion;  // Store context
  processInAPNAPOrder("minionenters", game);
  currentEnteringMinion = nullptr;  // Clear context
}

void TriggerManager::notifyMinionLeaves(Minion* minion, Game* game) {
  processInAPNAPOrder("minionleaves", game);
}

void TriggerManager::clearAll() {
  allObservers.clear();
}
