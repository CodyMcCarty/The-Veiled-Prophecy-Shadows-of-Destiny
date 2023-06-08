#include "SDBaseCharacter.h"

#include "raymath.h"

SDBaseCharacter::SDBaseCharacter() {}

void SDBaseCharacter::UndoMovement() { WorldPos = WorldPosLastFrame; }

Rectangle SDBaseCharacter::GetCollision()
{
  return Rectangle{GetScreenPos().x, GetScreenPos().y, Scale * SpriteWidth,
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

  if (Vector2Length(Velocity) != 0.0)
  {
    WorldPos =
        Vector2Add(WorldPos, Vector2Scale(Vector2Normalize(Velocity), Speed));
    RightLeft = Velocity.x < 0.f ? -1.f : 1.f;
    Texture = Run;
  }
  else
  {
    Texture = Idle;
  }
  Velocity = {};

  // Draw Character
  Rectangle Source{Frame * SpriteWidth, 0.f, RightLeft * SpriteWidth,
                   SpriteHeight};
  Rectangle Dest{GetScreenPos().x, GetScreenPos().y, SpriteWidth * Scale,
                 SpriteHeight * Scale};
  DrawTexturePro(Texture, Source, Dest, Vector2{}, 0.f, WHITE);
}
