#define LITE_GFX_IMPLEMENTATION

#include <glfw3.h>
#include <iostream>
#include "../src/Header Files/Sprite.h"

using namespace std;

constexpr unsigned int WINDOW_WIDTH = 1200u;
constexpr unsigned int WINDOW_HEIGHT = 800u;

int main() {
  if (!glfwInit()) {
    static_cast<void>(fprintf(stderr, "Failed to initialize GLFW3.\n"));
    return -1;
  }

  GLFWwindow* pWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Animation Test", nullptr, nullptr);
  if (!pWindow) {
    static_cast<void>(fprintf(stderr, "Failed to open GLFW3 window.\n"));
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(pWindow);

  lgfx_setup2d(WINDOW_WIDTH, WINDOW_HEIGHT);

  // Texture Variables
  CTexture oBeeTexture = CTexture("./data/bee_anim.png");
  CSprite oBeeSprite = CSprite(oBeeTexture.GetTexture(), 8, 1);
  oBeeSprite.SetPosition({ WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f });
  oBeeSprite.SetFps(8);

  CTexture oCoinTexture = CTexture("./data/coin_anim.png");
  CSprite oCoinSprite = CSprite(oCoinTexture.GetTexture(), 5, 1);
  oCoinSprite.SetPosition({ WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f });
  oCoinSprite.SetFps(8);

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

    // Get mouse cursor position.
    glfwGetCursorPos(pWindow, &dCursorPosX, &dCursorPosY);
    vMousePosition.SetX(dCursorPosX);
    vMousePosition.SetY(dCursorPosY);

    // Move entity towards mouse cursor.
    fDistance = vMousePosition.Distance(oBeeSprite.GetPosition());
    if (fDistance > 0) {
      vDirection = vMousePosition - oBeeSprite.GetPosition();
      vNormalizedDirection = vDirection.Normalized();
      vDisplacement = vNormalizedDirection * fMovementSpeed * fDeltaTime;

      if (vDisplacement.Magnitude() > fDistance) vDisplacement = vNormalizedDirection * fDistance;

      oBeeSprite.SetPosition(oBeeSprite.GetPosition() + vDisplacement);

      fTargetAngle = vNormalizedDirection.GetX() > 0 ? -15.f : 15.f;
    }
    else fTargetAngle = 0.f;

    // Rotate towards movement direction.
    fAngleDifference = fTargetAngle - oBeeSprite.GetAngle();
    oBeeSprite.SetAngle(oBeeSprite.GetAngle() + fRotationSpeed * fDeltaTime * (fAngleDifference > 0 ? 1 : -1));

    // Look towards mouse cursor.
    oBeeSprite.SetScale(vNormalizedDirection.GetX() > 0 ? CVec2(1.f, 1.f) : CVec2(-1.f, 1.f));

    // Update sprite on screen.
    oCoinSprite.Update(fDeltaTime);
    oCoinSprite.Draw();
    
    oBeeSprite.Update(fDeltaTime);
    oBeeSprite.Draw();

    glfwSwapBuffers(pWindow);
    glfwPollEvents();
  }

  glfwDestroyWindow(pWindow);
  glfwTerminate();

  return 0;
}
