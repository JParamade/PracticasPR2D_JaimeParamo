#define LITE_GFX_IMPLEMENTATION

#include <glfw3.h>
#include <iostream>
#include "../src/Header Files/Sprite.h"

using namespace std;

constexpr unsigned int WINDOW_WIDTH = 1200u;
constexpr unsigned int WINDOW_HEIGHT = 800u;

int main() {
    CTexture oBeeTexture = CTexture("./data/bee_anim.png");
    CSprite oSprite = CSprite(oBeeTexture.GetTexture());

    if (!glfwInit()) {
        static_cast<void>(fprintf(stderr, "Failed to initialize GLFW3.\n"));
        return -1;
    }

    GLFWwindow* pWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Textures Test", nullptr, nullptr);
    if (!pWindow) {
        static_cast<void>(fprintf(stderr, "Failed to open GLFW3 window.\n"));
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(pWindow);

    lgfx_setup2d(WINDOW_WIDTH, WINDOW_HEIGHT);

    while (!glfwWindowShouldClose(pWindow)) {
        lgfx_clearcolorbuffer(0.0f, 0.0f, 0.0f);
        
        oSprite.Draw();
        
        glfwSwapBuffers(pWindow);
        glfwPollEvents();
    }

    glfwDestroyWindow(pWindow);
    glfwTerminate();
    
    return 0;
}
