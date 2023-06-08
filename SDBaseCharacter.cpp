#include "SDBaseCharacter.h"

SDBaseCharacter::SDBaseCharacter() {}

void SDBaseCharacter::UndoMovement() { WorldPos = WorldPosLastFrame; }

Rectangle SDBaseCharacter::GetCollision()
{
  return Rectangle{ScreenPos.x, ScreenPos.y, Scale * SpriteWidth,
                   Scale * SpriteHeight};
}
