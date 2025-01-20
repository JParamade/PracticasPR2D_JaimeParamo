#include "../Header Files/CSprite.h"

CSprite::CSprite(const ltex_t* _pTexture, int _iHFrames, int _iVFrames)
    : m_pTexture(_pTexture)
    , m_iHFrames(_iHFrames)
    , m_iVFrames(_iVFrames)
    , m_fFunction(nullptr)
    , m_pData(nullptr)
    , m_eMode(BLEND_SOLID)
    , m_fR(1.0f)
    , m_fG(1.0f)
    , m_fB(1.0f)
    , m_fA(1.0f)
{}

void CSprite::SetCallback(CallbackFunc _fFunction) {
    m_fFunction = _fFunction;
}

// Texture Data

void CSprite::SetUserData(void* _pData) {
    m_pData = _pData;
}

const ltex_t* CSprite::GetTexture() const {
    return m_pTexture;
}

void CSprite::SetTexture(const ltex_t* _pTexture, int _iHFrames, int _iVFrames) {
    m_pTexture = _pTexture;
}

// Blending Mode & Color

lblend_t CSprite::GetBlend() const {
    return m_eMode;
}

void CSprite::SetBlend(lblend_t _eMode) {
    m_eMode = _eMode;
}

float CSprite::GetRed() const {
    return m_fR;    
}

float CSprite::GetGreen() const {
    return m_fG;
}

float CSprite::GetBlue() const {
    return m_fB;
}

float CSprite::GetAlpha() const {
    return m_fA;
}

void CSprite::SetColor(float _fR, float _fG, float _fB, float _fA) {
    m_fR = _fR;
    m_fG = _fG;
    m_fB = _fB;
    m_fA = _fA;
}






