#include "../include/Haste.h"
#include "../include/EnchantmentDecorator.h"
#include "../include/Player.h"
#include "../include/Minion.h"
#include "../include/Game.h"
#include <iostream>

Haste::Haste()
  : Enchantment("Haste", 1, "Give enchanted minion +2/+2") {}

std::unique_ptr<Card> Haste::clone() const {
  return std::make_unique<Haste>(*this);
}



void Haste::play(Target target, Game* game) {
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
    minion->addEnchantment(std::make_unique<HasteDecorator>());
}

HasteDecorator::HasteDecorator() {}

int HasteDecorator::getModifiedAttack(int baseAttack) const {
  return baseAttack + 2;
}

int HasteDecorator::getModifiedDefence(int baseDefence) const {
  return baseDefence + 2;
}

std::string HasteDecorator::getName() const {
  return "Giant Strength";
}

int HasteDecorator::getModifiedActions(int baseActions) const {
  return baseActions;
}