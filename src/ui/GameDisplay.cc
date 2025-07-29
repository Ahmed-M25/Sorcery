#include "../include/ui/GameDisplay.h"
#include "../include/core/Player.h"
#include "../include/cards/base/Card.h"
#include "../include/cards/base/Minion.h"
#include "../include/cards/base/Ritual.h"
#include "../include/cards/base/Spell.h"
#include "../include/cards/enchantments/system/EnchantmentDecorator.h"
#include "../include/factory/CardFactory.h"
#include "../include/ui/ascii_graphics.h"
#include <iostream>
#include <iomanip>

void GameDisplay::displayBoard(Player* p1, Player* p2) {
  // Top border
  std::cout << EXTERNAL_BORDER_CHAR_TOP_LEFT;
  for (int i = 0; i < 165; i++) {
    std::cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
  }
  std::cout << EXTERNAL_BORDER_CHAR_TOP_RIGHT << std::endl;
  // Top row: P1 ritual, P1 player card, P1 graveyard
  displayTopRow(p1);
  
  // P1 minions row
  displayMinionRow(p1);
  
  // Center graphic (Sorcery logo)
  displayCenterGraphic();
  
  // P2 minions row  
  displayMinionRow(p2);
  
  // Bottom row: P2 ritual, P2 player card, P2 graveyard
  displayBottomRow(p2);
  // Bottom border
  std::cout << EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;
  for (int i = 0; i < 165; i++) {
    std::cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
  }
  std::cout << EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT << std::endl;
}

void GameDisplay::displayHand(Player* player) {
  int totalCards = player->getHand().size();
  
  if (totalCards == 0) {
    // Show one row of 5 empty slots when hand is completely empty
    std::vector<card_template_t> emptyRow;
    for (int i = 0; i < 5; i++) {
      emptyRow.push_back(CARD_TEMPLATE_EMPTY);
    }
    displayCardsHorizontally(emptyRow);
    return;
  }
  
  // Calculate number of complete rows + any partial row
  int completeRows = totalCards / 5;
  int remainingCards = totalCards % 5;
  int totalRows = completeRows + (remainingCards > 0 ? 1 : 0);
  
  // Display each row
  for (int row = 0; row < totalRows; row++) {
    std::vector<card_template_t> rowCards;
    
    // Determine how many slots to show in this row
    int slotsInThisRow = 5; // Always show 5 slots per row
    
    // Fill this row
    for (int col = 0; col < slotsInThisRow; col++) {
      int cardIndex = row * 5 + col;
      
      if (cardIndex < totalCards) {
        // Add actual card
        Card* card = player->getHand().getCard(cardIndex);
        rowCards.push_back(getCardTemplate(card));
      } 
      else {
        // Add empty slot for remaining positions in the row
        rowCards.push_back(CARD_TEMPLATE_EMPTY);
      }
    }
    
    displayCardsHorizontally(rowCards);
  }
}

void GameDisplay::displayCard(Card* card) {
  if (!card) return;
  
  card_template_t cardTemplate = getCardTemplate(card);
  for (const auto& line : cardTemplate) {
    std::cout << line << std::endl;
  }
}

void GameDisplay::displayMinion(Minion* minion) {
  if (!minion) return;
  
  displayCard(minion);
  
  // TODO: Add enchantment display when enchantments are implemented
  std::cout << std::endl;
}

void GameDisplay::displayEnchantments(Minion* minion) {
  if (!minion || !minion->hasEnchantments()) {
    return;
  }

  const auto& enchantments = minion->getEnchantments();
  
  for (size_t i = 0; i < enchantments.size(); i += 5) {
    std::vector<card_template_t> enchantmentCards;
    
    for (size_t j = 0; j < 5 && (i + j) < enchantments.size(); j++) {
      std::string name = enchantments[i + j]->getName();
      auto enchantmentCard = CardFactory::createCard(name);
      
      if (enchantmentCard) {
        enchantmentCards.push_back(getCardTemplate(enchantmentCard.get()));
      } else {
        // Fallback for unknown enchantments
        enchantmentCards.push_back(CARD_TEMPLATE_EMPTY);
      }
    }
    
    displayCardsHorizontally(enchantmentCards);
  }
}

void GameDisplay::displayHelp() {
  std::cout << "Commands: help -- Display this message." << std::endl;
  std::cout << "          end  -- End the current player's turn." << std::endl;
  std::cout << "          quit -- End the game." << std::endl;
  std::cout << "          attack minion other-minion -- Orders minion to attack other-minion." << std::endl;
  std::cout << "          attack minion -- Orders minion to attack the opponent." << std::endl;
  std::cout << "          play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player." << std::endl;
  std::cout << "          use minion [target-player target-card] -- Use minion's special ability, optionally targeting target-card owned by target-player." << std::endl;
  std::cout << "          inspect minion -- View a minion's card and all enchantments on that minion." << std::endl;
  std::cout << "          hand -- Describe all cards in your hand." << std::endl;
  std::cout << "          board -- Describe all cards on the board." << std::endl;
}

void GameDisplay::displayGameOver(const std::string& reason) {
  std::cout << std::endl;
  std::cout << "================================" << std::endl;
  std::cout << "           GAME OVER            " << std::endl;
  std::cout << "================================" << std::endl;
  std::cout << reason << std::endl;
  std::cout << "================================" << std::endl;
}

std::string GameDisplay::cardToString(Card* card) {
  // Simple text representation for debugging
  if (!card) return "Empty";
  return card->getName() + " (" + card->getType() + ")";
}

