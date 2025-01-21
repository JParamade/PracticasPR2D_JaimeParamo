#define STB_IMAGE_IMPLEMENTATION

#include "../Header Files/Sprite.h"
#include "stb_image.h"
#include <cmath>

void CTexture::LoadTexture(const char* _sFilename) {
    int iWidth, iHeight;
	
    stbi_uc* sBuffer = stbi_load(_sFilename, &iWidth, &iHeight, nullptr, 4);
    if (!sBuffer) {
        static_cast<void>(fprintf(stderr, "Error: File '%s' failed to load.\n", _sFilename));
        return;
    }
	
    ltex_t* pTexture = ltex_alloc(iWidth, iHeight, 1);
    if (!pTexture) {
        static_cast<void>(fprintf(stderr, "Error: Texture couldn't be allocated.\n"));
        stbi_image_free(sBuffer);
        return;
    }
	
    ltex_setpixels(pTexture, sBuffer);
    stbi_image_free(sBuffer);

    m_pTexture = pTexture;
}

CTexture::CTexture(const char* _sFilename) {
    LoadTexture(_sFilename);
}

CTexture::~CTexture() {
    if (m_pTexture) ltex_free(m_pTexture);  
}

CTexture::CTexture(CTexture&& _rOther) noexcept
    : m_pTexture(_rOther.m_pTexture) {
    _rOther.m_pTexture = nullptr;
}

CTexture& CTexture::operator=(CTexture&& _rOther) noexcept {
    if (this != &_rOther) {
        if (m_pTexture) ltex_free(m_pTexture);
        m_pTexture = _rOther.m_pTexture;
        _rOther.m_pTexture = nullptr;
    }
    return *this;
}

ltex_t* CTexture::GetTexture() const {
    return m_pTexture;
}

CSprite::CSprite(const ltex_t* _pTexture, int _iHFrames, int _iVFrames)
    : m_pTexture(_pTexture)
    , m_iHFrames(_iHFrames)
    , m_iVFrames(_iVFrames)
    , m_fCurrentFrame(0)
    , m_iFps(0)
    , m_fFunction(nullptr)
    , m_pData(nullptr)
    , m_eMode(BLEND_SOLID)
    , m_fR(1.0f)
    , m_fG(1.0f)
    , m_fB(1.0f)
    , m_fA(1.0f)
    , m_vPosition(0.0f, 0.0f)
    , m_fAngle(0.0f)
    , m_vScale(1.0f, 1.0f)
    , m_vPivot(0.0f, 0.0f)
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

// Transform

const CVec2& CSprite::GetPosition() const {
    return m_vPosition;
}

void CSprite::SetPosition(const CVec2& _vPos) {
    m_vPosition = _vPos;
}

float CSprite::GetAngle() const {
    return m_fAngle;
}

void CSprite::SetAngle(float _fAngle) {
    m_fAngle = _fAngle;
}

const CVec2& CSprite::GetScale() const {
    return m_vScale;
}

void CSprite::SetScale(const CVec2& _vScale) {
    m_vScale = _vScale;
}

CVec2 CSprite::GetSize() const {
    return {static_cast<float>(m_pTexture->width) / static_cast<float>(m_iHFrames) * m_vScale.GetX(),static_cast<float>(m_pTexture->height) / static_cast<float>(m_iHFrames) * m_vScale.GetY()};
}

const CVec2& CSprite::GetPivot() const {
    return m_vPivot;
}

void CSprite::SetPivot(const CVec2& _vPivot) {
    m_vPivot = _vPivot;
}

// Additional Data

int CSprite::GetHFrames() const {
    return m_iHFrames;
}

int CSprite::GetVFrames() const {
    return m_iVFrames;
}

int CSprite::GetFps() const {
    return m_iFps;
}

void CSprite::SetFps(int _iFps) {
    m_iFps = _iFps;
}

float CSprite::GetCurrentFrame() const {
    return m_fCurrentFrame;
}

void CSprite::SetCurrentFrame(int _iFrame) {
    m_fCurrentFrame = static_cast<float>(_iFrame);
}

// Execution Functions

void CSprite::Update(float _fDeltaTime) {
    if (m_fFunction) {
        m_fFunction(*this, _fDeltaTime);
        
        
        
        if (m_fCurrentFrame > static_cast<float>(m_iHFrames)) m_fCurrentFrame = 0;
        if (m_fCurrentFrame < 0) m_fCurrentFrame = static_cast<float>(m_iHFrames);
        
        SetCurrentFrame(static_cast<int>(m_fCurrentFrame));
    }
}

void CSprite::Draw() const {
    int iFrameIndex = static_cast<int>(m_fCurrentFrame);
    const float fU = static_cast<float>(iFrameIndex % m_iHFrames) * GetSize().GetX();
    const float fV = static_cast<float>(iFrameIndex / m_iVFrames) * GetSize().GetY();
    
    lgfx_setblend(m_eMode);
    lgfx_setcolor(m_fR, m_fG, m_fB, m_fA);
    ltex_drawrotsized(m_pTexture, m_vPosition.GetX(), m_vPosition.GetY(), m_fAngle, m_vPivot.GetX(), m_vPivot.GetY(), GetSize().GetX(),GetSize().GetY(),fU,fV, fU + GetSize().GetX(), fV + GetSize().GetY());
}