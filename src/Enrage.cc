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

EnchantmentDecorator* Enrage::createDecorator(Minion* target) const {
  return new EnrageDecorator(target);
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
    EnchantmentDecorator* deco = createDecorator(minion);
    owner->getBoard().replaceMinion(idx, std::unique_ptr<Minion>(deco));
}

EnrageDecorator::EnrageDecorator(Minion* minion)
  : EnchantmentDecorator(minion) {}

int EnrageDecorator::getAttack() const {
  return baseAttack * 2;
}

int EnrageDecorator::getDefence() const {
  return baseDefence * 2;
}
