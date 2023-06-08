#pragma once
#include "SDBaseCharacter.h"
#include "raylib.h"

class SDCharacter;

class SDEnemy : public SDBaseCharacter
{
 public:
  SDEnemy(Vector2 pos, Texture2D Idle, Texture2D Run);
  virtual void Tick(float deltaTime) override;
  void SetTarget(SDCharacter* target) { Target = target; }

  //  private:
  SDCharacter* Target;
};
