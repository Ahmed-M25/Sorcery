#include "../include/Target.h"
#include "../include/Player.h"
#include "../include/Game.h"
#include "../include/Card.h"
#include "../include/Minion.h"

Target::Target() : playerNum{0}, position{0}, isRitual{false}, isPlayer{false} {}

Target::Target(int player, int pos, bool ritual) : playerNum{player}, position{pos}, isRitual{ritual}, isPlayer{false} {}

Target::Target(int player) : playerNum{player}, position{0}, isRitual{false}, isPlayer{true} {}

bool Target::isValidTarget(Game* game) {
  if (isPlayer) {
    return (playerNum == 1 || playerNum == 2);
  }
  
  Player* targetPlayer = (playerNum == 1) ? game->getPlayer1() : game->getPlayer2();
  if (!targetPlayer) return false;
  
  if (isRitual) {
    return targetPlayer->getRitual() != nullptr;
  } 
  else {
    return (position >= 0 && position < targetPlayer->getBoard().size());
  }
}

Card* Target::getTargetCard(Game* game) {
  if (isPlayer) return nullptr;
  
  Player* targetPlayer = (playerNum == 1) ? game->getPlayer1() : game->getPlayer2();
  if (!targetPlayer) return nullptr;
  
  if (isRitual) {
    return targetPlayer->getRitual();
  } 
  else {
    return targetPlayer->getBoard().getMinion(position);
  }
}

Minion* Target::getTargetMinion(Game* game) {
  if (isPlayer || isRitual) return nullptr;
  
  Player* targetPlayer = (playerNum == 1) ? game->getPlayer1() : game->getPlayer2();
  if (!targetPlayer) return nullptr;
  
  return targetPlayer->getBoard().getMinion(position);
}