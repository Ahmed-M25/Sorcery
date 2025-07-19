#include "../include/Hand.h"
#include <iostream>

Hand::Hand() {}

void Hand::addCard(std::unique_ptr<Card> card) {
  if (!isFull() && card) {
    cards.push_back(std::move(card));
  }
}

std::unique_ptr<Card> Hand::removeCard(int index) {
  if (index >= 0 && index < static_cast<int>(cards.size())) {
    auto card = std::move(cards[index]);
    cards.erase(cards.begin() + index);

    return card;
  }

  return nullptr;
}

bool Hand::isFull() const {
  return cards.size() >= MAX_SIZE;
}

int Hand::size() const {
  return static_cast<int>(cards.size());
}

void Hand::display() const {
  std::cout << "Hand (" << size() << "/" << MAX_SIZE << "):";
  for (int i = 0; i < size(); i++) {
    std::cout << " [" << (i + 1) << "] " << cards[i]->getName();
  }
  
  std::cout << std::endl;
}

Card* Hand::getCard(int index) const {
  if (index >= 0 && index < static_cast<int>(cards.size())) {
    return cards[index].get();
  }

  return nullptr;
}
