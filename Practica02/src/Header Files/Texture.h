#pragma once

#include "litegfx.h"

class CTexture {
private:
    ltex_t* m_pTexture;
public:
    CTexture(const char* _sFileName);
    
    static ltex_t* LoadTexture(const char* _sFilename);
    ltex_t* GetTexture() const;    
};
