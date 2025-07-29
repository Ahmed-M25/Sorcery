#include "../include/abilities/TriggerObserver.h"

TriggerObserver::TriggerObserver(std::string desc, int cost, std::string trigger)
    : description{desc}, cost{cost}, triggerType{trigger} {}

bool TriggerObserver::matchesTrigger(const std::string& eventType) const {
    return triggerType == eventType;
}

std::string TriggerObserver::getTriggerType() const {
    return triggerType;
}

int TriggerObserver::getCost() const {
    return cost;
}
