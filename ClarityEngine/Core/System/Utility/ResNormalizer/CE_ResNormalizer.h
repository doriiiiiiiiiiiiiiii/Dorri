#pragma once

//해상도를 '0.0'~'1.0' 사잇값으로 정규화함
class CE_ResNormalizer final
{
private:

    INT64 _screenX;
    INT64 _screenY;

public:

    CE_ResNormalizer(const INT64& x, const INT64& y);
    ~CE_ResNormalizer();

    const INT64& GetTargetX() const noexcept { return _screenX; }
    void SetTargetX(const INT64& x) noexcept { _screenX = x; }

    const INT64& GetTargetY() const noexcept { return _screenY; }
    void SetTargetY(const INT64& y) noexcept { _screenY = y; }

    Vec2 ToRelative(const INT64& absX, const INT64& absY);
    Vec2 ToAbsolute(const DOUBLE& relX, const DOUBLE& relY);
};

using ResNormalizer = CE_ResNormalizer; //편의성을 위해 객체의 이름을 재정의, 충돌 시 주석처리