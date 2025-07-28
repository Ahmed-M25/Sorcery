#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H

#include <string>
#include "Card.h"
#include "Target.h"

class EnchantmentDecorator;

class Enchantment : public Card {
public:
    Enchantment(const std::string& name, int cost, const std::string& desc);
    virtual ~Enchantment() = default;

    void play(Target target, Game* game) override;
    std::unique_ptr<Card> clone() const override;
    std::string getType() const override;
    bool requiresTarget() const override;
};

#endif 
