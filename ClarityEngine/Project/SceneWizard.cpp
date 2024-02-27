#include "pch.h"
#include "SceneWizard.h"

void SceneWizard::SceneRegister()    //Scene을 등록하는 함수이므로 건들지 말 것
{
    for (const auto& scene : _sceneRegs)
    {
        SceneMNGR->SaveScene(scene.first, scene.second);
    }
    SceneMNGR->LoadScene(L"Default");
}