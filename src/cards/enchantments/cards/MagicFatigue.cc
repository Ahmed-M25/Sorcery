#include "cards/enchantments/cards/MagicFatigue.h"
#include "cards/enchantments/system/EnchantmentDecorator.h"
#include "core/Player.h"
#include "cards/base/Minion.h"
#include "core/Game.h"
#include <iostream>

MagicFatigue::MagicFatigue()
  : Enchantment("Magic Fatigue", 0, "Enchanted minion's activated ability costs 2 more") {}

std::unique_ptr<Card> MagicFatigue::clone() const {
  return std::make_unique<MagicFatigue>(*this);
}

void MagicFatigue::play(Target target, Game* game) {
    if (!target.isValidTarget(game) || target.Ritual() || target.targetsPlayer()) {
        std::cout << "Invalid target for Magic Fatigue.\n";
        return;
    }

    Player* owner = (target.getPlayerNum() == 1) ? game->getPlayer1() : game->getPlayer2();
    int idx = target.getPosition();
    Minion* minion = owner->getBoard().getMinion(idx);
    if (!minion) {
        std::cout << "No minion at that position.\n";
        return;
    }

    std::cout << "Magic Fatigue makes " << minion->getName() << "'s activated ability cost 2 more.\n";
    minion->addEnchantment(std::make_unique<MagicFatigueDecorator>());
}

MagicFatigueDecorator::MagicFatigueDecorator() {}

int MagicFatigueDecorator::getModifiedAttack(int baseAttack) const {
  return baseAttack; // Magic Fatigue doesn't modify attack
}

int MagicFatigueDecorator::getModifiedDefence(int baseDefence) const {
  return baseDefence; // Magic Fatigue doesn't modify defence
}

int MagicFatigueDecorator::getModifiedActions(int baseActions) const {
  return baseActions; // Magic Fatigue doesn't modify actions
}

int MagicFatigueDecorator::getModifiedAbilityCost(int baseCost) const {
  return baseCost + 2; // Magic Fatigue adds 2 to ability cost
}

bool MagicFatigueDecorator::isAbilitySilenced() const {
  return false; // Magic Fatigue doesn't silence abilities
}

std::string MagicFatigueDecorator::getName() const {
  return "Magic Fatigue";
} 