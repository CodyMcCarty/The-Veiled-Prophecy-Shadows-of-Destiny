#pragma once
#include "raylib.h"

class SDBaseCharacter
{
 public:
  SDBaseCharacter();
  Vector2 GetWorldPos() { return WorldPos; }
  void SetScale(float scale) { Scale = scale; }
  void UndoMovement();
  Rectangle GetCollision();

 protected:
  Texture2D Idle{LoadTexture("characters/knight_idle_spritesheet.png")};
  Texture2D Run{LoadTexture("characters/knight_run_spritesheet.png")};
  Texture2D Texture{Idle};
  float Scale{4.f};
  Vector2 ScreenPos{};
  Vector2 WorldPos{};
  // 1:facing right -1:facing left
  float RightLeft{1.f};  // TODO: make it a bool?
  // animation vars
  float RunningTime{};
  int Frame{};
  int MaxFrames{6};
  float UpdateTime{1.f / 12.f};
  float Speed{4.f};
  // TODO: turn into sprite map
  float SpriteWidth{};
  float SpriteHeight{};
  Vector2 WorldPosLastFrame{};

 private:
};
