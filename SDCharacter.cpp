#include "SDCharacter.h"

#include "raymath.h"

SDCharacter::SDCharacter() { SpriteWidth = Texture.width / MaxFrames; }

void SDCharacter::SetResolution(int Width, int Height)
{
  ScreenPos = {
      ((float)Width / 2.0f) - Scale * (0.5f * (float)Texture.width / 6.0f),
      ((float)Height / 2.0f) - Scale * (.05f * (float)Texture.height)};
}

void SDCharacter::Tick(float DeltaTime)
{
  Vector2 direction{};
  if (IsKeyDown(KEY_A)) direction.x -= 1.0;
  if (IsKeyDown(KEY_D)) direction.x += 1.0;
  if (IsKeyDown(KEY_W)) direction.y -= 1.0;
  if (IsKeyDown(KEY_S)) direction.y += 1.0;
  // TODO: should be normalized right after
  if (Vector2Length(direction) != 0.0)
  {
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
  Rectangle Source{Frame * (float)Texture.width / 6.f, 0.f,
                   RightLeft * (float)Texture.width / 6.f,
                   (float)Texture.height};
  Rectangle Dest{ScreenPos.x, ScreenPos.y, (float)Texture.width / 6.f * Scale,
                 (float)Texture.height * Scale};
  DrawTexturePro(Texture, Source, Dest, Vector2{}, 0.f, WHITE);
}
