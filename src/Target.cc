#include "../include/Target.h"
#include "../include/Game.h"
#include "../include/Card.h"
#include "../include/Minion.h"

Target::Target() : playerNum{0}, position{0}, isRitual{false}, isPlayer{false} {}

Target::Target(int player, int pos, bool ritual) : playerNum{player}, position{pos}, isRitual{ritual}, isPlayer{false} {}

Target::Target(int player) : playerNum{player}, position{0}, isRitual{false}, isPlayer{true} {}

bool Target::isValidTarget(Game* game) {
  // TODO: Implement validation logic
  
  return true;
}

Card* Target::getTargetCard(Game* game) {
  // TODO: Implement card retrieval logic
  return nullptr;
}

Minion* Target::getTargetMinion(Game* game) {
  // TODO: Implement minion retrieval logic
  return nullptr;
}
