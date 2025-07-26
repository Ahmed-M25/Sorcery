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
  Player* owner = this->getOwner();
  if (!owner) {
    std::cout << "Error: Ritual has no owner!" << std::endl;
    return;
  }

  // Remove existing ritual if player has one
  if (owner->getRitual()) {
    // Unregister old ritual's trigger
    if (owner->getRitual()->getTriggerObserver()) {
      game->getTriggerManager().unregisterObserver(owner->getRitual()->getTriggerObserver());
      std::cout << owner->getName() << "'s " << owner->getRitual()->getName() 
                << " is replaced by " << name << "." << std::endl;
    }
  } else {
    std::cout << owner->getName() << " plays " << name << " with " 
              << charges << " charges." << std::endl;
  }

  // Set this ritual as the player's active ritual  
  owner->setRitual(std::unique_ptr<Ritual>(this));

  // Setup the ritual's trigger
  owner->getRitual()->setupTrigger(owner);

  // Register trigger with TriggerManager
  if (owner->getRitual()->getTriggerObserver()) {
    // We need to create a separate trigger instance for the TriggerManager
    std::unique_ptr<TriggerObserver> globalTrigger;
    
    if (name == "Dark Ritual") {
      globalTrigger = std::make_unique<DarkRitualTrigger>(owner->getRitual());
    } else if (name == "Aura of Power") {
      globalTrigger = std::make_unique<AuraPowerTrigger>(owner->getRitual());
    } else if (name == "Standstill") {
      globalTrigger = std::make_unique<StandstillTrigger>(owner->getRitual());
    }
    
    if (globalTrigger) {
      game->getTriggerManager().registerObserver(std::move(globalTrigger));
    }
  }
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

void Ritual::addCharges(int amount) {
  charges += amount;
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