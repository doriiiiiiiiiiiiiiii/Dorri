#pragma once

class EasingTest final : public CE_SceneBase
{
private:

    std::shared_ptr<VideoPlayer> _video = nullptr;
    std::shared_ptr<Animator> _obj = nullptr;

    std::unique_ptr<Delay> _delay = nullptr;
    std::unique_ptr<Delay> _delay01 = nullptr;

    Sequence seq;

public:

    EasingTest() { Construct(); }
    ~EasingTest() { Destruct(); }

    void Construct() override;
    void Destruct() override;
    void Begin() override;
    void End() override;
    void Update() override;
    void ASyncUpdate() override;

    void Test();

    EasingTest* SceneInstance() { return new EasingTest; }
};