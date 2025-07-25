#include "../include/TriggerManager.h"
#include "../include/TriggerObserver.h"
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
    for (const auto& observer : allObservers) {
        if (observer->matchesTrigger(event)) {
            observer->notify(event, game);
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
    processInAPNAPOrder("minionenters", game);
}

void TriggerManager::notifyMinionLeaves(Minion* minion, Game* game) {
    processInAPNAPOrder("minionleaves", game);
}

void TriggerManager::clearAll() {
    allObservers.clear();
}
