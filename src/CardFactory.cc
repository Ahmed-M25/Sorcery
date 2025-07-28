#include "../include/CardFactory.h"
#include "../include/Spell.h"
#include "../include/Minion.h"
#include "../include/Ritual.h"
#include "../include/Unsummon.h"
#include "../include/Banish.h"
#include "../include/Blizzard.h"
#include "../include/RaiseDead.h"
#include "../include/Recharge.h"
#include "../include/GiantStrength.h"
#include "../include/Enrage.h"
#include "../include/Disenchant.h"
#include <iostream>
#include <unordered_map>
#include <functional>

void CardFactory::initializeCards() {
  // Nothing needed for now
}

std::unique_ptr<Card> CardFactory::createCard(const std::string& name) {
  static std::unordered_map<std::string, std::function<std::unique_ptr<Card>()>> cardMap = {
    // Minions
    {"Air Elemental", []() { return std::make_unique<Minion>("Air Elemental", 0, 1, 1, ""); }},
    {"Earth Elemental", []() { return std::make_unique<Minion>("Earth Elemental", 3, 4, 4, ""); }},
    {"Bone Golem", []() { return std::make_unique<Minion>("Bone Golem", 2, 1, 3, "Gain +1/+1 whenever a minion leaves play."); }},
    {"Fire Elemental", []() { return std::make_unique<Minion>("Fire Elemental", 2, 2, 2, "Whenever an opponent's minion enters play, deal 1 damage to it."); }},
    {"Potion Seller", []() { return std::make_unique<Minion>("Potion Seller", 2, 1, 3, "At the end of your turn, all your minions gain +0/+1."); }},
    {"Novice Pyromancer", []() { return std::make_unique<Minion>("Novice Pyromancer", 1, 0, 1, "Deal 1 damage to target minion."); }},
    {"Apprentice Summoner", []() { return std::make_unique<Minion>("Apprentice Summoner", 1, 1, 1, "Summon a 1/1 air elemental."); }},
    {"Master Summoner", []() { return std::make_unique<Minion>("Master Summoner", 3, 2, 3, "Summon up to three 1/1 air elementals."); }},

    // Spells
    {"Unsummon", []() { return std::make_unique<Unsummon>("Unsummon", 1, "Return target minion to its owner's hand."); }},
    {"Banish", []() { return std::make_unique<Banish>("Banish", 2, "Destroy target minion or ritual."); }},
    {"Blizzard", []() { return std::make_unique<Blizzard>("Blizzard", 3, "Deal 2 damage to all minions."); }},
    {"Raise Dead", []() { return std::make_unique<RaiseDead>("Raise Dead", 1, "Resurrect the top minion in your graveyard and set its defence to 1."); }},
    {"Recharge", []() { return std::make_unique<Recharge>("Recharge", 1, "Your ritual gains 3 charges."); }},
    {"Disenchant", []() { return std::make_unique<Disenchant>("Disenchant", 1, "Destroy the top enchantment on target minion."); }},


    
    // Enhancements
    {"Giant Strength", []() { return std::make_unique<GiantStrength>(); }},
    {"Enrage", []() { return std::make_unique<Enrage>(); }},

    // Rituals
    {"Aura of Power", []() { return std::make_unique<Ritual>("Aura of Power", 1, "Whenever a minion enters play under your control, it gains +1/+1", 4, 1); }},
    {"Standstill", []() { return std::make_unique<Ritual>("Standstill", 3, "Whenever a minion enters play, destroy it", 4, 2); }},
    {"Dark Ritual", []() { return std::make_unique<Ritual>("Dark Ritual", 0, "At the start of your turn, gain 1 mana", 5, 1); }}, 
  };

  auto it = cardMap.find(name);
  if (it != cardMap.end()) {
    return it->second();
  }

  std::cerr << "Warning: Unknown card name: " << name << std::endl;
  return nullptr;
}