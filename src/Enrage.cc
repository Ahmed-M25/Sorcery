#include "../include/Enrage.h"
#include "../include/EnchantmentDecorator.h"
#include "../include/Player.h"
#include "../include/Minion.h"
#include "../include/Game.h"
#include <iostream>

Enrage::Enrage()
  : Enchantment("Enrage", 2, "Give enchanted minion *2/*2") {}

std::unique_ptr<Card> Enrage::clone() const {
  return std::make_unique<Enrage>(*this);
}



void Enrage::play(Target target, Game* game) {
    if (!target.isValidTarget(game) || target.Ritual() || target.targetsPlayer()) {
        std::cout << "Invalid target for Enrage.\n";
        return;
    }

    Player* owner = (target.getPlayerNum() == 1) ? game->getPlayer1() : game->getPlayer2();
    int idx = target.getPosition();
    Minion* minion = owner->getBoard().getMinion(idx);
    if (!minion) {
        std::cout << "No minion at that position.\n";
        return;
    }

    std::cout << "Enrage gives " << minion->getName() << " *2/*2.\n";
    minion->addEnchantment(std::make_unique<EnrageDecorator>());
}

EnrageDecorator::EnrageDecorator() {}

int EnrageDecorator::getModifiedAttack(int baseAttack) const {
  return baseAttack * 2;
}

int EnrageDecorator::getModifiedDefence(int baseDefence) const {
  return baseDefence * 2;
}

std::string EnrageDecorator::getName() const {
  return "Enrage";
}

int EnrageDecorator::getModifiedActions(int baseActions) const {
  return baseActions;
}

int EnrageDecorator::getModifiedAbilityCost(int baseCost) const {
  return baseCost; // Enrage doesn't modify ability costs
}

bool EnrageDecorator::isAbilitySilenced() const {
  return false; // Enrage doesn't silence abilities
}