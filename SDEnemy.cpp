#include "SDEnemy.h"

#include <iostream>

#include "SDCharacter.h"
#include "raymath.h"

SDEnemy::SDEnemy(Vector2 worldPos, Texture2D idleTexture, Texture2D runTexture)
{
  WorldPos = worldPos;
  StartLocation = worldPos;
  Texture = idleTexture;
  Idle = idleTexture;
  Run = runTexture;
  Speed = 3.5f;

  SpriteWidth = Texture.width / MaxFrames;
  SpriteHeight = Texture.height;

  SetNearbyRandomTargetLocation();
}

void SDEnemy::SetNearbyRandomTargetLocation()
{
  int dist = 200;
  TargetLocation.x =
      GetRandomValue(StartLocation.x - dist, StartLocation.x + dist);
  TargetLocation.y =
      GetRandomValue(StartLocation.y - dist, StartLocation.y + dist);
}

void SDEnemy::MoveToTarget(Vector2 targetLocation)
{
  // tL=Target->GetScreenPos()
  // Vector2 toTarget = Vector2Subtract(Target->GetScreenPos(), ScreenPos);
  // toTarget = Vector2Scale(Vector2Normalize(toTarget), Speed);
  //  WorldPos = Vector2Add(WorldPos, toTarget);
  Vector2 location = Vector2Subtract(targetLocation, WorldPos);
  location = Vector2Scale(Vector2Normalize(location), Speed / 2);
  WorldPos = Vector2Add(WorldPos, location);
}

void SDEnemy::Tick(float deltaTime)
{
  ScreenPos = Vector2Subtract(WorldPos, Target->GetWorldPos());
  SDBaseCharacter::Tick(deltaTime);

  // update timer
  Timer += deltaTime;
  if (Timer > 1000) Timer = 0;

  // TODO: make AI component
  //-ai behavior-
  enum Action
  {
    NOTHING,
    WONDER,
    CHASE
  };
  Action action{NOTHING};
  //-PERCEIVE
  Vector2 toTarget = Vector2Subtract(Target->GetScreenPos(), ScreenPos);
  //-THINK
  if (Vector2Distance(ScreenPos, Target->GetScreenPos()) < SightDistance)
  {
    toTarget = Vector2Scale(Vector2Normalize(toTarget), Speed);
    action = CHASE;
  }
  else if (static_cast<int>(Timer) % Wait == 0)
  {
    if (action != WONDER)
    {
      Wait = GetRandomValue(6, 15);
      SetNearbyRandomTargetLocation();
    }
    action = WONDER;
  }
  else if (Vector2Distance(WorldPos, TargetLocation) > 10.f)
  {
    action = WONDER;
  }
  else
  {
    action = NOTHING;
  }
  //-ACT
  switch (action)
  {
    case WONDER:
      MoveToTarget(TargetLocation);
      break;
    case CHASE:
      WorldPos = Vector2Add(WorldPos, toTarget);
      break;
    default:
      break;
  }
}
