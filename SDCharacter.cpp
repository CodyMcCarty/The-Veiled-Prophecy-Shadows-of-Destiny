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

void SDCharacter::UndoMovement() { WorldPos = WorldPosLastFrame; }

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

Rectangle SDCharacter::GetCollision()
{
  return Rectangle{ScreenPos.x, ScreenPos.y, Scale * SpriteWidth,
                   Scale * SpriteHeight};
}

void SDCharacter::Tick(float DeltaTime)
{
  WorldPosLastFrame = WorldPos;
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

  // Update animation frame
  RunningTime += DeltaTime;
  if (RunningTime >= UpdateTime)
  {
    Frame++;
    RunningTime = 0.f;
    if (Frame > MaxFrames) Frame = 0;
  }

  // Draw Character
  Rectangle Source{Frame * SpriteWidth, 0.f, RightLeft * SpriteWidth,
                   SpriteHeight};
  Rectangle Dest{ScreenPos.x, ScreenPos.y, SpriteWidth * Scale,
                 SpriteHeight * Scale};
  DrawTexturePro(Texture, Source, Dest, Vector2{}, 0.f, WHITE);
}
