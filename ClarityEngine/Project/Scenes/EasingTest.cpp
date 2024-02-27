#include "pch.h"
#include "EasingTest.h"

/* Delay Test Code */
void EasingTest::Test() { std::cerr << "IN" << '\n'; }
void Test01() { std::cerr << "IN01" << '\n'; }

void EasingTest::Begin()
{
    Timer timer;

    timer.Start();

    _video = std::make_shared<VideoPlayer>(L"Project/Assets/Vid/sample.mp4");
    AddObj(_video);

    _obj = std::make_shared<Animator>
        (
            L"Project/Assets/Img/chara_walk.png",
            Vec2(600, 600),
            RECT(0, 0, 128, 128),
            UINT32(128),
            UINT8(8),
            RenderDir::HORIZONTAL
        );
    _obj->SetScale(2.f, 2.f);
    _obj->SetPos(Win32MNGR->GetWidth() * 0.5f, Win32MNGR->GetHeight() * 0.5f);
    _obj->SetColor(Vec4(1.f, 1.f, 1.f, 0.5f));

    AddObj(_obj);

    timer.Stop();

    std::cout << "[MS]" << timer.ElapsedTime() << "\n[SEC]" << timer.HighElapsedTime() << std::endl;

    /* Delay Test Code */
    //_delay = std::make_unique<Delay>(1000, 0, [this]() { this->Test(); });
    //_delay01 = std::make_unique<Delay>(1000, 10, Test01);

    std::vector<std::function<void()>> vec
    {
        []() {for (UINT64 i = 0; i <= 9000000000; i++) {} std::cerr << "DONE (1)" << std::endl; },
        []() {for (UINT64 i = 0; i <= 9000000000; i++) {} std::cerr << "DONE (2)" << std::endl; },
        []() {for (UINT64 i = 0; i <= 9000000000; i++) {} std::cerr << "DONE (3)" << std::endl; },
        []() {for (UINT64 i = 0; i <= 9000000000; i++) {} std::cerr << "DONE (4)" << std::endl; },
        []() {for (UINT64 i = 0; i <= 9000000000; i++) {} std::cerr << "DONE (5)" << std::endl; },
        []() {for (UINT64 i = 0; i <= 9000000000; i++) {} std::cerr << "DONE (6)" << std::endl; },
        []() {for (UINT64 i = 0; i <= 9000000000; i++) {} std::cerr << "DONE (7)" << std::endl; },
        []() {for (UINT64 i = 0; i <= 9000000000; i++) {} std::cerr << "DONE (8)" << std::endl; },
        []() {for (UINT64 i = 0; i <= 9000000000; i++) {} std::cerr << "DONE (9)" << std::endl; },
        []() {for (UINT64 i = 0; i <= 9000000000; i++) {} std::cerr << "DONE (10)" << std::endl; },
    };

    seq.AddJob(vec);
    seq.RunJobs();
    //seq.WaitEndJobs();

    ResNormalizer asd(Win32MNGR->GetWidth(), Win32MNGR->GetHeight());
    Vec2 Temp1 = asd.ToRelative(512, 256);
    Vec2 Temp2 = asd.ToAbsolute(Temp1.x, Temp1.y);

    std::cerr << "Rel Value : " << Temp1.x << " , " << Temp1.y << std::endl;
    std::cerr << "Abs Value : " << Temp2.x << " , " << Temp2.y << std::endl;
}

void EasingTest::Construct()
{

}

void EasingTest::Destruct()
{

}

void EasingTest::End()
{

}

void EasingTest::Update()
{
    static DoOnce leftKeyOnce;
    static DoOnce sideKeyOnce;

    if (InputMNGR->KeyPressed('D'))
    {
        _obj->SetFlip(Dir::DEFAULT);
        _obj->SetX(_obj->GetPos().x + 4);
    }

    if (InputMNGR->KeyPressed('A'))
    {
        _obj->SetFlip(Dir::HORIZONTAL);
        _obj->SetX(_obj->GetPos().x - 4);
    }

    if (InputMNGR->KeyPressed('W'))
    {
        _obj->SetY(_obj->GetPos().y - 4);
    }

    if (InputMNGR->KeyPressed('S'))
    {
        _obj->SetY(_obj->GetPos().y + 4);
    }

    if (InputMNGR->KeyPressed(MouseKeys::SIDE_UP) && NOT_PASSED(leftKeyOnce))
    {
        std::cerr << "DOWN" << std::endl;
        leftKeyOnce.Block();
    }

    if (InputMNGR->KeyReleased(MouseKeys::SIDE_UP) && PASSED(leftKeyOnce))
    {
        std::cerr << "UP" << std::endl;
        leftKeyOnce.Reset();
    }
}

void EasingTest::ASyncUpdate()
{

}