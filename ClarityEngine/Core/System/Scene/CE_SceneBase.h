#pragma once

class CE_SceneBase
{
private:

    std::list<std::shared_ptr<CE_GameObject>> _gameObject;

protected:

    void AddObj(std::shared_ptr<CE_GameObject> obj);
    void DelObj(std::shared_ptr<CE_GameObject> obj);

public:

    CE_SceneBase();
    virtual ~CE_SceneBase() = 0;

    virtual void Construct() = 0;
    virtual void Begin() = 0;
    virtual void Update() = 0;
    virtual void ASyncUpdate() = 0;
    virtual void End() = 0;
    virtual void Destruct() = 0;

    void Draw();

    //Scene 재할당에 꼭 필요한 함수이므로 필수적으로 구현해야 함
    virtual CE_SceneBase* SceneInstance() = 0;
};