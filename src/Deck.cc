#include "../include/Deck.h"
#include "../include/CardFactory.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <chrono>

// Global seed variable (seeded once)
static unsigned globalSeed = std::chrono::system_clock::now().time_since_epoch().count();
static std::default_random_engine globalRng(globalSeed);

Deck::Deck() {}

void Deck::addCard(std::unique_ptr<Card> card) {
  if (card) {
    cards.push_back(std::move(card));
  }
}

std::unique_ptr<Card> Deck::drawCard(){
  if (isEmpty()){
    return nullptr;
  }

  auto card = std::move(cards.back());
  cards.pop_back();
  return card;
}

void Deck::shuffle() {
  std::shuffle(cards.begin(), cards.end(), globalRng);
}

bool Deck::isEmpty() const {
  return cards.empty();
}

int Deck::size() const {
  return static_cast<int>(cards.size());
}

void Deck::display() const {
  std::cout << "Deck (" << size() << " cards):" << std::endl;
  for (int i = 0; i < size(); i++) {
    std::cout << " [" << (i + 1) << "] " << cards[i]->getName() << std::endl;
  }
}

void Deck::loadFromFile(const std::string& filename){
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error: Could not open deck file " << filename << std::endl;
    return;
  }

  std::string cardName;
  while(std::getline(file, cardName)){
    if (!cardName.empty()) {
      auto card = CardFactory::createCard(cardName);
      if (card) {
        addCard(std::move(card));
        std::cout << "loading card: " << cardName << std::endl;
      }
      else {
        std::cerr << "Failed to create card: " << cardName << std::endl;
      }
    }
  }

  file.close();
  std::cout << "Loaded " << size() << " cards from " << filename << std::endl;
}
