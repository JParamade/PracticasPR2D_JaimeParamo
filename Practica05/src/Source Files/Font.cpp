#include "../Header Files/Font.h"

// System
#include <stdio.h>

// Font
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

// STL
#include <algorithm>

CFont::CFont()
  : m_sAlphaMap(nullptr)
  , m_pTexture(nullptr)
  , m_vTextSize({0.f , 0.f})
  , m_fFontHeight(0.0f)
{}

CFont::~CFont() {
  if (m_pTexture) {
    ltex_free(m_pTexture);
    m_pTexture = nullptr;
  }
}

CFont* CFont::Load(const char* _sFilename, float _fHeight) {
  FILE* pFile = nullptr;

  // Open File.
  if (fopen_s(&pFile, _sFilename, "rb") != 0 || !pFile) {
    static_cast<void>(fprintf(stderr, "Error: Could not open font file '%s'\n", _sFilename));
    return nullptr;
  }

  // Seek Size.
  fseek(pFile, 0, SEEK_END);
  long lFileSize = ftell(pFile);
  fseek(pFile, 0, SEEK_SET);

  if (lFileSize <= 0) {
    fclose(pFile);
    static_cast<void>(fprintf(stderr, "Error: Font file '%s' is empty or unreadable\n", _sFilename));
    return nullptr;
  }

  // Create Buffer & Read File.
  unsigned char* pBuffer = new unsigned char[lFileSize];
  size_t iBytesRead = fread(pBuffer, 1, lFileSize, pFile);
  fclose(pFile);
  
  if (iBytesRead != lFileSize) {
    delete[] pBuffer;
    static_cast<void>(fprintf(stderr, "Error: Failed to read entire font file '%s'\n", _sFilename));
    return nullptr;
  }

  // Create Font.
  CFont* pFont = new CFont();
  pFont->m_vTextSize.SetX(512);
  pFont->m_vTextSize.SetY(512);
  pFont->m_sAlphaMap = new unsigned char[pFont->m_vTextSize.GetX() * pFont->m_vTextSize.GetY()];

  if (stbtt_BakeFontBitmap(
      pBuffer, 
      0, 
      _fHeight, 
      pFont->m_sAlphaMap, 
      pFont->m_vTextSize.GetX(), pFont->m_vTextSize.GetY(), 
      32, 96, 
      pFont->m_oCharData
    ) < 0) {
        delete[] pFont->m_sAlphaMap;
        delete[] pBuffer;
        delete pFont;
        static_cast<void>(fprintf(stderr, "Error: Failed to bake font bitmap from '%s'\n", _sFilename));
        return nullptr;
  }

  // Conversion from 1-byte Alpha to RGBA.
  unsigned int uWidth = static_cast<unsigned int>(pFont->m_vTextSize.GetX());
  unsigned int uHeight = static_cast<unsigned int>(pFont->m_vTextSize.GetY());
  unsigned char* sRGBA = new unsigned char[uWidth * uHeight * 4];
  for (unsigned int uIndex = 0; uIndex < uWidth * uHeight; ++uIndex) {
    sRGBA[uIndex * 4 + 0] = 255;
    sRGBA[uIndex * 4 + 1] = 255;
    sRGBA[uIndex * 4 + 2] = 255;
    sRGBA[uIndex * 4 + 3] = pFont->m_sAlphaMap[uIndex];
  }

  pFont->m_pTexture = ltex_alloc(pFont->m_vTextSize.GetX(), pFont->m_vTextSize.GetY(), 0);
  ltex_setpixels(pFont->m_pTexture, sRGBA);

  pFont->m_fFontHeight = _fHeight;

  // Free Memory.
  delete[] sRGBA;
  delete[] pFont->m_sAlphaMap;
  delete[] pBuffer;

  return pFont;
}

float CFont::GetHeight() const {
  return m_fFontHeight;
}

CVec2 CFont::GetTextSize(const char* _sText) const {
  float fPosX = 0.f;
  float fPosY = 0.f;

  stbtt_aligned_quad oQuad;

  for (const char* pChar = _sText; *pChar; ++pChar) {
    if (*pChar < 32 || *pChar > 126) continue;
    stbtt_GetBakedQuad(m_oCharData, m_vTextSize.GetX(), m_vTextSize.GetY(), *pChar - 32, &fPosX, &fPosY, &oQuad, 1);
  }

  return CVec2(fPosX, m_fFontHeight);
}

void CFont::Draw(const char* _sText, const CVec2& _rPos) const {
  lgfx_setblend(BLEND_ALPHA);
  
  float fPosX = _rPos.GetX();
  float fPosY = _rPos.GetY();
  
  stbtt_aligned_quad oQuad;
  for (const char* pChar = _sText; *pChar; ++pChar) {
    char cChar = *pChar;
    if (cChar < 32 || cChar > 126) continue;

    stbtt_GetBakedQuad(m_oCharData, m_vTextSize.GetX(), m_vTextSize.GetY(), cChar - 32, &fPosX, &fPosY, &oQuad, 1);

    ltex_drawrotsized(
      m_pTexture,
      oQuad.x0, oQuad.y0,
      0.0f,
      0.0f, 0.0f,
      oQuad.x1 - oQuad.x0,
      oQuad.y1 - oQuad.y0,
      oQuad.s0, oQuad.t0,
      oQuad.s1, oQuad.t1
    );
  }
}