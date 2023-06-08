#include "SDProp.h"

#include "raymath.h"

SDProp::SDProp(Vector2 worldPos, Texture2D texture)
    : WorldPos(worldPos), Texture(texture)
{
}

void SDProp::Render(Vector2 knightPos)
{
  Vector2 screenPos{Vector2Subtract(WorldPos, knightPos)};
  DrawTextureEx(Texture, screenPos, 0.f, Scale, WHITE);
}

Rectangle SDProp::GetCollision(Vector2 knightPos)
{
  Vector2 screenPos{Vector2Subtract(WorldPos, knightPos)};
  return Rectangle{screenPos.x, screenPos.y, Texture.width * Scale,
                   Texture.height * Scale};
}
