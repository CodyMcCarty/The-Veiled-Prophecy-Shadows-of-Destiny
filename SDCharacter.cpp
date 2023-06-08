#include "SDCharacter.h"

#include "raymath.h"

SDCharacter::SDCharacter(int viewWidth, int viewHeight)
    : ViewWidth(viewWidth), ViewHeight(viewHeight)
{
  SpriteWidth = Texture.width / MaxFrames;
  SpriteHeight = Texture.height;
}

Vector2 SDCharacter::GetScreenPos()
{
  return Vector2{
      (static_cast<float>(ViewWidth) / 2.0f) - Scale * (0.5f * SpriteWidth),
      (static_cast<float>(ViewHeight) / 2.0f) - Scale * (0.5f * SpriteHeight)};
}

/*
Updated location method.
Location 0,0 is top,left of map and mapSize+mapScale
i.e. ~4000,4000 is bottom,right
*/
Vector2 SDCharacter::GetLocation()
{
  Vector2 pos{WorldPos.x + Scale * (0.5f * SpriteWidth),
              WorldPos.y + Scale * (0.5f * SpriteHeight)};
  return Vector2Add(pos, GetScreenPos());
}

void SDCharacter::Tick(float deltaTime)
{
  if (IsKeyDown(KEY_A)) Velocity.x -= 1.0;
  if (IsKeyDown(KEY_D)) Velocity.x += 1.0;
  if (IsKeyDown(KEY_W)) Velocity.y -= 1.0;
  if (IsKeyDown(KEY_S)) Velocity.y += 1.0;
  // TODO: should be normalized right after?
  // TODO: Remove Debug speed
  Speed = IsKeyDown(KEY_LEFT_SHIFT) ? 20.f : 4.f;

  SDBaseCharacter::Tick(deltaTime);
}
