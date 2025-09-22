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

  GLFWwindow* pWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Font Test", nullptr, nullptr);
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
  oWorld.SetScrollRatio(0, 1.f);
  oWorld.SetScrollSpeed(0, { -16.f, -8.f });
  oWorld.SetScrollRatio(1, 1.f);
  oWorld.SetScrollRatio(2, 1.f);
  oWorld.SetScrollRatio(3, 1.f);

  // Create Bee sprite and add it to the world.
  CTexture oBeeTexture = CTexture("./data/bee_anim.png");
  CSprite oBeeSprite = CSprite(oBeeTexture.GetTexture(), 8, 1);
  oBeeSprite.SetPosition({ WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f });
  oBeeSprite.SetFps(8);
  oWorld.AddSprite(oBeeSprite);

  // Delta Time Variables
  float fLastTime = glfwGetTime();

  while (!glfwWindowShouldClose(pWindow)) {
    lgfx_clearcolorbuffer(0.f, 0.f, 0.f);

    // Calculate Delta Time.
    float fElapsedTime = glfwGetTime();
    float fDeltaTime = static_cast<float>(fElapsedTime - fLastTime);
    fLastTime = fElapsedTime;

    oWorld.Update(fDeltaTime);
    oWorld.Draw({ WINDOW_WIDTH, WINDOW_HEIGHT });

    glfwSwapBuffers(pWindow);
    glfwPollEvents();
  }

  glfwDestroyWindow(pWindow);
  glfwTerminate();

  return 0;
}