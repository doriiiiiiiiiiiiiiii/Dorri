#include "pch.h"
#include "CE_SceneManager.h"
#include "Project/SceneWizard.h"

void CE_SceneManager::Init()    //SceneWizard를 통해 Scene을 로딩
{
    SceneWizard sceneWz;
    sceneWz.SceneRegister();
}

void CE_SceneManager::SaveScene(const std::wstring& sceneName, CE_SceneBase* const scene)
{
    bool saveState = !_sceneDatas.contains(sceneName);

    if (saveState)
    {
        _sceneDatas.insert({ sceneName, nullptr });
        _sceneDatas[sceneName].reset(scene);
    }
    else
    {
        WIN32::MessageBoxW
        (
            Win32MNGR->GetWindowHandle(),
            L"Scene name is duplicated",
            L"CRITICAL ERROR",
            MB_ICONERROR
        );

        assert(saveState);
    }
}

//false가 인자로 전달되면 Scene의 인스턴스를 삭제합니다.
void CE_SceneManager::LoadScene(const std::wstring& sceneName, const bool& isKeep)
{
    bool loadState = _sceneDatas.contains(sceneName);

    if (loadState)
    {
        static bool validState = false;

        if (validState)
        {
            _sceneIt->second->End();
        }

        validState = true;

        _sceneIt = _sceneDatas.find(sceneName);
        _sceneIt->second->Begin();
    }
    else
    {
        WIN32::MessageBoxW
        (
            Win32MNGR->GetWindowHandle(),
            L"Scene not found",
            L"CRITICAL ERROR",
            MB_ICONERROR
        );

        assert(loadState);
    }

    if (!isKeep)    //Scene 인스턴스 재할당
    {
        _sceneIt->second.reset(_sceneIt->second->SceneInstance());
    }
}

void CE_SceneManager::DeleteScene(const std::wstring& sceneName)
{
    bool deleteState = _sceneDatas.contains(sceneName);

    if (deleteState)
    {
        _sceneDatas.erase(sceneName);
    }
    else
    {
        WIN32::MessageBoxW
        (
            Win32MNGR->GetWindowHandle(),
            L"Scene to delete not found",
            L"CRITICAL ERROR",
            MB_ICONERROR
        );

        assert(deleteState);
    }
}

void CE_SceneManager::SceneUpdate()
{
    assert(_sceneIt->second);
    _sceneIt->second->Update();
}

void CE_SceneManager::SceneASyncUpdate()
{
    assert(_sceneIt->second);
    _sceneIt->second->ASyncUpdate();
}

void CE_SceneManager::SceneDraw()
{
    assert(_sceneIt->second);
    _sceneIt->second->Draw();
}