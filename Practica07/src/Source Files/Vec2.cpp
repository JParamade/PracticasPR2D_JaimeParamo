#include "../Header Files/Vec2.h"
#include <cmath>

// Constructors

CVec2::CVec2()
    : m_fX(0)
    , m_fY(0)
{}

CVec2::CVec2(float _fX, float _fY)
    : m_fX(_fX)
    , m_fY(_fY)
{}

// Arithmetic Operators

CVec2& CVec2::operator=(const CVec2& _rOther) {
    if (this != &_rOther) {
        m_fX = _rOther.m_fX;
        m_fY = _rOther.m_fY;
    }
    
    return *this;
}

CVec2 CVec2::operator+(const CVec2& _rOther) const {
    return {m_fX + _rOther.m_fX, m_fY + _rOther.m_fY};
}

CVec2 CVec2::operator-(const CVec2& _rOther) const {
    return {m_fX - _rOther.m_fX, m_fY - _rOther.m_fY};
}

CVec2 CVec2::operator*(float _fValue) const {
    return {m_fX * _fValue, m_fY * _fValue};
}

CVec2 CVec2::operator/(float _fValue) const {
    return {m_fX / _fValue, m_fY / _fValue};
}

CVec2& CVec2::operator+=(const CVec2& _rOther) {
    m_fX += _rOther.m_fX;
    m_fY += _rOther.m_fY;

    return *this;
}

CVec2& CVec2::operator-=(const CVec2& _rOther) {
    m_fX -= _rOther.m_fX;
    m_fY -= _rOther.m_fY;

    return *this;
}

CVec2& CVec2::operator*=(float _fValue) {
    m_fX *= _fValue;
    m_fY *= _fValue;

    return *this;    
}

CVec2& CVec2::operator/=(float _fValue) {
    m_fX /= _fValue;
    m_fY /= _fValue;

    return *this;    
}

// Logic Operators

bool CVec2::operator==(const CVec2& _rOther) const {
    return Magnitude() == _rOther.Magnitude() && Normalized() == _rOther.Normalized();
}

bool CVec2::operator!=(const CVec2& _rOther) const {
    return Magnitude() != _rOther.Magnitude() || Normalized() != _rOther.Normalized();
}

// Methods

float CVec2::GetX() const {
    return m_fX;
}

float CVec2::GetY() const {
    return m_fY;
}

void CVec2::SetX(float _fValue) {
    m_fX = _fValue;
}

void CVec2::SetY(float _fValue) {
    m_fY = _fValue;
} 

float CVec2::Magnitude() const {
    return sqrt(m_fX * m_fX + m_fY * m_fY);
}

CVec2& CVec2::Normalize() {
    return *this /= Magnitude();
}

CVec2 CVec2::Normalized() const {
    return *this / Magnitude();
}

CVec2 CVec2::Abs() const {
    return {m_fX < 0 ? -m_fX : m_fX, m_fY < 0 ? -m_fY : m_fY};
}

float CVec2::Dot(const CVec2& _rOther) const {
    return m_fX * _rOther.m_fX + m_fY * _rOther.m_fY;
}

float CVec2::Angle(const CVec2& _rOther) const {
    return atan2(_rOther.m_fY - m_fY, _rOther.m_fX - m_fX);
}

float CVec2::Distance(const CVec2& _rOther) const {
    return sqrt((_rOther.m_fX - m_fX) * (_rOther.m_fX - m_fX) + (_rOther.m_fY - m_fY) * (_rOther.m_fY - m_fY));
}

CVec2& CVec2::Add(const CVec2& _rOther) {
    return *this += _rOther;
}

CVec2& CVec2::Add(float _fX, float _fY) {
    return *this += CVec2(_fX, _fY);
}

CVec2& CVec2::Sub(const CVec2& _rOther) {
    return *this -= _rOther;
}

CVec2& CVec2::Sub(float _fX, float _fY) {
    return *this -= CVec2(_fX, _fY);
}

CVec2& CVec2::Mul(float _fValue) {
    return *this *= _fValue;
}

CVec2& CVec2::Div(float _fValue) {
    return *this /= _fValue;
}