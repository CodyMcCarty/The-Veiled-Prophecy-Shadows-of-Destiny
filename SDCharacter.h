#pragma once
#include "SDBaseCharacter.h"
#include "raylib.h"

class SDCharacter : public SDBaseCharacter
{
 public:
  SDCharacter(int ResolutionWidth, int ResolutionHeight);
  virtual void Tick(float DeltaTime) override;
  Vector2 GetLocation();
  virtual Vector2 GetScreenPos() override;

 private:
  int ViewWidth{};
  int ViewHeight{};
};
