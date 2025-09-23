// IOStream
#include <iostream>

// Sprite
#include "Header Files/Sprite.h"

// World
#include "Header Files/World.h"

// Graphics
#define LITE_GFX_IMPLEMENTATION
#include "litegfx.h"
#include <glfw3.h>

using namespace std;

constexpr unsigned int WINDOW_WIDTH = 1200u;
constexpr unsigned int WINDOW_HEIGHT = 800u;

int main() {
  if (!glfwInit()) {
    static_cast<void>(fprintf(stderr, "Failed to initialize GLFW3.\n"));
    return -1;
  }

  GLFWwindow* pWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "World Test", nullptr, nullptr);
  if (!pWindow) {
    static_cast<void>(fprintf(stderr, "Failed to open GLFW3 window.\n"));
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(pWindow);

  lgfx_setup2d(WINDOW_WIDTH, WINDOW_HEIGHT);

  // Create background textures.
  CTexture oBG1Texture = CTexture("./data/clouds.png");
  CTexture oBG2Texture = CTexture("./data/trees2.png");
  CTexture oBG3Texture = CTexture("./data/trees1.png");
  CTexture oBG4Texture = CTexture("./data/level.png");

  // Create world.
  CWorld oWorld = CWorld(
    .15f, .15f, .15f,
    oBG1Texture.GetTexture(),
    oBG2Texture.GetTexture(),
    oBG3Texture.GetTexture(),
    oBG4Texture.GetTexture()
  );

  // Set background Parallax properties.
  oWorld.SetScrollRatio(0, .4f);
  oWorld.SetScrollSpeed(0, { -16.f, -8.f });
  oWorld.SetScrollRatio(1, .6f);
  oWorld.SetScrollRatio(2, .8f);
  oWorld.SetScrollRatio(3, 1.f);

  // Create Bee sprite and add it to the world.
  CTexture oBeeTexture = CTexture("./data/bee_anim.png");
  CSprite oBeeSprite = CSprite(oBeeTexture.GetTexture(), 8, 1);
  oBeeSprite.SetPosition({ WINDOW_WIDTH * .5f, WINDOW_HEIGHT * .5f });
  oBeeSprite.SetFps(8);
  oWorld.AddSprite(oBeeSprite);

  // Delta Time Variables
  float fLastTime = glfwGetTime();

  // Mouse Variables
  double dCursorPosX = 0;
  double dCursorPosY = 0;
  CVec2 vMousePosition;

  // Movement Variables
  CVec2 vDirection;
  CVec2 vNormalizedDirection;
  CVec2 vDisplacement;
  float fMovementSpeed = 128.f;
  float fDistance;

  // Rotation Variables
  float fTargetAngle = 0.f;
  float fRotationSpeed = 32.f;
  float fAngleDifference;

  while (!glfwWindowShouldClose(pWindow)) {
    lgfx_clearcolorbuffer(0.f, 0.f, 0.f);

    // Calculate Delta Time.
    float fElapsedTime = glfwGetTime();
    float fDeltaTime = static_cast<float>(fElapsedTime - fLastTime);
    fLastTime = fElapsedTime;

    // Get mouse cursor position (screen coords).
    glfwGetCursorPos(pWindow, &dCursorPosX, &dCursorPosY);

    // Convert to world coordinates.
    vMousePosition.SetX(static_cast<float>(dCursorPosX) + oWorld.GetCameraPosition().GetX());
    vMousePosition.SetY(static_cast<float>(dCursorPosY) + oWorld.GetCameraPosition().GetY());

    // Move bee towards mouse.
    fDistance = vMousePosition.Distance(oBeeSprite.GetPosition());
    if (fDistance > 0.f) {
      vDirection = vMousePosition - oBeeSprite.GetPosition();
      vNormalizedDirection = vDirection.Normalized();
      vDisplacement = vNormalizedDirection * fMovementSpeed * fDeltaTime;

      if (vDisplacement.Magnitude() > fDistance) vDisplacement = vNormalizedDirection * fDistance;

      oBeeSprite.SetPosition(oBeeSprite.GetPosition() + vDisplacement);

      // Rotate bee based on movement direction.
      fTargetAngle = (vNormalizedDirection.GetX() > 0 ? -15.f : 15.f);
    }
    else fTargetAngle = 0.f;

    // Apply rotation.
    fAngleDifference = fTargetAngle - oBeeSprite.GetAngle();
    oBeeSprite.SetAngle(oBeeSprite.GetAngle() + fRotationSpeed * fDeltaTime * (fAngleDifference > 0 ? 1 : -1));

    // Flip sprite if needed.
    oBeeSprite.SetScale(vNormalizedDirection.GetX() > 0 ? CVec2(1.f, 1.f) : CVec2(-1.f, 1.f));

    // Center camera on bee (with clamp inside).
    oWorld.CenterCameraOn(oBeeSprite.GetPosition(), { WINDOW_WIDTH, WINDOW_HEIGHT });

    oWorld.Update(fDeltaTime);
    oWorld.Draw({ WINDOW_WIDTH, WINDOW_HEIGHT });

    glfwSwapBuffers(pWindow);
    glfwPollEvents();
  }

  glfwDestroyWindow(pWindow);
  glfwTerminate();

  return 0;
}