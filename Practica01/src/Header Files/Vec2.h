#pragma once

class CVec2 {
public:
    CVec2();
    CVec2(float _fX, float _fY);
    ~CVec2();
    CVec2(const CVec2& other);
    
    CVec2& operator=(const CVec2& other);
    CVec2& operator+=(const CVec2& other);
    CVec2& operator-=(const CVec2& other);
    CVec2& operator*=(const CVec2& other);
    CVec2& operator/=(const CVec2& other);
    bool operator==(const CVec2& other);
    bool operator!=(const CVec2& other);
    bool operator<(const CVec2& other);
    bool operator>(const CVec2& other);
    bool operator<=(const CVec2& other);
    bool operator>=(const CVec2& other);
    
private:
    float m_fX;
    float m_fY;
};
