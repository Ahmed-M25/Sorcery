#include "cards/spells/Silence.h"
#include "cards/enchantments/system/EnchantmentDecorator.h"
#include "core/Player.h"
#include "cards/base/Minion.h"
#include "core/Game.h"
#include <iostream>

Silence::Silence()
  : Enchantment("Silence", 1, "Enchanted minion cannot use abilities") {}

std::unique_ptr<Card> Silence::clone() const {
  return std::make_unique<Silence>(*this);
}

void Silence::play(Target target, Game* game) {
    if (!target.isValidTarget(game) || target.Ritual() || target.targetsPlayer()) {
        std::cout << "Invalid target for Silence.\n";
        return;
    }

    Player* owner = (target.getPlayerNum() == 1) ? game->getPlayer1() : game->getPlayer2();
    int idx = target.getPosition();
    Minion* minion = owner->getBoard().getMinion(idx);
    if (!minion) {
        std::cout << "No minion at that position.\n";
        return;
    }

    std::cout << "Silence prevents " << minion->getName() << " from using abilities.\n";
    minion->addEnchantment(std::make_unique<SilenceDecorator>());
}

SilenceDecorator::SilenceDecorator() {}

int SilenceDecorator::getModifiedAttack(int baseAttack) const {
  return baseAttack; // Silence doesn't modify attack
}

int SilenceDecorator::getModifiedDefence(int baseDefence) const {
  return baseDefence; // Silence doesn't modify defence
}

int SilenceDecorator::getModifiedActions(int baseActions) const {
  return baseActions; // Silence doesn't modify actions
}

int SilenceDecorator::getModifiedAbilityCost(int baseCost) const {
  return baseCost; // Silence doesn't modify ability cost (abilities are just disabled)
}

bool SilenceDecorator::isAbilitySilenced() const {
  return true; // Silence prevents ability use
}

std::string SilenceDecorator::getName() const {
  return "Silence";
} 