#ifndef RITUAL_H
#define RITUAL_H

#include "Card.h"
#include "TriggerObserver.h"

class Ritual : public Card {
public:
    Ritual(const std::string& name, int cost, const std::string& desc, int charges, int actCost);
    ~Ritual() override;
    
    void play(Target target, Game* game) override;

    std::unique_ptr<Card> clone() const override;
    
    std::string getType() const override;

    void trigger(Game* game);

    bool canActivate() const;

    void useCharges(int amount);
    int getCharges() const;
    
    void addTriggerObserver(TriggerObserver* observer);

private:
    int charges; // Number of charges the ritual has
    int actionCost; // Cost in actions to activate the ritual
    TriggerObserver* triggerObserver; // Observer for handling triggers related to the ritual
};

#endif