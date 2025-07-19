#ifndef CARDFACTORY_H
#define CARDFACTORY_H

#include <string>
#include <memory>
#include "Card.h"

class CardFactory {
public:
  static std::unique_ptr<Card> createCard(const std::string& name);
  static void initializeCards();

private:
};

#endif