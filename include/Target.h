#ifndef TARGET_H
#define TARGET_H

class Game;
class Card;
class Minion;

class Target {
private:
  int playerNum;
  int position;
  bool isRitual;
  bool isPlayer;

public:
  Target();
  Target(int player, int pos, bool ritual);
  Target(int player); // For targeting players directly

  bool isValidTarget(Game* game);
  Card* getTargetCard(Game* game);
  Minion* getTargetMinion(Game* game);

  bool Ritual() const { return isRitual; }
  int getPosition() const { return position; }
  int getPlayerNum() const { return playerNum; }
  bool Player() const { return isPlayer; }
};

#endif