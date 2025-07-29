#ifndef GRAVEYARD_H
#define GRAVEYARD_H

#include <vector>
#include <memory>
#include "cards/base/Minion.h"

class Graveyard {
private:
  std::vector<std::unique_ptr<Minion>> deadMinions;

public:
  Graveyard();
  ~Graveyard() = default;

  void addMinion(std::unique_ptr<Minion> minion);
  std::unique_ptr<Minion> removeTop();
  Minion* getTop();
  bool isEmpty() const;
  int size() const;
  void display() const;
};

#endif