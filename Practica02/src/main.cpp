#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include <litegfx.h>
#include <glfw3.h>
#include <iostream>
#include "./Header Files/Vec2.h"
#include "stb_image.h"

using namespace std;

constexpr unsigned int WINDOW_WIDTH = 1000;
constexpr unsigned int WINDOW_HEIGHT = 1000;

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

	ltex_t* pWallTexture = LoadTexture("./data/wall.jpg");
	ltex_t* pFireTexture = LoadTexture("./data/fire.png");
	ltex_t* pGrilleTexture = LoadTexture("./data/grille.png");
	ltex_t* pLightTexture = LoadTexture("./data/light.png");

	double iMouseX, iMouseY;
	
	while (!glfwWindowShouldClose(pWindow)) {
		glfwGetCursorPos(pWindow, &iMouseX, &iMouseY);

		lgfx_setblend(BLEND_SOLID);
		ltex_drawrotsized(pWallTexture, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 0.0f,  WINDOW_WIDTH / static_cast<float>(pWallTexture->width), WINDOW_HEIGHT / static_cast<float>(pWallTexture->height));
		
		lgfx_setblend(BLEND_ADD);
		ltex_drawrotsized(pFireTexture, static_cast<float>(iMouseX) - static_cast<float>(pFireTexture->width) / 2, static_cast<float>(iMouseY) - static_cast<float>(pFireTexture->height) / 2, 0.0f, 0.0f, 0.0f, static_cast<float>(pFireTexture->width), static_cast<float>(pFireTexture->height), 0.0f, 0.0f, 1.0f, 1.0f);

		lgfx_setblend(BLEND_ALPHA);
		ltex_drawrotsized(pGrilleTexture, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 0.0f,  WINDOW_WIDTH / static_cast<float>(pGrilleTexture->width), WINDOW_HEIGHT / static_cast<float>(pGrilleTexture->height));

		lgfx_setblend(BLEND_MUL);
		ltex_drawrotsized(pLightTexture, static_cast<float>(iMouseX) - static_cast<float>(pLightTexture->width) / 2, static_cast<float>(iMouseY) - static_cast<float>(pLightTexture->height) / 2, 0.0f, 0.0f, 0.0f, static_cast<float>(pLightTexture->width), static_cast<float>(pLightTexture->height), 0.0f, 0.0f, 1.0f, 1.0f);
		
		glfwSwapBuffers(pWindow);
		glfwPollEvents();
	}

	glfwDestroyWindow(pWindow);
	glfwTerminate();

    return 0;
}
