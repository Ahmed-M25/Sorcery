#include "../include/Minion.h"
#include "../include/Game.h"
#include "../include/Player.h"
#include "../include/EnchantmentDecorator.h"
#include "../include/AbilityCommand.h"
#include <iostream>

Minion::Minion(const std::string& name, int cost, int att, int def, const std::string& desc) : Card{name, cost, desc}, baseAttack{att}, baseDefence{def}, currentActions{0} {}

Minion::~Minion() = default;

void Minion::play(Target target, Game* game) {
  std::cout << "Playing minion: " << name << " (" << baseAttack << "/" << baseDefence << ")" << std::endl;
  // TODO: Add to board in later steps
}

std::unique_ptr<Card> Minion::clone() const {
  auto cloned = std::make_unique<Minion>(name, cost, baseAttack, baseDefence, description);
  
  // Clone the single activated ability
  if (activatedAbility) {
    cloned->setActivatedAbility(activatedAbility->clone());
  }
  
  return cloned;
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

void Minion::setActivatedAbility(std::unique_ptr<AbilityCommand> ability) {
  activatedAbility = std::move(ability);
}

void Minion::useAbility(Target target, Game* game) {
  if (!activatedAbility) {
    std::cout << name << " has no activated ability!" << std::endl;
    return;
  }

  if (!hasActions()) {
    std::cout << name << " has no actions remaining!" << std::endl;
    return;
  }

  if (!owner->canAfford(activatedAbility->getCost())) {
    std::cout << "Not enough magic to use " << activatedAbility->getDescription() << std::endl;
    return;
  }

  // Use action and pay magic
  useAction();
  owner->payMagic(activatedAbility->getCost());

  activatedAbility->execute(target, game);

  std::cout << name << " uses " << activatedAbility->getDescription() << std::endl;
}

bool Minion::hasActivatedAbility() const {
  return activatedAbility != nullptr;
}

int Minion::getAbilityCost(int abilityIndex) const {
  return activatedAbility ? activatedAbility->getCost() : 0;
}

const std::string& Minion::getAbilityDescription(int abilityIndex) const {
  static const std::string empty = "";
  return activatedAbility ? activatedAbility->getDescription() : empty;
}

int Minion::getAttack() const {
  return baseAttack;
}

int Minion::getDefence() const {
  return baseDefence;
}

void Minion::setAttack(int att) {
  baseAttack = att;
}

void Minion::setDefence(int def) {
  baseDefence = def;
}

