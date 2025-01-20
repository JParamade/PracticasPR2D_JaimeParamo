#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include <glfw3.h>
#include <iostream>
#include "../src/Header Files/Sprite.h"
#include "stb_image.h"

using namespace std;

constexpr unsigned int WINDOW_WIDTH = 1200u;
constexpr unsigned int WINDOW_HEIGHT = 800u;

ltex_t* LoadTexture(const char* _sFilename) {
    int iWidth, iHeight;
	
    stbi_uc* sBuffer = stbi_load(_sFilename, &iWidth, &iHeight, nullptr, 4);
    if (!sBuffer) {
        static_cast<void>(fprintf(stderr, "Error: File '%s' failed to load.\n", _sFilename));
        return nullptr;
    }
	
    ltex_t* pTexture = ltex_alloc(iWidth, iHeight, 1);
    if (!pTexture) {
        static_cast<void>(fprintf(stderr, "Error: Texture couldn't be allocated.\n"));
        stbi_image_free(sBuffer);
        return nullptr;
    }
	
    ltex_setpixels(pTexture, sBuffer);
    stbi_image_free(sBuffer);

    return pTexture;
}

int main() {
    ltex_t* pTestTexture = LoadTexture("./data/bee_anim.png");
    CSprite oSprite = CSprite(pTestTexture);

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
