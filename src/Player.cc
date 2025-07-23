#include "../include/Player.h"
#include <iostream>


Player::Player(const std::string& name) : name{name}, life{20}, magic{3} {}

const std::string& Player::getName() const {
  return name;
}

void Player::drawCard() {
  if (hand.isFull()) {
    std::cout << name << "'s hand is full, cannot draw." << std::endl;
  }

  auto card = deck.drawCard();
  if (card) {
    hand.addCard(std::move(card));
    std::cout << name << " draws a card." << std::endl;
  }
  else {
    std::cout << name << "'s deck is empty, cannot draw." << std::endl;
  }
}

void Player::loadDeck(const std::string& filename) {
  std::cout << name << " loading deck from " << filename << std::endl;
  deck.loadFromFile(filename);
}

void Player::shuffleDeck() {
  deck.shuffle();
  std::cout << name << "'s deck shuffled." << std::endl;
}

void Player::playCard(int index, Target target, Game* game) {
  // Conver from 1-indexed to 0-indexed
  int cardIndex = index - 1;

  Card* card = hand.getCard(cardIndex);
  if (!card) {
    std::cout << "Invalid card index!" << std::endl;
    return;
  }

  if (!canAfford(card->getCost())) {
    std::cout << "Not enough magic to play " << card->getName() << "!" << std::endl;
    return;
  }

  // Minions
  if (card->getType() == "Minion") {
    if (board.isFull()) {
      std::cout << "Board is full! Cannot play minion." << std::endl;
      return;
    }
    // std::cout << "Step 1: got card\n";

    std::unique_ptr<Card> playedCard = hand.removeCard(cardIndex);
    std::unique_ptr<Minion> minion(static_cast<Minion*>(playedCard.release()));

    if (!minion) {
      std::cout << "Not a real minion\n";
      return;
    }
    // std::cout << "Step 2: cast to minion\n";

    minion->setOwner(this);

    std::cout << name << " plays " << card->getName() << " (" << minion->getAttack() << "/" << minion->getDefence() << ")" << std::endl;

    board.addMinion(std::move(minion));
    // std::cout << "Step 3: added to board\n";

    payMagic(card->getCost());
    // std::cout << "Step 4: paid magic\n";


    // Remove from hand but don't delete (board now references it)
    // hand.removeCard(cardIndex);
    // std::cout << "Step 5: removed from hand\n";
  }
  // Spells
  else if (card->getType() == "Spell") {
    std::unique_ptr<Card> playedCard = hand.removeCard(cardIndex);
    playedCard->play(target, game);
    payMagic(card->getCost());
    // hand.removeCard(cardIndex); // Spell is consumed
  }
}

void Player::takeDamage(int damage) {
  life -= damage;
  std::cout << name << " takes " << damage << " damage. Life: " << life << std::endl;
}

void Player::heal(int amount) {
  life += amount;
  std::cout << name << " heals for " << amount << ". Life: " << life << std::endl;
}

bool Player::isDead() const {
  return life <= 0;
}

void Player::startTurn() {
  gainMagic(1);
  drawCard();
  restoreMinionsActions();
  std::cout << "\n" << name << "'s turn begins. Life: " << life << ", Magic: " << magic << std::endl;
}

void Player::endTurn() {
  std::cout << name << "'s turn ends." << std::endl;
}

void Player::restoreMinionsActions() {
  board.restoreActions();
}

void Player::gainMagic(int amount) {
  magic += amount;
}

bool Player::canAfford(int cost) const {
  return magic >= cost;
}

void Player::payMagic(int cost) {
  magic -= cost;
}
