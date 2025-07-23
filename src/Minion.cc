#include "../include/Minion.h"
#include "../include/Game.h"
#include "../include/Player.h"
#include <iostream>

Minion::Minion(const std::string& name, int cost, int att, int def, const std::string& desc) : Card{name, cost, desc}, baseAttack{att}, baseDefence{def}, currentActions{0} {}

void Minion::play(Target target, Game* game) {
  std::cout << "Playing minion: " << name << " (" << baseAttack << "/" << baseDefence << ")" << std::endl;
  // TODO: Add to board in later steps
}

std::unique_ptr<Card> Minion::clone() const {
  return std::make_unique<Minion>(name, cost, baseAttack, baseDefence, description);
}

std::string Minion::getType() const {
  return "Minion";
}

void Minion::attackPlayer(Player* target, Game* game) {
  std::cout << name << " attacks " << target->getName() << " for " << getAttack() << " damage!\n";
  // TODO: Implement damage to a player
  target->takeDamage(this->getAttack());
}

void Minion::attackMinion(Minion* target, Game* game) {
  if (!target) {
    std::cout << "Invalid target for attack!\n";
    return;
  }

  std::cout << name << " (" << getAttack() << "/" << getDefence() << ") attacks " << target->name << " (" << target->getAttack() << "/" << target->getDefence() << ")!\n";

  // Store original stats for damage calculation
  int attackerDamage = this->getAttack();
  int defenderDamage = target->getAttack();

  // Apply damage simultaneously
  this->takeDamage(defenderDamage, game);
  target->takeDamage(attackerDamage, game);
}

void Minion::takeDamage(int damage, Game* game) {
  baseDefence -= damage;
  std::cout << name << " takes " << damage << " damage. Defence: " << baseDefence << std::endl;
  if (baseDefence <= 0) {
    this->die(game);
  }
}

void Minion::die(Game* game) {
  std::cout << name << " dies!" << std::endl;
  
  Player* owner = this->getOwner();
  if (owner) {
    auto deadMinion = owner->getBoard().removeMinion(this);
    if (deadMinion) {
      owner->getGraveyard().addMinion(std::move(deadMinion));
    }
  }
}

void Minion::restoreActions() {
  currentActions = 1;
}

bool Minion::hasActions() const {
  return currentActions > 0;
}

void Minion::useAction() {
  if (currentActions > 0) {
    currentActions--;
  }
}

int Minion::getAttack() const {
  return baseAttack;
}

int Minion::getDefence() const {
  return baseDefence;
}