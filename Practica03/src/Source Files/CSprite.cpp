#include "../Header Files/CSprite.h"

CSprite::CSprite(const ltex_t* _pTexture, int _iHFrames, int _iVFrames)
    : m_pTexture(_pTexture)
    , m_iHFrames(_iHFrames)
    , m_iVFrames(_iVFrames)
    , m_fFunction(nullptr)
    , m_pData(nullptr)
{}

void CSprite::SetCallback(CallbackFunc _fFunction) {
    m_fFunction = _fFunction;
}

void CSprite::SetUserData(void* _pData) {
    m_pData = _pData;
}

const ltex_t* CSprite::GetTexture() const {
    return m_pTexture;
}

void CSprite::SetTexture(const ltex_t* _pTexture, int _iHFrames, int _iVFrames) {
    m_pTexture = _pTexture;
}





