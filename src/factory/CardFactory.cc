#include "factory/CardFactory.h"
#include "core/Game.h"
#include "core/Player.h"
#include "cards/base/Spell.h"
#include "cards/base/Minion.h"
#include "cards/base/Ritual.h"
#include "cards/spells/Unsummon.h"
#include "cards/spells/Banish.h"
#include "cards/spells/Blizzard.h"
#include "cards/spells/RaiseDead.h"
#include "cards/spells/Recharge.h"
#include "cards/enchantments/cards/GiantStrength.h"
#include "cards/enchantments/cards/Enrage.h"
#include "cards/enchantments/cards/Haste.h"
#include "cards/enchantments/cards/MagicFatigue.h"
#include "cards/spells/Silence.h"
#include "cards/spells/Disenchant.h"
#include "abilities/triggers/BoneGolemTrigger.h"
#include "abilities/triggers/FireElementalTrigger.h"
#include "abilities/triggers/PotionSellerTrigger.h"
#include "abilities/ActivatedAbility.h"
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

    // Triggerd ability minions
    {"Bone Golem", []() {
      auto minion =  std::make_unique<Minion>("Bone Golem", 2, 1, 3, "Gain +1/+1 whenever a minion leaves play.");

      auto trigger = std::make_unique<BoneGolemTrigger>(minion.get());
      minion->setTriggeredAbility(std::move(trigger));

      return minion;
    }},
    {"Fire Elemental", []() {
      auto minion = std::make_unique<Minion>("Fire Elemental", 2, 2, 2, "Whenever an opponent's minion enters play, deal 1 damage to it.");
      
      auto trigger = std::make_unique<FireElementalTrigger>(minion.get());
      minion->setTriggeredAbility(std::move(trigger));

      return minion;
    }},
    {"Potion Seller", []() {
      auto minion = std::make_unique<Minion>("Potion Seller", 2, 1, 3, "At the end of your turn, all your minions gain +0/+1.");

      auto trigger = std::make_unique<PotionSellerTrigger>(minion.get());
      minion->setTriggeredAbility(std::move(trigger));

      return minion;
    }},
    
    // Activated ability minions
    {"Novice Pyromancer", []() { 
      auto minion = std::make_unique<Minion>("Novice Pyromancer", 1, 0, 1, "Deal 1 damage to target minion.");
      
      // Add activated ability: Deal 1 damage to target minion (costs 1 magic)
      auto ability = std::make_unique<ActivatedAbility>("Deal 1 damage to target minion", 1,
        [](Target target, Game* game) {
          if (!target.isValidTarget(game) || target.Ritual()) {
            std::cout << "Invalid target for Novice Pyromancer ability." << std::endl;
            return;
          }
          
          Player* targetOwner = (target.getPlayerNum() == 1 ? game->getPlayer1() : game->getPlayer2());
          Minion* targetMinion = targetOwner->getBoard().getMinion(target.getPosition());
          
          if (targetMinion) {
            targetMinion->takeDamage(1, game);
            std::cout << "Novice Pyromancer deals 1 damage to " << targetMinion->getName() << std::endl;
          }
        });
      
      minion->setActivatedAbility(std::move(ability));
      return minion;
    }},
    {"Apprentice Summoner", []() {
      auto minion = std::make_unique<Minion>("Apprentice Summoner", 1, 1, 1, "Summon a 1/1 air elemental.");
      
      // Add activated ability: Summon a 1/1 air elemental (costs 1 magic)
      auto ability = std::make_unique<ActivatedAbility>("Summon a 1/1 air elemental", 1,
        [](Target target, Game* game) {
          Player* owner = game->getActivePlayer();
          
          if (owner->getBoard().isFull()) {
            std::cout << "Board is full! Cannot summon Air Elemental." << std::endl;
            return;
          }
          
          // Create and summon Air Elemental
          auto airElemental = std::make_unique<Minion>("Air Elemental", 0, 1, 1, "");
          airElemental->setOwner(owner);
          
          std::cout << "Apprentice Summoner summons an Air Elemental!" << std::endl;
          Minion* minionPtr = airElemental.get();
          owner->getBoard().addMinion(std::move(airElemental));
          
          // Trigger minion enters play
          game->getTriggerManager().notifyMinionEnters(minionPtr, game);
        });
      
      minion->setActivatedAbility(std::move(ability));
      return minion;
    }},
    {"Master Summoner", []() {
      auto minion = std::make_unique<Minion>("Master Summoner", 3, 2, 3, "Summon up to three 1/1 air elementals.");
      
      // Add activated ability: Summon up to three 1/1 air elementals (costs 2 magic)
      auto ability = std::make_unique<ActivatedAbility>("Summon up to three 1/1 air elementals", 2,
        [](Target target, Game* game) {
          Player* owner = game->getActivePlayer();
          
          int availableSlots = 5 - owner->getBoard().size();
          int summonsToCreate = std::min(3, availableSlots);
          
          if (summonsToCreate == 0) {
            std::cout << "Board is full! Cannot summon any Air Elementals." << std::endl;
            return;
          }
          
          std::cout << "Master Summoner summons " << summonsToCreate << " Air Elemental(s)!" << std::endl;
          
          for (int i = 0; i < summonsToCreate; i++) {
            auto airElemental = std::make_unique<Minion>("Air Elemental", 0, 1, 1, "");
            airElemental->setOwner(owner);
            
            Minion* minionPtr = airElemental.get();
            owner->getBoard().addMinion(std::move(airElemental));
            
            // Trigger minion enters play for each summoned minion
            game->getTriggerManager().notifyMinionEnters(minionPtr, game);
          }
        });
      
      minion->setActivatedAbility(std::move(ability));
      return minion;
    }},

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
    {"Haste", []() { return std::make_unique<Haste>(); }},
    {"Magic Fatigue", []() { return std::make_unique<MagicFatigue>(); }},
    {"Silence", []() { return std::make_unique<Silence>(); }},

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