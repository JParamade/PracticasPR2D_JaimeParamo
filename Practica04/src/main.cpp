#define LITE_GFX_IMPLEMENTATION

#include <glfw3.h>
#include <iostream>
#include "../src/Header Files/Sprite.h"

// STL
#include <algorithm>
#include <vector>

using namespace std;

constexpr unsigned int WINDOW_WIDTH = 1200u;
constexpr unsigned int WINDOW_HEIGHT = 800u;

int main() {
  if (!glfwInit()) {
    static_cast<void>(fprintf(stderr, "Failed to initialize GLFW3.\n"));
    return -1;
  }

  GLFWwindow* pWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Collision Test", nullptr, nullptr);
  if (!pWindow) {
    static_cast<void>(fprintf(stderr, "Failed to open GLFW3 window.\n"));
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(pWindow);

  lgfx_setup2d(WINDOW_WIDTH, WINDOW_HEIGHT);

  // Ball Sprite
  CTexture oBallTexture = CTexture("./data/ball.png");
  CSprite oBallSprite = CSprite(oBallTexture.GetTexture());
  oBallSprite.SetCollisionType(ECollisionType::COLLISION_CIRCLE);
  oBallSprite.SetPosition({ (WINDOW_WIDTH * .5f) - 200.f, WINDOW_HEIGHT * .5f });

  // Bee Sprite
  CTexture oBeeTexture = CTexture("./data/bee.png");
  CSprite oBeeSprite = CSprite(oBeeTexture.GetTexture());
  oBeeSprite.SetCollisionType(ECollisionType::COLLISION_PIXELS);
  oBeeSprite.SetPosition({ WINDOW_WIDTH * .5f, WINDOW_HEIGHT * .5f });

  // Box Sprite
  CTexture oBoxTexture = CTexture("./data/box.png");
  CSprite oBoxSprite = CSprite(oBoxTexture.GetTexture());
  oBoxSprite.SetCollisionType(ECollisionType::COLLISION_RECT);
  oBoxSprite.SetPosition({ (WINDOW_WIDTH * .5f) + 200.f, WINDOW_HEIGHT * .5f });

  // Circle Sprite
  CTexture oCircleTexture = CTexture("./data/circle.png");
  CTexture oRectTexture = CTexture("./data/rect.png");
  CSprite oMouseSprite = CSprite(oCircleTexture.GetTexture());
  oMouseSprite.SetCollisionType(ECollisionType::COLLISION_CIRCLE);

  // Delta Time Variables
  float fLastTime = glfwGetTime();

  // Scale Variables
  float fMinScale = .9f;
  float fMaxScale = 1.1f;
  float fScaleSpeed = .25f;
  float fAmplitude = (fMaxScale - fMinScale) * .5f;
  float fOffset = (fMaxScale + fMinScale) * .5f;
  float fScaleTime = 0.f;

  // Mouse Variables
  double dCursorPosX = 0;
  double dCursorPosY = 0;
  CVec2 vMousePosition;

  // Collision Variables
  vector<CSprite*> vSprites = { &oBallSprite, &oBeeSprite, &oBoxSprite };
  bool bIsColliding = false;

  while (!glfwWindowShouldClose(pWindow)) {
    lgfx_clearcolorbuffer(0.f, 0.f, 0.f);

    // Calculate Delta Time.
    float fElapsedTime = glfwGetTime();
    float fDeltaTime = static_cast<float>(fElapsedTime - fLastTime);
    fLastTime = fElapsedTime;

    // Scale Sprites.
    fScaleTime += fDeltaTime;
    float fNewScale = fOffset + fAmplitude * sin(fScaleSpeed / fAmplitude * fScaleTime);

    oBallSprite.SetScale({ fNewScale, fNewScale });
    oBoxSprite.SetScale({ fNewScale, fNewScale });

    // Get mouse cursor position.
    glfwGetCursorPos(pWindow, &dCursorPosX, &dCursorPosY);
    vMousePosition.SetX(dCursorPosX);
    vMousePosition.SetY(dCursorPosY);

    // Poll Input.
    if (glfwGetMouseButton(pWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
      oMouseSprite.SetTexture(oCircleTexture.GetTexture());
      oMouseSprite.SetCollisionType(ECollisionType::COLLISION_CIRCLE);
    }
    else if (glfwGetMouseButton(pWindow, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
      oMouseSprite.SetTexture(oBeeTexture.GetTexture());
      oMouseSprite.SetCollisionType(ECollisionType::COLLISION_PIXELS);
    }
    else if (glfwGetMouseButton(pWindow, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
      oMouseSprite.SetTexture(oRectTexture.GetTexture());
      oMouseSprite.SetCollisionType(ECollisionType::COLLISION_RECT);
    }

    // Move Sprite to Mouse Position.
    oMouseSprite.SetPosition(vMousePosition);

    // Check Collision
    bIsColliding = false;
    for (CSprite* pSprite : vSprites) {
      if (oMouseSprite.Collides(*pSprite)) {
        pSprite->SetColor(1.f, 0.f, 0.f, 1.f);
        bIsColliding = true;
      }
      else pSprite->SetColor(1.f, 1.f, 1.f, 1.f);
    }

    oMouseSprite.SetColor(
      bIsColliding ? 1.f : 1.f,
      bIsColliding ? 0.f : 1.f,
      bIsColliding ? 0.f : 1.f,
      1.f
    );

    // Draw Sprites.
    oBallSprite.Draw();
    oBeeSprite.Draw();
    oBoxSprite.Draw();
    oMouseSprite.Draw();

    glfwSwapBuffers(pWindow);
    glfwPollEvents();
  }

  glfwDestroyWindow(pWindow);
  glfwTerminate();

  return 0;
}
