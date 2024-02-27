#pragma once

class FileIO_BIN final : public CE_SceneBase
{
private:


public:

    FileIO_BIN() { Construct(); }
    ~FileIO_BIN() { Destruct(); }

    void Construct() override;
    void Destruct() override;
    void Begin() override;
    void End() override;
    void Update() override;
    void ASyncUpdate() override;

    FileIO_BIN* SceneInstance() { return new FileIO_BIN; }
};