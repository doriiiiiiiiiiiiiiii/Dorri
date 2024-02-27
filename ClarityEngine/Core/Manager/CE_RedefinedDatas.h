#pragma once

namespace ClarityEngine         //타입 재정의
{
    template <typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

    //DirectX Math(DXTK SimpleMath)
    using Vec2 = DirectX::SimpleMath::Vector2;
    using Vec3 = DirectX::SimpleMath::Vector3;
    using Vec4 = DirectX::SimpleMath::Vector4;
    using Color = DirectX::SimpleMath::Vector4;
    using Matrix = DirectX::SimpleMath::Matrix;
    using Quaternion = DirectX::SimpleMath::Quaternion;

    //Math
    constexpr DOUBLE CE_PI = 3.141592653589793;
    constexpr DOUBLE CE_EPSILON = 0.000001;
    constexpr DOUBLE CE_DEG2RAD(CE_PI / 180.0);
    constexpr DOUBLE CE_RAD2DEG(180.0 / CE_PI);
}

using namespace ClarityEngine; //네임스페이스 충돌 시 주석처리