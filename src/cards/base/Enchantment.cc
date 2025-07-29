#include "cards/base/Enchantment.h"

Enchantment::Enchantment(const std::string& name, int cost, const std::string& desc)
  : Card{name, cost, desc} {}

std::string Enchantment::getType() const {
    return "Enchantment";
}

bool Enchantment::requiresTarget() const {
    return true; // All enchantments require targeting
}

void Enchantment::play(Target, Game*) {
}

std::unique_ptr<Card> Enchantment::clone() const {
    return nullptr;
}
