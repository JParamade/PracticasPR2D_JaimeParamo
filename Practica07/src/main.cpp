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

constexpr unsigned int WINDOW_WIDTH = 1024u;
constexpr unsigned int WINDOW_HEIGHT = 1024u;

int main() {
  if (!glfwInit()) {
    static_cast<void>(fprintf(stderr, "Failed to initialize GLFW3.\n"));
    return -1;
  }

  GLFWwindow* pWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tiles Test", nullptr, nullptr);
  if (!pWindow) {
    static_cast<void>(fprintf(stderr, "Failed to open GLFW3 window.\n"));
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(pWindow);

  lgfx_setup2d(WINDOW_WIDTH, WINDOW_HEIGHT);

  CTexture oCloudsTexture = CTexture("./data/clouds.png");

  // Create world.
  CWorld oWorld(
    .15f, .15f, .15f,
    oCloudsTexture.GetTexture(),
    nullptr,
    nullptr,
    nullptr
  );

  // Load Map
  if (!oWorld.LoadMap("data/map.tmx", 1)) {
    static_cast<void>(fprintf(stderr, "Failed to load map.\n"));
    glfwTerminate();
    return -1;
  }

  CTexture oIdleTexture = CTexture("./data/idle.png");
  CTexture oRunTexture = CTexture("./data/run.png");
  CSprite oPlayerSprite = CSprite(oIdleTexture.GetTexture());
  oPlayerSprite.SetPosition({ WINDOW_WIDTH * .5f, WINDOW_HEIGHT * .5f });
  oPlayerSprite.SetCollisionType(COLLISION_RECT);

  oWorld.AddSprite(oPlayerSprite);

  // Movement Variables
  CVec2 vVelocity = CVec2(.0f, .0f);
  float fGravity = 500.f;
  float fSpeed = 200.f;
  float fJumpForce = 300.f;
  bool bGrounded = true;

  // Delta Time Variables
  float fLastTime = glfwGetTime();

  while (!glfwWindowShouldClose(pWindow)) {
    lgfx_clearcolorbuffer(0.f, 0.f, 0.f);

    // Calculate Delta Time.
    float fElapsedTime = glfwGetTime();
    float fDeltaTime = static_cast<float>(fElapsedTime - fLastTime);
    fLastTime = fElapsedTime;

    vVelocity.SetY(vVelocity.GetY() + fGravity * fDeltaTime);

    if (glfwGetKey(pWindow, GLFW_KEY_LEFT) == GLFW_PRESS) {
      vVelocity.SetX(-fSpeed);
      oPlayerSprite.SetFlipX(true);
    }
    else if (glfwGetKey(pWindow, GLFW_KEY_RIGHT) == GLFW_PRESS) {
      vVelocity.SetX(fSpeed);
      oPlayerSprite.SetFlipX(false);
    }
    else vVelocity.SetX(0.f);

    if (glfwGetKey(pWindow, GLFW_KEY_SPACE) == GLFW_PRESS && bGrounded) {
      vVelocity.SetY(-fJumpForce);
      bGrounded = false; 
    }

    bool bCollided = oWorld.MoveSprite(oPlayerSprite, vVelocity * fDeltaTime);
    if (bCollided) {
      if (vVelocity.GetY() > 0.f) {
        vVelocity.SetY(0.f);
        bGrounded = true;
      }
    }

    if ((fabs(vVelocity.GetX()) > 0) && bGrounded) {
      oPlayerSprite.SetTexture(oRunTexture.GetTexture(), 6, 1);
      oPlayerSprite.SetFps(8);
    }
    else {
      oPlayerSprite.SetTexture(oIdleTexture.GetTexture());
      oPlayerSprite.SetFps(0);
    }

    oWorld.Update(fDeltaTime);
    oWorld.Draw({ WINDOW_WIDTH, WINDOW_HEIGHT });

    glfwSwapBuffers(pWindow);
    glfwPollEvents();
  }

  glfwDestroyWindow(pWindow);
  glfwTerminate();

  return 0;
}