#include "../include/EnchantmentDecorator.h"
#include "../include/Player.h"
#include "../include/Game.h"
#include "../include/Board.h"
#include <iostream>

EnchantmentDecorator::EnchantmentDecorator(Minion* minion)
  : Minion(minion->getName(), minion->getCost(), minion->getAttack(), minion->getDefence(), minion->getDescription()), 
    baseAttack(minion->getAttack()), baseDefence(minion->getDefence()) {}

EnchantmentDecorator::~EnchantmentDecorator() {}

void EnchantmentDecorator::attackPlayer(Player* player, Game* game) {
  // Use the decorator's own stats for attack
  std::cout << getName() << " attacks " << player->getName() << " for " << getAttack() << " damage!\n";
  player->takeDamage(getAttack());
}

void EnchantmentDecorator::attackMinion(Minion* minion, Game* game) {
  if (!minion) {
    std::cout << "Invalid target for attack!\n";
    return;
  }

  std::cout << getName() << " (" << getAttack() << "/" << getDefence() << ") attacks " << minion->getName() << " (" << minion->getAttack() << "/" << minion->getDefence() << ")!\n";

  // Store original stats for damage calculation
  int attackerDamage = this->getAttack();
  int defenderDamage = minion->getAttack();

  // Apply damage simultaneously
  this->takeDamage(defenderDamage, game);
  minion->takeDamage(attackerDamage, game);
}

void EnchantmentDecorator::takeDamage(int damage, Game* game) {
  baseDefence -= damage;
  std::cout << getName() << " takes " << damage << " damage. Defence: " << baseDefence << std::endl;
  if (baseDefence <= 0) {
    this->die(game);
  }
}

void EnchantmentDecorator::die(Game* game) {
  std::cout << getName() << " dies!" << std::endl;
  
  // Notify TriggerManager that this minion is leaving play
  game->getTriggerManager().notifyMinionLeaves(this, game);
  
  Player* owner = this->getOwner();
  if (owner) {
    auto deadMinion = owner->getBoard().removeMinion(this);
    if (deadMinion) {
      owner->getGraveyard().addMinion(std::move(deadMinion));
    }
  }
}

void EnchantmentDecorator::restoreActions() {
  currentActions = 1;
}

bool EnchantmentDecorator::hasActions() const {
  return currentActions > 0;
}
