#ifndef HAND_H
#define HAND_H

#include <vector> 
#include <memory>
#include "../cards/base/Card.h"

class Hand {
private:
  std::vector<std::unique_ptr<Card>> cards;
  static const int MAX_SIZE = 5;

public:
  Hand();
  ~Hand() = default;

  void addCard(std::unique_ptr<Card> card);
  std::unique_ptr<Card> removeCard(int index);
  bool isFull() const;
  int size() const;
  void display() const;
  Card* getCard(int index) const; // Non-owning access for viewing
};

#endif