void GameDisplay::loadAsciiArt() {
  // Not needed for simple graphics - templates are pre-loaded
}

// Helper methods
card_template_t GameDisplay::getCardTemplate(Card* card) {
  if (!card) return CARD_TEMPLATE_EMPTY;
  
  std::string type = card->getType();
  
  if (type == "Minion") {
    Minion* minion = static_cast<Minion*>(card);
    // Check if minion has activated ability first (and is not silenced)
    if (minion->hasActivatedAbility() && !minion->isAbilitySilenced()) {
      return display_minion_activated_ability(minion->getName(), minion->getCost(),
                                            minion->getAttack(), minion->getDefence(),
                                            minion->getAbilityCost(0), minion->getAbilityDescription(0));
    }
    // Check if minion has triggered ability (and is not silenced)
    else if (minion->hasTriggeredAbility() && !minion->isAbilitySilenced()) {
      return display_minion_triggered_ability(minion->getName(), minion->getCost(),
                                            minion->getAttack(), minion->getDefence(),
                                            minion->getTriggeredDescription());
    }
    // No abilities or abilities are silenced
    else {
      return display_minion_no_ability(minion->getName(), minion->getCost(), 
                                      minion->getAttack(), minion->getDefence());
    }
  }
  else if (type == "Ritual") {
    Ritual* ritual = static_cast<Ritual*>(card);
    return display_ritual(ritual->getName(), ritual->getCost(), 
                        ritual->getActivationCost(), ritual->getDescription(),
                        ritual->getCharges());
  }
  else if (type == "Spell") {
    return display_spell(card->getName(), card->getCost(), card->getDescription());
  }
  else if (type == "Enchantment") {
    // Use attack/defense template for enchantments that modify stats
    if (card->getName() == "Giant Strength") {
      return display_enchantment_attack_defence(card->getName(), card->getCost(), 
                                               card->getDescription(), "+2", "+2");
    } else if (card->getName() == "Enrage") {
      return display_enchantment_attack_defence(card->getName(), card->getCost(), 
                                               card->getDescription(), "*2", "*2");
    } else {
      return display_enchantment(card->getName(), card->getCost(), card->getDescription());
    }
  }
  
  return CARD_TEMPLATE_EMPTY;
}

void GameDisplay::displayTopRow(Player* player) {
  std::vector<card_template_t> topRow;
  
  // Ritual card
  if (player->getRitual()) {
    topRow.push_back(getCardTemplate(player->getRitual()));
  } 
  else {
    topRow.push_back(CARD_TEMPLATE_EMPTY);
  }

  // Slot 2: Empty
  topRow.push_back(CARD_TEMPLATE_EMPTY);
  
  // Player card
  topRow.push_back(display_player_card(1, player->getName(), player->getLife(), player->getMagic()));

  // Slot 4: Empty  
  topRow.push_back(CARD_TEMPLATE_EMPTY);
  
  // Graveyard (simplified - just show if empty or not)
  if (player->getGraveyard().isEmpty()) {
    topRow.push_back(CARD_TEMPLATE_EMPTY);
  } 
  else {
    Minion* topMinion = player->getGraveyard().getTop();
    topRow.push_back(getCardTemplate(topMinion));
  }
  
  displayCardsHorizontally(topRow);
}

void GameDisplay::displayBottomRow(Player* player) {
  std::vector<card_template_t> bottomRow;
  
  // Ritual card
  if (player->getRitual()) {
    bottomRow.push_back(getCardTemplate(player->getRitual()));
  } 
  else {
    bottomRow.push_back(CARD_TEMPLATE_EMPTY);
  }

  // Slot 2: Empty
  bottomRow.push_back(CARD_TEMPLATE_EMPTY);
  
  // Player card
  bottomRow.push_back(display_player_card(2, player->getName(), player->getLife(), player->getMagic()));

  // Slot 4: Empty  
  bottomRow.push_back(CARD_TEMPLATE_EMPTY);
  
  // Graveyard
  if (player->getGraveyard().isEmpty()) {
    bottomRow.push_back(CARD_TEMPLATE_EMPTY);
  } 
  else {
    Minion* topMinion = player->getGraveyard().getTop();
    bottomRow.push_back(getCardTemplate(topMinion));
  }
  
  displayCardsHorizontally(bottomRow);
}

void GameDisplay::displayMinionRow(Player* player) {
  std::vector<card_template_t> minionRow;
  
  // Get up to 5 minions
  for (int i = 0; i < 5; i++) {
    if (i < player->getBoard().size()) {
      Minion* minion = player->getBoard().getMinion(i);
      minionRow.push_back(getCardTemplate(minion));
    } 
    else {
      minionRow.push_back(CARD_TEMPLATE_EMPTY);
    }
  }
  
  displayCardsHorizontally(minionRow);
}

void GameDisplay::displayCenterGraphic() {
  for (const auto& line : CENTRE_GRAPHIC) {
    std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN << line << EXTERNAL_BORDER_CHAR_UP_DOWN << std::endl;
  }
}

void GameDisplay::displayCardsHorizontally(const std::vector<card_template_t>& cards) {
  // Display cards side by side, line by line
  for (int line = 0; line < 11; line++) { // Each card is 11 lines tall
    std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
    for (const auto& card : cards) {
      if (line < card.size()) {
        std::cout << card[line];
      } 
      else {
        std::cout << "                                 "; // Empty line
      }
    }
    std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN << std::endl;
  }
}