#include "SDEnemy.h"

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
  WorldPosLastFrame = WorldPos;

  // Update animation frame
  RunningTime += deltaTime;
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
