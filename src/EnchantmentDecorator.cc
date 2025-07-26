#include "../include/EnchantmentDecorator.h"

EnchantmentDecorator::EnchantmentDecorator(Minion* minion)
  : Minion(*minion), decoratedMinion(minion) {}

EnchantmentDecorator::~EnchantmentDecorator() {}

void EnchantmentDecorator::attackPlayer(Player* player, Game* game) {
  decoratedMinion->attackPlayer(player, game);
}

void EnchantmentDecorator::attackMinion(Minion* minion, Game* game) {
  decoratedMinion->attackMinion(minion, game);
}

void EnchantmentDecorator::takeDamage(int damage, Game* game) {
  decoratedMinion->takeDamage(damage, game);
}

void EnchantmentDecorator::die(Game* game) {
  decoratedMinion->die(game);
}

void EnchantmentDecorator::restoreActions() {
  decoratedMinion->restoreActions();
}

bool EnchantmentDecorator::hasActions() const {
  return decoratedMinion->hasActions();
}
