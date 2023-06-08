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
  void SetNearbyRandomTargetLocation();
  void MoveToTarget(Vector2 targetLocation);

 private:
  SDCharacter* Target;
  float SightDistance{350};
  float Timer{0};
  int Wait{3};
  Vector2 StartLocation{};
  Vector2 TargetLocation{};
};
