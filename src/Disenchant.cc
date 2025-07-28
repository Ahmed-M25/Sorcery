#include "../include/Disenchant.h"
#include "../include/Game.h"
#include "../include/Player.h"
#include "../include/EnchantmentDecorator.h"
#include <iostream>

Disenchant::Disenchant(const std::string& name, int cost, const std::string& desc)
  : Spell(name, cost, desc) {}

std::unique_ptr<Card> Disenchant::clone() const {
  return std::make_unique<Disenchant>(getName(), getCost(), getDescription());
}



void Disenchant::play(Target target, Game* game) {
  if (!target.isValidTarget(game) || target.Ritual() || target.targetsPlayer()) {
    std::cout << "Invalid target for Disenchant.\n";
    return;
  }

  Player* owner = (target.getPlayerNum() == 1) ? game->getPlayer1() : game->getPlayer2();
  int idx = target.getPosition();
  Minion* minion = owner->getBoard().getMinion(idx);
  if (!minion) {
    std::cout << "No minion at that position.\n";
    return;
  }

  if (minion->hasEnchantments()) {
    minion->removeTopEnchantment();
    std::cout << "Disenchant removes the top enchantment from " << minion->getName() << ".\n";
  } else {
    std::cout << "No enchantment to remove from " << minion->getName() << ".\n";
  }
} 