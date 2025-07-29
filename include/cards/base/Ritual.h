#ifndef RITUAL_H
#define RITUAL_H

#include "Card.h"
#include "../../abilities/TriggerObserver.h"
#include <memory>

class Ritual : public Card {
public:
    Ritual(const std::string& name, int cost, const std::string& desc, int initialCharges, int activationCost);
    ~Ritual() override;
    
    void play(Target target, Game* game) override;

    std::unique_ptr<Card> clone() const override;
    
    std::string getType() const override;

    void trigger(Game* game);

    bool canActivate() const;

    void useCharges(int amount);
    int getCharges() const;

    void addCharges(int amount);

    int getActivationCost() const { return actionCost; }
    
    void addTriggerObserver(TriggerObserver* observer);

    // Trigger management
    void setupTrigger(Player* owner);
    TriggerObserver* getTriggerObserver() const { return triggerObserver.get(); }

private:
    int charges; // Number of charges the ritual has
    int actionCost; // Cost in actions to activate the ritual
    std::unique_ptr<TriggerObserver> triggerObserver; // Observer for handling triggers related to the ritual
};

#endif