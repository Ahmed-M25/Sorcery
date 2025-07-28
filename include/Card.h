#ifndef CARD_H
#define CARD_H

#include <string>
#include <memory>

class Player;
class Game;
class Target;

class Card {
protected:
  std::string name;
  int cost;
  Player* owner;
  std::string description;

public:
  Card(const std::string& name, int cost, const std::string& desc);
  virtual ~Card() = default;

  // Pure virtual methods–must be implemented by sublcass
  virtual void play(Target target, Game* game) = 0;
  virtual std::unique_ptr<Card> clone() const = 0;
  virtual std::string getType() const = 0;
  virtual bool requiresTarget() const { return false; } // Default implementation - override in subclasses

  // Basic functionality
  void setOwner(Player* player);

  // Getters (for debugging/display only)
  const std::string& getName() const { return name; }
  int getCost() const { return cost; }
  const std::string& getDescription() const { return description; }
  Player* getOwner() const { return owner; }
};

#endif