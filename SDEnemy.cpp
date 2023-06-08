#include "SDEnemy.h"

#include <iostream>

#include "SDCharacter.h"
#include "raymath.h"

SDEnemy::SDEnemy(Vector2 worldPos, Texture2D idleTexture, Texture2D runTexture)
{
  WorldPos = worldPos;
  Texture = idleTexture;
  Idle = idleTexture;
  Run = runTexture;
  Speed = 3.5f;

  SpriteWidth = Texture.width / MaxFrames;
  SpriteHeight = Texture.height;
}

Vector2 SDEnemy::GetScreenPos()
{
  return Vector2Subtract(WorldPos, Target->GetWorldPos());
}

void SDEnemy::Tick(float deltaTime)
{
  Velocity = Vector2Subtract(Target->GetScreenPos(), GetScreenPos());
  SDBaseCharacter::Tick(deltaTime);
}
