#ifndef TARGET_H
#define TARGET_H

class Game;
class Card;
class Minion;

class Target {
private:
  int playerNum;
  int position;
  bool Ritual;
  bool isPlayer;

public:
  Target();
  Target(int player, int pos, bool ritual);
  Target(int player); // For targeting players directly

  bool isValidTarget(Game* game);
  Card* getTargetCard(Game* game);
  Minion* getTargetMinion(Game* game);

  bool isRitual() const { return Ritual; }
  int  getPosition()  const { return position; }
};

#endif