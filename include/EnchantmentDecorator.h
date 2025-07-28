#ifndef EnchantmentDecorator_H
#define EnchantmentDecorator_H

#include <string>

class EnchantmentDecorator {
public:
  EnchantmentDecorator() = default;
  virtual ~EnchantmentDecorator() = default;

  virtual int getModifiedAttack(int baseAttack) const = 0;
  virtual int getModifiedDefence(int baseDefence) const = 0;
  virtual int getModifiedActions(int baseActions) const = 0;
  virtual std::string getName() const = 0;
};

#endif