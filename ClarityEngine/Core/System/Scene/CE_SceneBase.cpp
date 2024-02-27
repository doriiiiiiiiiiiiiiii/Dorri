#include "pch.h"
#include "CE_SceneBase.h"

CE_SceneBase::CE_SceneBase()
{

}

CE_SceneBase::~CE_SceneBase()
{

}

void CE_SceneBase::AddObj(std::shared_ptr<CE_GameObject> obj)
{
    _gameObject.push_back(obj);
}

void CE_SceneBase::DelObj(std::shared_ptr<CE_GameObject> obj)
{
    auto objIt = std::find(_gameObject.begin(), _gameObject.end(), obj);

    if (*objIt == obj)
    {
        _gameObject.erase(objIt);
    }
    else
    {
        WIN32::MessageBoxW
        (
            Win32MNGR->GetWindowHandle(),
            L"Object not found",
            L"CRITICAL ERROR",
            MB_ICONERROR
        );
        assert(false);
    }
}

void CE_SceneBase::Draw()
{
    for (const auto& objs : _gameObject)
    {
        objs->Update();
        objs->Render();
    }
}