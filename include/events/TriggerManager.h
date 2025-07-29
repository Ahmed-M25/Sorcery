#ifndef TRIGGER_MANAGER_H
#define TRIGGER_MANAGER_H

#include <vector>
#include <string>
#include "../abilities/TriggerObserver.h" 
#include "../core/Player.h"
#include "../cards/base/Minion.h"

class Game; 

class TriggerManager {
private:
    std::vector<std::unique_ptr<TriggerObserver>> allObservers;
    Minion* currentEnteringMinion = nullptr;

public:
    TriggerManager();

    void registerObserver(std::unique_ptr<TriggerObserver> observer);
    void unregisterObserver(TriggerObserver* observer);

    void notifyStartOfTurn(Player* player, Game* game);
    void notifyEndOfTurn(Player* player, Game* game);
    void notifyMinionEnters(Minion* minion, Game* game);
    void notifyMinionLeaves(Minion* minion, Game* game);

    Minion* getCurrentEnteringMinion() const { return currentEnteringMinion; }

    // Apply all observers in APNAP order for a given event
    void processInAPNAPOrder(const std::string& event, Game* game);

    // Remove all observers
    void clearAll();
};

#endif
