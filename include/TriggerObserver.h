#ifndef TRIGGEROBSERVER_H
#define TRIGGEROBSERVER_H

#include <string>

class Game;
class Ritual;
class Minion;

class TriggerObserver {
protected:
    std::string description;
    int cost;
    std::string triggerType;

public:
    TriggerObserver(std::string desc, int cost, std::string trigger);
    virtual ~TriggerObserver() = default;

    virtual void notify(const std::string& event, Game* game) = 0;
    virtual void notifyMinionEvent(const std::string& event, Game* game, Minion* minion) {
        // Default implementation just calls regular notify
        notify(event, game);
    }

    virtual Ritual* getRitual() const { return nullptr; }

    bool matchesTrigger(const std::string& eventType) const;
    std::string getTriggerType() const;
    int getCost() const;
    
    const std::string& getDescription() const { return description; }
};


#endif
