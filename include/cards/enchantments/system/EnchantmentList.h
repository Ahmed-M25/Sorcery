#ifndef ENCHANTMENTLIST_H
#define ENCHANTMENTLIST_H

#include "EnchantmentDecorator.h"
#include <vector>
#include <memory>

class EnchantmentList {
private:
  std::vector<std::unique_ptr<EnchantmentDecorator>> enchantments;

public:
  EnchantmentList() = default;
  ~EnchantmentList() = default;

  void addEnchantment(std::unique_ptr<EnchantmentDecorator> enchantment);
  void removeTopEnchantment();
  bool hasEnchantments() const;
  const std::vector<std::unique_ptr<EnchantmentDecorator>>& getEnchantments() const;
};

#endif 