#ifndef BOARD_H
#define BOARD_H

#include <vector> 
#include <memory>
#include "Minion.h"

class Board {
private: 
  std::vector<std::unique_ptr<Minion>> minions; 
  static const int MAX_MINIONS = 5;

public:
  Board();
  ~Board() = default;

  void addMinion(std::unique_ptr<Minion> minion);
  std::unique_ptr<Minion> removeMinion(int index);
  Minion* getMinion(int index);
  bool isFull() const;
  int size() const;
  void display() const;
  void restoreActions();
  std::vector<Minion*> getMinions();
  std::unique_ptr<Minion> removeMinion(Minion* minion);
  void replaceMinion(int index, std::unique_ptr<Minion> newMinion);
};

#endif