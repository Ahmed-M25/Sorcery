#ifndef TRIGGEREDABILITY_H
#define TRIGGEREDABILITY_H

#include "TriggerObserver.h"
#include "Target.h"

class TriggeredAbility : public TriggerObserver {
public:
    TriggeredAbility(std::string desc, int cost, std::string trigger);

    void notify(std::string event, Game* game) override;

    virtual void execute(Target target, Game* game) = 0;

    virtual std::unique_ptr<TriggeredAbility> clone() const = 0;
};

#endif