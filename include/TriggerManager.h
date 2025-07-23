#ifndef TRIGGER_MANAGER_H
#define TRIGGER_MANAGER_H

#include <vector>
#include <string>
#include "TriggerObserver.h" 
#include "Player.h"
#include "Minion.h"

class Game; 

class TriggerManager {
private:
    std::vector<std::unique_ptr<TriggerObserver>> allObservers;

public:
    TriggerManager();

    void registerObserver(std::unique_ptr<TriggerObserver> observer);
    void unregisterObserver(std::unique_ptr<TriggerObserver> observer);

    void notifyStartOfTurn(Player* player, Game* game);
    void notifyEndOfTurn(Player* player, Game* game);
    void notifyMinionEnters(Minion* minion, Game* game);
    void notifyMinionLeaves(Minion* minion, Game* game);

    // Apply all observers in APNAP order for a given event
    void processInAPNAPOrder(const std::string& event, Game* game);

    // Remove all observers
    void clearAll();
};

#endif
