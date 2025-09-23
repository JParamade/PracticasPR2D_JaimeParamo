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