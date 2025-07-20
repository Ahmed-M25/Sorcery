#ifndef TRIGGEROBSERVER_H
#define TRIGGEROBSERVER_H

#include <string>

class Game;

class TriggerObserver {
public:
    explicit TriggerObserver(const std::string& desc, int cost, const std::string& triggerType);
    virtual ~TriggerObserver();

    virtual void notify(const std::string& event, Game* game) = 0;

    virtual TriggerObserver* clone() const = 0;

    std::string getTriggerType() const;

    bool matchesTrigger(const std::string& event) const;

protected:
    std::string triggerType;
    std::string description;
    int cost;
};

#endif
