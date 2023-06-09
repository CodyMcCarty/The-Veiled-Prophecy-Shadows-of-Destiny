#pragma once
#include "SDBaseCharacter.h"
#include "raylib.h"

class SDCharacter;

class SDEnemy : public SDBaseCharacter
{
 public:
  SDEnemy(Vector2 pos, Texture2D Idle, Texture2D Run);
  void SetTarget(SDCharacter* target) { Target = target; }
  virtual Vector2 GetScreenPos() override;
  virtual void Tick(float deltaTime) override;

 private:
  SDCharacter* Target;
  float DPS{10.f};
};
