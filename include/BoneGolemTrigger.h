#ifndef BONE_GOLEM_TRIGGER_H
#define BONE_GOLEM_TRIGGER_H

#include "TriggeredAbility.h"

class Minion;

class BoneGolemTrigger : public TriggeredAbility {
private:
  Minion* source;  // The Bone Golem itself

public:
  BoneGolemTrigger(Minion* src);
  
  std::unique_ptr<TriggeredAbility> clone() const override;
  void execute(Game* game) override;
};

#endif