#include "../include/Minion.h"
#include "../include/Game.h"
#include "../include/Player.h"
#include "../include/EnchantmentDecorator.h"
#include "../include/EnchantmentList.h"
#include "../include/TriggeredAbility.h"
#include "../include/AbilityCommand.h"
#include <iostream>

Minion::Minion(const std::string& name, int cost, int att, int def, const std::string& desc) : Card{name, cost, desc}, baseAttack{att}, baseDefence{def}, currentActions{0}, enchantments{std::make_unique<EnchantmentList>()} {}

Minion::~Minion() = default;

void Minion::play(Target target, Game* game) {
  std::cout << "Playing minion: " << name << " (" << baseAttack << "/" << baseDefence << ")" << std::endl;
  // TODO: Add to board in later steps
}

std::unique_ptr<Card> Minion::clone() const {
  auto cloned = std::make_unique<Minion>(name, cost, baseAttack, baseDefence, description);
  
  // Clone the triggered ability
  if (triggeredAbility) {
    cloned->setTriggeredAbility(triggeredAbility->clone());
  }

  // Clone the activated ability
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
  int baseActions = 1;
  for (const auto& enchantment : enchantments->getEnchantments()) {
    baseActions = enchantment->getModifiedActions(baseActions);
  }
  currentActions = baseActions;
}

bool Minion::hasActions() const {
  return currentActions > 0;
}

void Minion::useAction() {
  if (currentActions > 0) {
    currentActions--;
  }
}

// Triggered minion abilities
void Minion::setTriggeredAbility(std::unique_ptr<TriggeredAbility> ability) {
  triggeredAbility = std::move(ability);
}

bool Minion::hasTriggeredAbility() const {
  return triggeredAbility != nullptr;
}

TriggeredAbility* Minion::getTriggeredAbility() const {
  return triggeredAbility.get();
}

const std::string& Minion::getTriggeredDescription() const {
  static const std::string empty = "";
  return triggeredAbility ? triggeredAbility->getDescription() : empty;
}

// Activated minion abilities
void Minion::setActivatedAbility(std::unique_ptr<AbilityCommand> ability) {
  activatedAbility = std::move(ability);
}

void Minion::useAbility(Target target, Game* game) {
  if (!activatedAbility) {
    std::cout << name << " has no activated ability!" << std::endl;
    return;
  }

  if (isAbilitySilenced()) {
    std::cout << name << "'s abilities are silenced!" << std::endl;
    return;
  }

  if (!hasActions()) {
    std::cout << name << " has no actions remaining!" << std::endl;
    return;
  }

  int modifiedCost = getAbilityCost(0);
  if (!owner->canAfford(modifiedCost)) {
    if (game->isTestingMode()) {
      std::cout << "Testing mode: Using " << activatedAbility->getDescription() << " without enough magic." << std::endl;
      owner->setMagic(0); // Set magic to 0 in testing mode
    }
    else {
      std::cout << "Not enough magic to use " << activatedAbility->getDescription() << " (costs " << modifiedCost << ")" << std::endl;
      return;
    }
  }
  else {
    owner->payMagic(modifiedCost);
  }

  useAction();

  activatedAbility->execute(target, game);

  std::cout << name << " uses " << activatedAbility->getDescription() << std::endl;
}

bool Minion::hasActivatedAbility() const {
  return activatedAbility != nullptr;
}

int Minion::getAbilityCost(int abilityIndex) const {
  if (!activatedAbility) return 0;
  
  int baseCost = activatedAbility->getCost();
  for (const auto& enchantment : enchantments->getEnchantments()) {
    baseCost = enchantment->getModifiedAbilityCost(baseCost);
  }
  return baseCost;
}

bool Minion::isAbilitySilenced() const {
  for (const auto& enchantment : enchantments->getEnchantments()) {
    if (enchantment->isAbilitySilenced()) {
      return true;
    }
  }
  return false;
}

const std::string& Minion::getAbilityDescription(int abilityIndex) const {
  static const std::string empty = "";
  return activatedAbility ? activatedAbility->getDescription() : empty;
}

int Minion::getAttack() const {
  int attack = baseAttack;
  for (const auto& enchantment : enchantments->getEnchantments()) {
    attack = enchantment->getModifiedAttack(attack);
  }
  return attack;
}

int Minion::getDefence() const {
  int defence = baseDefence;
  for (const auto& enchantment : enchantments->getEnchantments()) {
    defence = enchantment->getModifiedDefence(defence);
  }
  return defence;
}

void Minion::addEnchantment(std::unique_ptr<EnchantmentDecorator> enchantment) {
  enchantments->addEnchantment(std::move(enchantment));
}

void Minion::removeTopEnchantment() {
  enchantments->removeTopEnchantment();
}

bool Minion::hasEnchantments() const {
  return enchantments->hasEnchantments();
}

const std::vector<std::unique_ptr<EnchantmentDecorator>>& Minion::getEnchantments() const {
  return enchantments->getEnchantments();
}

void Minion::setAttack(int att) {
  baseAttack = att;
}

void Minion::setDefence(int def) {
  baseDefence = def;
}

void Minion::setActions(int act) {
  currentActions = act;
}
