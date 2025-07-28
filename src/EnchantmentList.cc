#include "../include/EnchantmentList.h"

void EnchantmentList::addEnchantment(std::unique_ptr<EnchantmentDecorator> enchantment) {
  enchantments.push_back(std::move(enchantment));
}

void EnchantmentList::removeTopEnchantment() {
  if (!enchantments.empty()) {
    enchantments.pop_back();
  }
}

bool EnchantmentList::hasEnchantments() const {
  return !enchantments.empty();
}

const std::vector<std::unique_ptr<EnchantmentDecorator>>& EnchantmentList::getEnchantments() const {
  return enchantments;
} 