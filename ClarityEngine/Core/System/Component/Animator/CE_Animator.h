#pragma once

enum class RenderDir : UINT8    //스프라이트의 렌더링 방향 정의
{
    HORIZONTAL = 0,
    VERTICAL = 1,
};

class CE_Animator final : public CE_Painter
{
    using Super = CE_Painter;

private:

    std::vector<RECT> _frameData;

    RenderDir _renderDirection{};

    UINT32 _offset = 0;
    UINT8 _animFrame = 0;
    DOUBLE _stdFrameRate = 0.0;
    DOUBLE _frameLerp = 0.0;

private:

    void HorizontalRender();
    void VerticalRender();

public:

    CE_Animator
    (
        const std::wstring& path,
        const Vec2& pos,
        const RECT& spriteStartSize,
        const UINT32& spriteOffset,
        const UINT8& frame,
        const RenderDir& renderDir = RenderDir::HORIZONTAL,
        const Vec4& color = { 1.f, 1.f, 1.f, 1.f },
        const Vec2& scale = { 1.f, 1.f },
        const FLOAT& rot = 0.f,
        const FLOAT& depth = 0.f
    );
    ~CE_Animator();

    //애니메이션을 그리는 데 필요한 한 프레임의 크기를 받거나 조정
    const UINT32& GetSpriteOffset() const noexcept { return _offset; }
    void SetSpriteOffset(const UINT32& offset) noexcept { _offset = offset; };

    //재생할 애니메이션의 프레임 수를 받거나 조정
    const UINT32& GetFrame() const noexcept { return _animFrame; }
    void SetFrame(const UINT32& frame) noexcept { _animFrame = frame; }

    //애니메이션 재생속도 값을 받거나 조정
    const DOUBLE& GetAnimFrameRate() const noexcept { return _stdFrameRate; }
    void SetAnimFrameRate(const DOUBLE& frameRate) noexcept { _stdFrameRate = frameRate; }

    //애니메이션을 재생하는 방향 값을 받거나 조정
    const RenderDir& GetRenderDirection() const noexcept { return _renderDirection; }
    void SetRenderDirection(const RenderDir& renderDir);

    //선형보간 기준 값을 받음
    const DOUBLE& GetFrameLerp() const noexcept { return _frameLerp; }

    //애니메이션 데이터를 뒤집음
    void SetAnimReverse() noexcept { std::reverse(_frameData.begin(), _frameData.end()); }

    //애니메이션의 프레임을 선형보간
    void Update() override;

    //렌더링
    void Render() override;
};

using Animator = CE_Animator; //편의성을 위해 객체의 이름을 재정의, 충돌 시 주석처리