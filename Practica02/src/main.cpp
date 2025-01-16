#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define _USE_MATH_DEFINES

#include <litegfx.h>
#include <glfw3.h>
#include <iostream>
#include "./Header Files/Vec2.h"
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

	// Texture Variables
	ltex_t* pWallTexture = LoadTexture("./data/wall.jpg");
	ltex_t* pFireTexture = LoadTexture("./data/fire.png");
	ltex_t* pGrilleTexture = LoadTexture("./data/grille.png");
	ltex_t* pLightTexture = LoadTexture("./data/light.png");

	// Transform Values
	double iMouseX, iMouseY;
	CVec2 vFireSize(static_cast<float>(pFireTexture->width), static_cast<float>(pFireTexture->height));
	
	// Time Variables
	double dLastTime = glfwGetTime();
	double dElapsedTime = glfwGetTime();
	
	while (!glfwWindowShouldClose(pWindow)) {
		double dCurrentTime = glfwGetTime();
		double dDeltaTime = dCurrentTime - dLastTime;
		dLastTime = dCurrentTime;
		dElapsedTime += dDeltaTime;

		glfwGetCursorPos(pWindow, &iMouseX, &iMouseY);

		lgfx_clearcolorbuffer(0.0f, 0.0f, 0.0f);
		lgfx_setcolor(1.0f, 1.0f, 1.0f, 1.0f);
		
		// Draw wall texture with solid blending.
		lgfx_setblend(BLEND_SOLID);
		ltex_drawrotsized(pWallTexture, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 0.0f,  WINDOW_WIDTH / static_cast<float>(pWallTexture->width), WINDOW_HEIGHT / static_cast<float>(pWallTexture->height));

		// Calculate desired angle and size value with ping-pong function (sin).
		float fFireAngles = 10.0f * sin(static_cast<float>(M_PI) * static_cast<float>(dElapsedTime));
		vFireSize.SetX((1.0f + 0.2f * sin(static_cast<float>(2.5f * M_PI) * static_cast<float>(dElapsedTime))) * static_cast<float>(pFireTexture->width));
		vFireSize.SetY((1.0f + 0.2f * sin(static_cast<float>(2.5f * M_PI) * static_cast<float>(dElapsedTime))) * static_cast<float>(pFireTexture->height));
		// Draw fire texture with additive blending.
		lgfx_setblend(BLEND_ADD);
		ltex_drawrotsized(pFireTexture, static_cast<float>(iMouseX), static_cast<float>(iMouseY), fFireAngles, 0.5f, 0.5f, vFireSize.GetX(), vFireSize.GetY(), 0.0f, 0.0f, 1.0f, 1.0f);

		// Draw grille texture with alpha blending.
		lgfx_setblend(BLEND_ALPHA);
		ltex_drawrotsized(pGrilleTexture, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 0.0f,  WINDOW_WIDTH / static_cast<float>(pGrilleTexture->width), WINDOW_HEIGHT / static_cast<float>(pGrilleTexture->height));

		// Draw light texture with multiply blending.
		lgfx_setblend(BLEND_MUL);
		ltex_drawrotsized(pLightTexture, static_cast<float>(iMouseX), static_cast<float>(iMouseY), 0.0f, 0.5f, 0.5f, static_cast<float>(pLightTexture->width), static_cast<float>(pLightTexture->height), 0.0f, 0.0f, 1.0f, 1.0f);
		// Draw left border.
		lgfx_setcolor(0.0f, 0.0f, 0.0f, 1.0f);
		lgfx_setblend(BLEND_SOLID);
		lgfx_drawrect(0, static_cast<float>(iMouseY) - static_cast<float>(pLightTexture->height) / 2, static_cast<float>(iMouseX) - static_cast<float>(pLightTexture->width) / 2, static_cast<float>(pLightTexture->height));
		// Draw right border.
		lgfx_drawrect(static_cast<float>(iMouseX) + static_cast<float>(pLightTexture->width) / 2, static_cast<float>(iMouseY) - static_cast<float>(pLightTexture->height) / 2, WINDOW_WIDTH - (static_cast<float>(iMouseX) + static_cast<float>(pLightTexture->width) / 2), static_cast<float>(pLightTexture->height));
		// Draw upper border.
		lgfx_drawrect(static_cast<float>(iMouseX) - static_cast<float>(pLightTexture->width) / 2, 0, static_cast<float>(pLightTexture->width), static_cast<float>(iMouseY) - static_cast<float>(pLightTexture->height) / 2);
		// Draw lower border.
		lgfx_drawrect(static_cast<float>(iMouseX) - static_cast<float>(pLightTexture->width) / 2, static_cast<float>(iMouseY) + static_cast<float>(pLightTexture->height) / 2, static_cast<float>(pLightTexture->width), WINDOW_HEIGHT - (static_cast<float>(iMouseY) + static_cast<float>(pLightTexture->height) / 2));
		// Draw upper-left corner.
		lgfx_drawrect(0, 0, static_cast<float>(iMouseX) - static_cast<float>(pLightTexture->width) / 2, static_cast<float>(iMouseY) - static_cast<float>(pLightTexture->height) / 2);
		// Draw upper-right corner.
		lgfx_drawrect(static_cast<float>(iMouseX) + static_cast<float>(pLightTexture->width) / 2, 0, WINDOW_WIDTH - (static_cast<float>(iMouseX) + static_cast<float>(pLightTexture->width) / 2), static_cast<float>(iMouseY) - static_cast<float>(pLightTexture->height) / 2);
		// Draw lower-left corner.
		lgfx_drawrect(0, static_cast<float>(iMouseY) + static_cast<float>(pLightTexture->height) / 2, static_cast<float>(iMouseX) - static_cast<float>(pLightTexture->width) / 2, WINDOW_HEIGHT - (static_cast<float>(iMouseY) + static_cast<float>(pLightTexture->height) / 2));
		// Draw lower-right corner.
		lgfx_drawrect(static_cast<float>(iMouseX) + static_cast<float>(pLightTexture->width) / 2, static_cast<float>(iMouseY) + static_cast<float>(pLightTexture->height) / 2, WINDOW_WIDTH - (static_cast<float>(iMouseX) + static_cast<float>(pLightTexture->width) / 2), WINDOW_HEIGHT - (static_cast<float>(iMouseY) + static_cast<float>(pLightTexture->height) / 2));
		
		glfwSwapBuffers(pWindow);
		glfwPollEvents();
	}

	glfwDestroyWindow(pWindow);
	glfwTerminate();

    return 0;
}
