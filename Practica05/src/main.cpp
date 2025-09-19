// IOStream
#include <iostream>

// STL
#include <vector>

// Random
#include <cstdlib>

// Sprite
#include "Header Files/Sprite.h"

// Font
#include "Header Files/Font.h"

// Graphics
#define LITE_GFX_IMPLEMENTATION
#include "litegfx.h"
#include <glfw3.h>

using namespace std;

constexpr unsigned int WINDOW_WIDTH = 1200u;
constexpr unsigned int WINDOW_HEIGHT = 800u;

struct CFloatingText {
  CFont* pFont;

  CVec2 vPosition;
  float fSpeed;
  
  float fRed;
  float fGreen;
  float fBlue;
};

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

  // Vector initialization.
  vector<CFont*> vFonts = { CFont::Load("./data/Orange.ttf", 32.0f), CFont::Load("./data/SFSlapstickComic.ttf", 32.0f) };
  vector<CFloatingText> vFloatingTexts;

  // Delta Time Variables
  float fLastTime = glfwGetTime();

  while (!glfwWindowShouldClose(pWindow)) {
    lgfx_clearcolorbuffer(0.f, 0.f, 0.f);

    // Calculate Delta Time.
    float fElapsedTime = glfwGetTime();
    float fDeltaTime = static_cast<float>(fElapsedTime - fLastTime);
    fLastTime = fElapsedTime;

    if (rand() % 101 == 0 && !vFonts.empty()) {
      int iRandomFontIndex = rand() % vFonts.size();
      int iRandomHeight = rand() % WINDOW_HEIGHT;
      float fRandomMovementSpeed = static_cast<float>(rand() % 181 + 20);

      CFloatingText oNewText;
      oNewText.pFont = vFonts[iRandomFontIndex];
      oNewText.vPosition = CVec2(WINDOW_WIDTH, iRandomHeight);
      oNewText.fSpeed = fRandomMovementSpeed;
      oNewText.fRed = static_cast<float>(rand() % 256) / 255.f;
      oNewText.fGreen = static_cast<float>(rand() % 256) / 255.f;
      oNewText.fBlue = static_cast<float>(rand() % 256) / 255.f;

      vFloatingTexts.push_back(oNewText);
    }

    for (auto it = vFloatingTexts.begin(); it != vFloatingTexts.end();) {
      it->vPosition -= CVec2(it->fSpeed * fDeltaTime, 0.f);

      lgfx_setcolor(it->fRed, it->fGreen, it->fBlue, 1.f);
      if (it->pFont) it->pFont->Draw("Hello World!", it->vPosition);

      if (it->vPosition.GetX() < -it->pFont->GetTextSize("Hello World!").GetX()) it = vFloatingTexts.erase(it);
      else ++it;
    }

    glfwSwapBuffers(pWindow);
    glfwPollEvents();
  }

  glfwDestroyWindow(pWindow);
  glfwTerminate();

  return 0;
}
