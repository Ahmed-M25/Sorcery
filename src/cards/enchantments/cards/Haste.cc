#include "cards/enchantments/cards/Haste.h"
#include "cards/enchantments/system/EnchantmentDecorator.h"
#include "core/Player.h"
#include "cards/base/Minion.h"
#include "core/Game.h"
#include <iostream>

Haste::Haste()
  : Enchantment("Haste", 1, "Enchanted minion gains +1 action each turn") {}

std::unique_ptr<Card> Haste::clone() const {
  return std::make_unique<Haste>(*this);
}

void Haste::play(Target target, Game* game) {
    if (!target.isValidTarget(game) || target.Ritual() || target.targetsPlayer()) {
        std::cout << "Invalid target for Haste.\n";
        return;
    }

    Player* owner = (target.getPlayerNum() == 1) ? game->getPlayer1() : game->getPlayer2();
    int idx = target.getPosition();
    Minion* minion = owner->getBoard().getMinion(idx);
    if (!minion) {
        std::cout << "No minion at that position.\n";
        return;
    }

    std::cout << "Haste gives " << minion->getName() << " +1 action each turn.\n";
    minion->addEnchantment(std::make_unique<HasteDecorator>());
}

HasteDecorator::HasteDecorator() {}

int HasteDecorator::getModifiedAttack(int baseAttack) const {
  return baseAttack; // Haste doesn't modify attack
}

int HasteDecorator::getModifiedDefence(int baseDefence) const {
  return baseDefence; // Haste doesn't modify defence
}

std::string HasteDecorator::getName() const {
  return "Haste";
}

int HasteDecorator::getModifiedActions(int baseActions) const {
  return baseActions + 1; // Haste gives +1 action
}

int HasteDecorator::getModifiedAbilityCost(int baseCost) const {
  return baseCost; // Haste doesn't modify ability costs
}

bool HasteDecorator::isAbilitySilenced() const {
  return false; // Haste doesn't silence abilities
}