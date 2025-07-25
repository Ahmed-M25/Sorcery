#include "../include/Ritual.h"
#include "../include/DarkRitualTrigger.h"
#include "../include/AuraPowerTrigger.h" 
#include "../include/StandstillTrigger.h"
#include "../include/Game.h"
#include "../include/TriggerObserver.h"
#include <iostream>

Ritual::Ritual(const std::string& name, int cost, const std::string& desc, int initialCharges, int activationCost)
  : Card(name, cost, desc),
    charges(initialCharges), actionCost(activationCost), triggerObserver(nullptr) {}

Ritual::~Ritual() = default;

void Ritual::play(Target target, Game* game) {
  std::cout << "[Debug] Ritual::play() called for " << name << std::endl;
}

std::unique_ptr<Card> Ritual::clone() const {
  auto cloned = std::make_unique<Ritual>(name, cost, description, charges, actionCost);
  cloned->setOwner(owner);
  return cloned;
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

void Ritual::setupTrigger(Player* owner) {
  if (name == "Dark Ritual") { 
    triggerObserver = std::make_unique<DarkRitualTrigger>(this);
  } 
  else if (name == "Aura of Power") {
    triggerObserver = std::make_unique<AuraPowerTrigger>(this);
  } 
  else if (name == "Standstill") {
    triggerObserver = std::make_unique<StandstillTrigger>(this);
  }
}

int Ritual::getCharges() const {
  return charges;
}

// void Ritual::addTriggerObserver(std::unique_ptr<TriggerObserver> observer) {}