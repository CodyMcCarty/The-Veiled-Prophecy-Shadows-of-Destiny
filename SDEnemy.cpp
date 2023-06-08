#include "SDEnemy.h"

#include "SDCharacter.h"
#include "raymath.h"

SDEnemy::SDEnemy(Vector2 worldPos, Texture2D idleTexture, Texture2D runTexture)
{
  WorldPos = worldPos;
  Texture = idleTexture;
  Idle = idleTexture;
  Run = runTexture;

  SpriteWidth = Texture.width / MaxFrames;
  SpriteHeight = Texture.height;
}

void SDEnemy::Tick(float deltaTime)
{
  ScreenPos = Vector2Subtract(WorldPos, Target->GetWorldPos());
  SDBaseCharacter::Tick(deltaTime);
  // ai behavior
}
