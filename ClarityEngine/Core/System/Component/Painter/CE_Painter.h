#pragma once

enum class Dir : UINT8      //렌더링 방향 정의
{
    DEFAULT = 0,
    HORIZONTAL = 1,
    VERTICAL = 2,
    BOTH = (HORIZONTAL | VERTICAL)
};

enum class SortMode : UINT8
{
    STACK = 0,      //스프라이트 데이터를 축적해 한 번에 렌더링
    NO_WAIT = 1,    //스프라이트를 즉시 렌더링
    TEX_QUEUE = 2,  //스프라이트를 텍스처별로 정렬 후 렌더링
    FORWARD = 3,    //Depth가 감소하는 순서로 스프라이트를 렌더링 (뒤에서 앞으로)
    BACKWARD = 4    //Depth가 증가하는 순서로 스프라이트를 렌더링 (앞에서 뒤로)
};

class CE_Painter : public CE_GameObject
{
protected:

    std::unique_ptr<DirectX::SpriteBatch> _texture = nullptr;

    //텍스처를 렌더링할 때 CommonStates를 사용해 렌더링 파이프라인을 제어
    std::unique_ptr<DirectX::CommonStates> _comState = nullptr;

    ComPtr<ID3D11ShaderResourceView> _srv = nullptr;

    DirectX::SpriteEffects _flipState = DirectX::SpriteEffects::SpriteEffects_None;

    std::wstring _path;     //이미지의 경로를 저장 (LPCWSTR == wstring)

    RECT _imgRenderSize{};  //렌더링 크기                  (AUTO CALCULATION)
    Vec2 _imgPivot{};       //이미지의 중심축(피벗)         (AUTO CALCULATION)
    Vec2 _imgScale{};       //이미지의 크기 지정
    Vec2 _imgPosition{};    //뷰포트에서 렌더링 할 위치
    Vec4 _imgColor{};       //이미지의 컬러와 알파값
    FLOAT _imgRotation = 0; //이미지의 각도 ('라디안'이 아닌 '도' 단위를 저장)
    FLOAT _imgDepth = 0;    //이미지 Depth를 저장           (NOT NECESSARY)

protected:

    void Load();    //이미지를 메모리에 로드 후 텍스처로 사용할 준비
    void Setup();   //텍스처 래핑 좌표 및 기타 관련 정보를 처리

public:

    CE_Painter
    (
        const std::wstring& path,
        const Vec2& pos,
        const Vec4& color = { 1.f, 1.f, 1.f, 1.f },
        const Vec2& scale = { 1.f, 1.f },
        const FLOAT& rot = 0,
        const FLOAT& depth = 0
    );

    virtual ~CE_Painter();

    //색상 및 알파값
    const Vec4& GetColor() const noexcept { return _imgColor; }
    void SetColor(const Vec4& color) noexcept { _imgColor = color; }

    //스케일
    const Vec2& GetScale() const noexcept { return _imgScale; }
    void SetScale(const FLOAT& x, const FLOAT& y) noexcept { _imgScale.x = x; _imgScale.y = y; }

    //회전
    const FLOAT& GetAngle() const noexcept { return _imgRotation; }
    void SetAngle(const FLOAT& deg) noexcept { _imgRotation = deg; }

    //위치
    const Vec2& GetPos() const noexcept { return _imgPosition; }
    void SetPos(const FLOAT& x, const FLOAT& y) noexcept { _imgPosition.x = x; _imgPosition.y = y; }
    void SetX(const FLOAT& x) noexcept { _imgPosition.x = x; }
    void SetY(const FLOAT& y) noexcept { _imgPosition.y = y; }

    //Depth
    const FLOAT& GetDepth() noexcept { return _imgDepth; }
    void SetDepth(const FLOAT& z) noexcept { _imgDepth = z; }

    //중심축(피벗)
    const Vec2& GetPivot() const noexcept { return _imgPivot; }
    void SetPivot(const FLOAT& x, const FLOAT& y) noexcept { _imgPivot.x = x; _imgPivot.y = y; }

    //이미지 렌더링 방향
    void SetFlip(const Dir& dir = Dir::DEFAULT) noexcept;

    //이미지 소스 변경
    void SetImage(const std::wstring& path) { _path = path; CE_Painter::Load(); CE_Painter::Setup(); }

    //렌더링
    void Render() override;
};

using Painter = CE_Painter; //편의성을 위해 객체의 이름을 재정의, 충돌 시 주석처리