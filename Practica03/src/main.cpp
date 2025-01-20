#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include <glfw3.h>
#include <iostream>
#include "../src/Header Files/Sprite.h"
#include "stb_image.h"

using namespace std;

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
    ltex_t* pTestTexture = LoadTexture("../data/bee_anim.png");
    CSprite oSprite = CSprite(pTestTexture);

    
    
    return 0;
}
