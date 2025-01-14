#define LITE_GFX_IMPLEMENTATION
#define _USE_MATH_DEFINES

#include <litegfx.h>
#include <glfw3.h>
#include <cmath>
#include <sstream>
#include "Header Files/Vec2.h"

using namespace std;

constexpr unsigned int WINDOW_WIDTH = 500u;
constexpr unsigned int WINDOW_HEIGHT = 500u;

template <typename T>
string StringFromNumber(T oValue) {
    ostringstream sStream;
    sStream << fixed << oValue;
    return sStream.str();
}

int main() {
    if (!glfwInit()) {
        printf("Error initializing GLFW.\n");
        return -1;
    }

    GLFWwindow* pCurrentWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "", nullptr, nullptr);
    if (!pCurrentWindow) {
        printf("Error creating GLFW window.\n");
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(pCurrentWindow);

    lgfx_setup2d (WINDOW_WIDTH, WINDOW_HEIGHT);

    // Figure Variables
    const unsigned int uFigureSize = 50u;
    double dMousePosX, dMousePosY;
    float fOvalDistance = 80.0f;
    float fOvalAngle = 0.0f;
    float fAngularSpeed = 32.0f * static_cast<float>(M_PI) / 180.0f;
    
    CVec2 oScreenCenter(static_cast<float>(WINDOW_WIDTH) / 2, static_cast<float>(WINDOW_HEIGHT) / 2);

    // Time Variables
    double dCurrentTime;
    double dDeltaTime;
    double dLastTime = glfwGetTime();

    while (!glfwWindowShouldClose(pCurrentWindow)) {
        glfwPollEvents();
        
        dCurrentTime = glfwGetTime();
        dDeltaTime = dCurrentTime - dLastTime;
        dLastTime = dCurrentTime;

        lgfx_clearcolorbuffer(0.9f, 0.9f, 0.9f);

        // Draw static red square in the center of the screen.
        lgfx_setcolor(1.0f, 0.7f, 0.7f, 1.0f);
        lgfx_drawrect(static_cast<float>(WINDOW_WIDTH) / 2 - static_cast<float>(uFigureSize) / 2,
                      static_cast<float>(WINDOW_HEIGHT) / 2 - static_cast<float>(uFigureSize) / 2,
                      uFigureSize, uFigureSize);

        glfwGetCursorPos(pCurrentWindow, &dMousePosX, &dMousePosY);

        // Draw dynamic green square following mouse.
        lgfx_setcolor(0.7f, 1.0f, 0.7f, 1.0f);
        lgfx_drawrect(static_cast<float>(dMousePosX) - static_cast<float>(uFigureSize) / 2,
                      static_cast<float>(dMousePosY) - static_cast<float>(uFigureSize) / 2,
                      uFigureSize, uFigureSize);
        CVec2 oMousePos = CVec2(static_cast<float>(dMousePosX), static_cast<float>(dMousePosY));

        // Draw dynamic blue circle following mouse and orbiting at 32 degrees per second.
        lgfx_setcolor(0.7f, 0.7f, 1.0f, 1.0f);
        lgfx_drawoval(static_cast<float>(dMousePosX) + fOvalDistance * cos(fOvalAngle) - static_cast<float>(uFigureSize) / 2,
                      static_cast<float>(dMousePosY) + fOvalDistance * sin(fOvalAngle) - static_cast<float>(uFigureSize) / 2,
                      uFigureSize, uFigureSize);
        CVec2 oOvalPos = CVec2(static_cast<float>(dMousePosX) + fOvalDistance * cos(fOvalAngle) - static_cast<float>(uFigureSize) / 2,
                               static_cast<float>(dMousePosY) + fOvalDistance * sin(fOvalAngle) - static_cast<float>(uFigureSize) / 2);
        fOvalAngle += fAngularSpeed * static_cast<float>(dDeltaTime);
        if (fOvalAngle > 2 * M_PI) fOvalAngle = 0.0f;
        
        // Draw initials ("JPB") with black lines.
        lgfx_setcolor(0.0f, 0.0f, 0.0f, 1.0f);
            // "J"
        lgfx_drawline(20, 440, 20, 470);
        lgfx_drawline(20, 470, 25, 480);
        lgfx_drawline(25, 480, 40, 480);
        lgfx_drawline(40, 480, 45, 470);
        lgfx_drawline(45, 470, 45, 400);
        lgfx_drawline(25, 400, 65, 400);
            // "P"
        lgfx_drawline(70, 480, 70, 400);
        lgfx_drawline(70, 400, 110, 400);
        lgfx_drawline(110, 400, 115, 410);
        lgfx_drawline(115, 410, 115, 430);
        lgfx_drawline(115, 430, 110, 440);
        lgfx_drawline(110, 440, 70, 440);
            // "B"
        lgfx_drawline(120, 480, 120, 400);
        lgfx_drawline(120, 400, 160, 400);
        lgfx_drawline(160, 400, 165, 410);
        lgfx_drawline(165, 410, 165, 430);
        lgfx_drawline(165, 430, 160, 440);
        lgfx_drawline(120, 440, 160, 440);
        lgfx_drawline(160, 440, 165, 450);
        lgfx_drawline(165, 450, 165, 470);
        lgfx_drawline(165, 470, 160, 480);
        lgfx_drawline(120, 480, 160, 480);

        // Change window title to current distance and angle.
        ostringstream sWindowTitle;
        sWindowTitle << "Distance: " << StringFromNumber(oMousePos.Distance(oScreenCenter)) << " - Angle: " << StringFromNumber(oMousePos.Angle(oOvalPos) * 180.0f / M_PI) << " - JPB";
        glfwSetWindowTitle(pCurrentWindow, sWindowTitle.str().c_str());
        
        glfwSwapBuffers(pCurrentWindow);
    }

    glfwTerminate();
    
    return 0;
}