#include "../include/Spell.h"
#include "../include/Game.h"
#include <iostream>

Spell::Spell(const std::string& name, int cost, const std::string& desc) : Card {name, cost, desc} {}

