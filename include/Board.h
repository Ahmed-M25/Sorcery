#ifndef BOARD_H
#define BOARD_H

#include <vector> 
#include <memory>
#include "Minion.h"

class Board {
private: 
  std::vector<Minion*> minions; // Non-owning pointers (minions owned by hand/player)
  static const int MAX_MINIONS = 5;

public:
  Board();
  ~Board() = default;

  void addMinion(Minion* minion);
  void removeMinion(int index);
  Minion* getMinion(int index);
  bool isFull() const;
  int size() const;
  void display() const;
  void restoreActions();
  std::vector<Minion*> getMinions();
};

#endif