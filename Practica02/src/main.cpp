#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define _USE_MATH_DEFINES

#include <glfw3.h>
#include <iostream>
#include "./Header Files/Vec2.h"
#include "../src/Header Files/Texture.h"
#include "stb_image.h"

using namespace std;

constexpr unsigned int WINDOW_WIDTH = 1200u;
constexpr unsigned int WINDOW_HEIGHT = 800u;

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
	CTexture pWallTexture = CTexture("./data/wall.jpg");
	CTexture pFireTexture = CTexture("./data/fire.png");
	CTexture pGrilleTexture = CTexture("./data/grille.png");
	CTexture pLightTexture = CTexture("./data/light.png");

	// Transform Values
	double iMouseX, iMouseY;
	CVec2 vFireSize(static_cast<float>(pFireTexture.GetTexture()->width), static_cast<float>(pFireTexture.GetTexture()->height));
	
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
		ltex_drawrotsized(pWallTexture.GetTexture(), 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 0.0f,  WINDOW_WIDTH / static_cast<float>(pWallTexture.GetTexture()->width), WINDOW_HEIGHT / static_cast<float>(pWallTexture.GetTexture()->height));

		// Calculate desired angle and size value with ping-pong function (sin).
		float fFireAngles = 10.0f * sin(static_cast<float>(M_PI) * static_cast<float>(dElapsedTime));
		vFireSize.SetX((1.0f + 0.2f * sin(static_cast<float>(2.5f * M_PI) * static_cast<float>(dElapsedTime))) * static_cast<float>(pFireTexture.GetTexture()->width));
		vFireSize.SetY((1.0f + 0.2f * sin(static_cast<float>(2.5f * M_PI) * static_cast<float>(dElapsedTime))) * static_cast<float>(pFireTexture.GetTexture()->height));
		// Draw fire texture with additive blending.
		lgfx_setblend(BLEND_ADD);
		ltex_drawrotsized(pFireTexture.GetTexture(), static_cast<float>(iMouseX), static_cast<float>(iMouseY), fFireAngles, 0.5f, 0.5f, vFireSize.GetX(), vFireSize.GetY(), 0.0f, 0.0f, 1.0f, 1.0f);

		// Draw grille texture with alpha blending.
		lgfx_setblend(BLEND_ALPHA);
		ltex_drawrotsized(pGrilleTexture.GetTexture(), 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 0.0f,  WINDOW_WIDTH / static_cast<float>(pGrilleTexture.GetTexture()->width), WINDOW_HEIGHT / static_cast<float>(pGrilleTexture.GetTexture()->height));

		// Draw light texture with multiply blending.
		lgfx_setblend(BLEND_MUL);
		ltex_drawrotsized(pLightTexture.GetTexture(), static_cast<float>(iMouseX), static_cast<float>(iMouseY), 0.0f, 0.5f, 0.5f, static_cast<float>(pLightTexture.GetTexture()->width), static_cast<float>(pLightTexture.GetTexture()->height), 0.0f, 0.0f, 1.0f, 1.0f);
		// Draw left border.
		lgfx_setcolor(0.0f, 0.0f, 0.0f, 1.0f);
		lgfx_setblend(BLEND_SOLID);
		lgfx_drawrect(0, static_cast<float>(iMouseY) - static_cast<float>(pLightTexture.GetTexture()->height) / 2, static_cast<float>(iMouseX) - static_cast<float>(pLightTexture.GetTexture()->width) / 2, static_cast<float>(pLightTexture.GetTexture()->height));
		// Draw right border.
		lgfx_drawrect(static_cast<float>(iMouseX) + static_cast<float>(pLightTexture.GetTexture()->width) / 2, static_cast<float>(iMouseY) - static_cast<float>(pLightTexture.GetTexture()->height) / 2, WINDOW_WIDTH - (static_cast<float>(iMouseX) + static_cast<float>(pLightTexture.GetTexture()->width) / 2), static_cast<float>(pLightTexture.GetTexture()->height));
		// Draw upper border.
		lgfx_drawrect(static_cast<float>(iMouseX) - static_cast<float>(pLightTexture.GetTexture()->width) / 2, 0, static_cast<float>(pLightTexture.GetTexture()->width), static_cast<float>(iMouseY) - static_cast<float>(pLightTexture.GetTexture()->height) / 2);
		// Draw lower border.
		lgfx_drawrect(static_cast<float>(iMouseX) - static_cast<float>(pLightTexture.GetTexture()->width) / 2, static_cast<float>(iMouseY) + static_cast<float>(pLightTexture.GetTexture()->height) / 2, static_cast<float>(pLightTexture.GetTexture()->width), WINDOW_HEIGHT - (static_cast<float>(iMouseY) + static_cast<float>(pLightTexture.GetTexture()->height) / 2));
		// Draw upper-left corner.
		lgfx_drawrect(0, 0, static_cast<float>(iMouseX) - static_cast<float>(pLightTexture.GetTexture()->width) / 2, static_cast<float>(iMouseY) - static_cast<float>(pLightTexture.GetTexture()->height) / 2);
		// Draw upper-right corner.
		lgfx_drawrect(static_cast<float>(iMouseX) + static_cast<float>(pLightTexture.GetTexture()->width) / 2, 0, WINDOW_WIDTH - (static_cast<float>(iMouseX) + static_cast<float>(pLightTexture.GetTexture()->width) / 2), static_cast<float>(iMouseY) - static_cast<float>(pLightTexture.GetTexture()->height) / 2);
		// Draw lower-left corner.
		lgfx_drawrect(0, static_cast<float>(iMouseY) + static_cast<float>(pLightTexture.GetTexture()->height) / 2, static_cast<float>(iMouseX) - static_cast<float>(pLightTexture.GetTexture()->width) / 2, WINDOW_HEIGHT - (static_cast<float>(iMouseY) + static_cast<float>(pLightTexture.GetTexture()->height) / 2));
		// Draw lower-right corner.
		lgfx_drawrect(static_cast<float>(iMouseX) + static_cast<float>(pLightTexture.GetTexture()->width) / 2, static_cast<float>(iMouseY) + static_cast<float>(pLightTexture.GetTexture()->height) / 2, WINDOW_WIDTH - (static_cast<float>(iMouseX) + static_cast<float>(pLightTexture.GetTexture()->width) / 2), WINDOW_HEIGHT - (static_cast<float>(iMouseY) + static_cast<float>(pLightTexture.GetTexture()->height) / 2));
		
		glfwSwapBuffers(pWindow);
		glfwPollEvents();
	}

	glfwDestroyWindow(pWindow);
	glfwTerminate();

    return 0;
}
