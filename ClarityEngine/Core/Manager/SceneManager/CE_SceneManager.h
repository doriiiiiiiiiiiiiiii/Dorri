#pragma once
#define SceneMNGR CE_SceneManager::GetInstance()

class CE_SceneManager final : public CE_Singleton<CE_SceneManager>
{
private:

    std::map<std::wstring, std::unique_ptr<CE_SceneBase>> _sceneDatas;
    std::map<std::wstring, std::unique_ptr<CE_SceneBase>>::iterator _sceneIt;

public:

    void SaveScene(const std::wstring& sceneName, CE_SceneBase* const scene);
    void LoadScene(const std::wstring& sceneName, const bool& isKeep = true);
    void DeleteScene(const std::wstring& sceneName);

    void Init();
    void SceneUpdate();
    void SceneASyncUpdate();
    void SceneDraw();
};