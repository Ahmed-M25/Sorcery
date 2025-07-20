#include "../include/Ritual.h"
#include "../include/Game.h"
#include "../include/TriggerObserver.h"
#include <iostream>

Ritual::Ritual(const std::string& name, int cost, const std::string& desc, int initialCharges, int activationCost)
  : Card(name, cost, desc),
    charges(initialCharges),
    actionCost(activationCost),
    triggerObserver(nullptr)
{
}

Ritual::~Ritual() = default;

void Ritual::play(Target target, Game* game) {
    std::cout << "[Ritual] " << name << " enters play with " << charges << " charges." << std::endl;
}

std::unique_ptr<Card> Ritual::clone() const {
    return std::make_unique<Ritual>(*this);
}

std::string Ritual::getType() const {
    return "Ritual";
}

void Ritual::trigger(Game* game) {
    std::cout << "[Ritual] " << name << " triggered, " << charges << " charges remaining." << std::endl;
}

bool Ritual::canActivate() const {
    return charges >= actionCost;
}

void Ritual::useCharges(int amount) {
    charges = std::max(0, charges - amount);
}

int Ritual::getCharges() const {
    return charges;
}

// void Ritual::addTriggerObserver(std::unique_ptr<TriggerObserver> observer) {}