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
  std::cout << name << " attacks player for " << baseAttack << " damage!" << std::endl;
  // TODO: Implement damage to a player
}

void Minion::attackMinion(Minion* target, Game* game) {
  std::cout << name << " attacks " << target->name << "!" << std::endl;
}

void Minion::takeDamage(int damage, Game* game) {
  baseDefence -= damage;
  std::cout << name << " takes " << damage << " damage. Defence: " << baseDefence << std::endl;
  if (baseDefence <= 0) {
    die(game);
  }
}

void Minion::die(Game* game) {
  std::cout << name << " dies!" << std::endl;
  // TODO: Move to graveyard 
}

void Minion::restoreActions() {
  currentActions = 1;
}

bool Minion::hasActions() const {
  return currentActions > 0;
}

int Minion::getAttack() const {
  return baseAttack;
}

int Minion::getDefence() const {
  return baseDefence;
}