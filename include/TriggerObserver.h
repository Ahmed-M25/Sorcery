#ifndef TRIGGEROBSERVER_H
#define TRIGGEROBSERVER_H

#include <string>

class Game;

class TriggerObserver {
protected:
    std::string description;
    int cost;
    std::string triggerType;

public:
    TriggerObserver(std::string desc, int cost, std::string trigger);
    virtual ~TriggerObserver() = default;

    virtual void notify(const std::string& event, Game* game) = 0;

    bool matchesTrigger(const std::string& eventType) const;
    std::string getTriggerType() const;
    int getCost() const;
};


#endif
