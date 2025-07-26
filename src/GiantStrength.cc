#include "../include/GiantStrength.h"
#include "../include/EnchantmentDecorator.h"
#include "../include/Player.h"
#include "../include/Minion.h"
#include "../include/Game.h"
#include <iostream>

GiantStrength::GiantStrength()
  : Enchantment("Giant Strength", 1, "Give enchanted minion +2/+2") {}

std::unique_ptr<Card> GiantStrength::clone() const {
  return std::make_unique<GiantStrength>(*this);
}

EnchantmentDecorator* GiantStrength::createDecorator(Minion* target) const {
  return new GiantStrengthDecorator(target);
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

    // Print before replacing, or use deco->getName() after
    std::cout << "Giant Strength gives " << minion->getName() << " +2/+2.\n";
    EnchantmentDecorator* deco = createDecorator(minion);
    owner->getBoard().replaceMinion(idx, std::unique_ptr<Minion>(deco));
}

GiantStrengthDecorator::GiantStrengthDecorator(Minion* minion)
  : EnchantmentDecorator(minion) {}

int GiantStrengthDecorator::getAttack() const {
  return baseAttack + 2;
}

int GiantStrengthDecorator::getDefence() const {
  return baseDefence + 2;
}
