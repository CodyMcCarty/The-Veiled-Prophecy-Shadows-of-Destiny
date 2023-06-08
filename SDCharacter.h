#pragma once
#include "SDBaseCharacter.h"
#include "raylib.h"

class SDCharacter : public SDBaseCharacter
{
 public:
  SDCharacter(int ResolutionWidth, int ResolutionHeight);
  void Tick(float DeltaTime);
  Vector2 GetLocation();

 private:
};
