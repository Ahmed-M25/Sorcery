#include "cards/enchantments/cards/GiantStrength.h"
#include "cards/enchantments/system/EnchantmentDecorator.h"
#include "core/Player.h"
#include "cards/base/Minion.h"
#include "core/Game.h"
#include <iostream>

GiantStrength::GiantStrength()
  : Enchantment("Giant Strength", 1, "Give enchanted minion +2/+2") {}

std::unique_ptr<Card> GiantStrength::clone() const {
  return std::make_unique<GiantStrength>(*this);
}



void GiantStrength::play(Target target, Game* game) {
    if (!target.isValidTarget(game) || target.Ritual() || target.targetsPlayer()) {
        std::cout << "Invalid target for Giant Strength.\n";
        return;
    }

    Player* owner = (target.getPlayerNum() == 1) ? game->getPlayer1() : game->getPlayer2();
    int idx = target.getPosition();
    Minion* minion = owner->getBoard().getMinion(idx);
    if (!minion) {
        std::cout << "No minion at that position.\n";
        return;
    }

    std::cout << "Giant Strength gives " << minion->getName() << " +2/+2.\n";
    minion->addEnchantment(std::make_unique<GiantStrengthDecorator>());
}

GiantStrengthDecorator::GiantStrengthDecorator() {}

int GiantStrengthDecorator::getModifiedAttack(int baseAttack) const {
  return baseAttack + 2;
}

int GiantStrengthDecorator::getModifiedDefence(int baseDefence) const {
  return baseDefence + 2;
}

std::string GiantStrengthDecorator::getName() const {
  return "Giant Strength";
}

int GiantStrengthDecorator::getModifiedActions(int baseActions) const {
  return baseActions;
}

int GiantStrengthDecorator::getModifiedAbilityCost(int baseCost) const {
  return baseCost; // Giant Strength doesn't modify ability costs
}

bool GiantStrengthDecorator::isAbilitySilenced() const {
  return false; // Giant Strength doesn't silence abilities
}