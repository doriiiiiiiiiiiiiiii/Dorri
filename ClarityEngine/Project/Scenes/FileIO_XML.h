#pragma once

class FileIO_XML final : public CE_SceneBase
{
private:


public:

    FileIO_XML() { Construct(); }
    ~FileIO_XML() { Destruct(); }

    void Construct() override;
    void Destruct() override;
    void Begin() override;
    void End() override;
    void Update() override;
    void ASyncUpdate() override;

    FileIO_XML* SceneInstance() { return new FileIO_XML; }
};