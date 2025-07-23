#include "../include/Graveyard.h"
#include <iostream>

Graveyard::Graveyard() {}

void Graveyard::addMinion(std::unique_ptr<Minion> minion) {
  if (minion) {
    std::cout << minion->getName() << " is added to the graveyard." << std::endl;
    deadMinions.push_back(std::move(minion));
  }
}

std::unique_ptr<Minion> Graveyard::removeTop() {
  if (!isEmpty()) {
    auto minion = std::move(deadMinions.back());
    deadMinions.pop_back();
    return minion;
  }

  return nullptr;
}

Minion* Graveyard::getTop() {
  if (!isEmpty()) {
    return deadMinions.back().get();
  }

  return nullptr;
}

bool Graveyard::isEmpty() const {
  return deadMinions.empty();
}

int Graveyard::size() const {
  return static_cast<int>(deadMinions.size());
}

void Graveyard::display() const {
  std::cout << "Graveyard (" << size() << " dead minions):";
  if (isEmpty()) {
    std::cout << " [Empty]";
  }
  else {
    for (int i = 0; i < size(); i++) {
      std::cout << " " << deadMinions[i]->getName();
    }
  }
  std::cout << std:: endl;
}
