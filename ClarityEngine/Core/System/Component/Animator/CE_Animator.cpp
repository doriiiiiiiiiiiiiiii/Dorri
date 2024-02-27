#include "pch.h"
#include "CE_Animator.h"

CE_Animator::CE_Animator
(
    const std::wstring& path,
    const Vec2& pos,
    const RECT& spriteStartSize,
    const UINT32& spriteOffset,
    const UINT8& frame,
    const RenderDir& renderDir,
    const Vec4& color,
    const Vec2& scale,
    const FLOAT& rot,
    const FLOAT& depth
)
    : Super(path, pos, color, scale, rot, depth)
{
    _renderDirection = renderDir;
    _imgRenderSize = spriteStartSize;
    _offset = spriteOffset;

    _animFrame = frame;
    _stdFrameRate = GameMNGR->GetTargetFPS();

    _imgPivot.x = static_cast<FLOAT>(spriteOffset / 2);
    _imgPivot.y = static_cast<FLOAT>(spriteOffset / 2);

    CE_Animator::SetRenderDirection(_renderDirection);
}

CE_Animator::~CE_Animator()
{

}

void CE_Animator::SetRenderDirection(const RenderDir& renderDir)
{
    _frameData.resize(_animFrame);

    switch (renderDir)
    {
    case RenderDir::HORIZONTAL:

        _renderDirection = RenderDir::HORIZONTAL;
        CE_Animator::HorizontalRender();
        break;

    case RenderDir::VERTICAL:

        _renderDirection = RenderDir::VERTICAL;
        CE_Animator::VerticalRender();
        break;
    }
}

void CE_Animator::HorizontalRender()
{
    RECT tempRenderSize = _imgRenderSize;

    for (UINT8 cutoff = 0; cutoff < _animFrame; cutoff++)
    {
        _frameData[cutoff] = tempRenderSize;

        tempRenderSize.left += _offset;
        tempRenderSize.right += _offset;
    }
}

void CE_Animator::VerticalRender()
{
    RECT tempRenderSize = _imgRenderSize;

    for (UINT8 cutoff = 0; cutoff < _animFrame; cutoff++)
    {
        _frameData[cutoff] = tempRenderSize;

        tempRenderSize.top += _offset;
        tempRenderSize.bottom += _offset;
    }
}

void CE_Animator::Update()
{
    _frameLerp += (_animFrame / _stdFrameRate);
    
    if (_frameLerp >= _animFrame)
    {
        _frameLerp = 0.0;
    }
}

void CE_Animator::Render()
{
    _texture->Begin(DirectX::SpriteSortMode_Deferred, _comState->NonPremultiplied());

    _texture->Draw
    (
        _srv.Get(),
        _imgPosition,
        &_frameData[static_cast<UINT8>(_frameLerp)],
        _imgColor,
        _imgRotation,
        _imgPivot,
        _imgScale,
        _flipState,
        _imgDepth
    );

    _texture->End();
}