#include "SDBaseCharacter.h"

SDBaseCharacter::SDBaseCharacter() {}

void SDBaseCharacter::UndoMovement() { WorldPos = WorldPosLastFrame; }

Rectangle SDBaseCharacter::GetCollision()
{
  return Rectangle{ScreenPos.x, ScreenPos.y, Scale * SpriteWidth,
                   Scale * SpriteHeight};
}

void SDBaseCharacter::Tick(float deltaTime)
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
