#ifndef DECK_H
#define DECK_H

#include <vector>
#include <memory>
#include <string>
#include "Card.h"

class Deck {
private:
  std::vector<std::unique_ptr<Card>> cards;

public:
  Deck();
  ~Deck() = default;

  void addCard(std::unique_ptr<Card> card);
  std::unique_ptr<Card> drawCard();
  void shuffle();
  bool isEmpty() const;
  int size() const;
  void display() const;
  void loadFromFile(const std::string& filename);
};

#endif