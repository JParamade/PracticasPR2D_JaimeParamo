#include "../Header Files/Texture.h"
#include <stb_image.h>

CTexture::CTexture(const char* _sFileName) {
    m_pTexture = LoadTexture(_sFileName);
}

ltex_t* CTexture::LoadTexture(const char* _sFilename) {
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

ltex_t* CTexture::GetTexture() const {
    return m_pTexture;
}    