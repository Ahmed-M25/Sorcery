#include "../include/Card.h"
#include "../include/Player.h"

Card::Card(const std::string& name, int cost, const std::string& desc) : name{name}, cost{cost}, owner{nullptr}, description{desc} {}

void Card::setOwner(Player* player) {
  owner = player;
}


