#ifndef BONE_GOLEM_TRIGGER_H
#define BONE_GOLEM_TRIGGER_H

#include "TriggeredAbility.h"
#include "Minion.h"

class BoneGolemTrigger : public TriggeredAbility {
  Minion* source;              // the Bone Golem itself
public:
  BoneGolemTrigger(Minion* src)
    : TriggeredAbility("Gain +1/+1 whenever a minion leaves play",
                        0,                  // cost (unused)
                        "minionleaves"),    // triggerType
      source{src} {}

  TriggerObserver* clone() const override {
    return new BoneGolemTrigger(source);
  }

  void execute(Target, Game* game) override {
    // only buff *this* Bone Golem
    source->modifyStats(1,1);
    std::cout << source->getName() << " gains +1/+1 from Bone Golem trigger.\n";
  }
};

#endif