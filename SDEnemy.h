#pragma once
#include "SDBaseCharacter.h"
#include "raylib.h"

class SDEnemy : public SDBaseCharacter
{
 public:
  SDEnemy(Vector2 pos, Texture2D Idle, Texture2D Run);
  void Tick(float deltaTime);

 private:
};
