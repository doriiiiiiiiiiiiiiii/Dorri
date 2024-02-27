#include "pch.h"
#include "CE_ResNormalizer.h"

CE_ResNormalizer::CE_ResNormalizer(const INT64& x, const INT64& y)
    : _screenX(x)
    , _screenY(y)
{

}

CE_ResNormalizer::~CE_ResNormalizer()
{

}

Vec2 CE_ResNormalizer::ToRelative(const INT64& absX, const INT64& absY)
{
    return Vec2
    (
        static_cast<FLOAT>(absX) / _screenX,
        static_cast<FLOAT>(absY) / _screenY
    );
}

Vec2 CE_ResNormalizer::ToAbsolute(const DOUBLE& relX, const DOUBLE& relY)
{
    return Vec2
    (
        static_cast<FLOAT>(relX * _screenX),
        static_cast<FLOAT>(relY * _screenY)
    );
}