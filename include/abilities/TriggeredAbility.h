#ifndef TRIGGEREDABILITY_H
#define TRIGGEREDABILITY_H

#include <memory>
#include "TriggerObserver.h"
#include "../core/Target.h"

class TriggeredAbility : public TriggerObserver {
public:
    TriggeredAbility(const std::string& desc, int cost, const std::string& trigger);

    void notify(const std::string& event, Game* game) override;

    virtual void execute(Game* game) = 0;

    virtual std::unique_ptr<TriggeredAbility> clone() const = 0;
};

#endif