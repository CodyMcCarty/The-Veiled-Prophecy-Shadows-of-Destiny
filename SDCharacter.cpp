#include "SDCharacter.h"

#include "raymath.h"

SDCharacter::SDCharacter(int ResolutionWidth, int ResolutionHeight)
{
  SpriteWidth = Texture.width / MaxFrames;
  SpriteHeight = Texture.height;

  ScreenPos = {(static_cast<float>(ResolutionWidth) / 2.0f) -
                   Scale * (0.5f * SpriteWidth),
               (static_cast<float>(ResolutionHeight) / 2.0f) -
                   Scale * (0.5f * SpriteHeight)};
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
  return Vector2Add(pos, ScreenPos);
}

void SDCharacter::Tick(float deltaTime)
{
  SDBaseCharacter::Tick(deltaTime);
  Vector2 direction{};
  if (IsKeyDown(KEY_A)) direction.x -= 1.0;
  if (IsKeyDown(KEY_D)) direction.x += 1.0;
  if (IsKeyDown(KEY_W)) direction.y -= 1.0;
  if (IsKeyDown(KEY_S)) direction.y += 1.0;
  // TODO: should be normalized right after

  if (Vector2Length(direction) != 0.0)
  {
    // TODO: Remove Debug speed
    Speed = IsKeyDown(KEY_LEFT_SHIFT) ? 20.f : 4.f;
    WorldPos =
        Vector2Add(WorldPos, Vector2Scale(Vector2Normalize(direction), Speed));
    RightLeft = direction.x < 0.f ? -1.f : 1.f;
    Texture = Run;
  }
  else
  {
    Texture = Idle;
  }
}
