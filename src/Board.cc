#include "../include/Board.h"
#include <iostream>

Board::Board() {}

void Board::addMinion(std::unique_ptr<Minion> minion) {
  if (!isFull() && minion) {
    std::cout << minion->getName() << " enters the battlefield!" << std::endl;
    minions.push_back(std::move(minion));
  }
  else {
    std::cout << "Board is full! Cannot play minion." << std::endl;
  }
}

void Board::removeMinion(int index) {
  if (index >= 0 && index < static_cast<int>(minions.size())) {
    std::cout << minions[index]->getName() << " leaves the battlefield." << std::endl;
    minions.erase(minions.begin() + index);
  }
}

Minion* Board::getMinion(int index) {
  if (index >= 0 && index < static_cast<int>(minions.size())) {
    return minions[index].get();
  }

  return nullptr;
}

bool Board::isFull() const {
  return minions.size() >= MAX_MINIONS;
}

int Board::size() const {
  return static_cast<int>(minions.size());
}

void Board::display() const {
  std::cout << "Board (" << size() << "/" << MAX_MINIONS << "):";
  if (size() == 0) {
    std::cout << " [Empty]";
  }
  else {
    for (int i = 0; i < size(); i++) {
      std::cout << " [" << (i + 1) << "] " << minions[i]->getName() << " (" << minions[i]->getAttack() << "/" << minions[i]->getDefence() << ")";
    }
  }
  std::cout << std::endl;
}

void Board::restoreActions() {
  for (auto& minion : minions) {
    minion->restoreActions();
  }
}

std::vector<Minion*> Board::getMinions() {
  std::vector<Minion*> result;
  for (const auto& minion : minions) {
    result.push_back(minion.get());
  }
  return result;
}
