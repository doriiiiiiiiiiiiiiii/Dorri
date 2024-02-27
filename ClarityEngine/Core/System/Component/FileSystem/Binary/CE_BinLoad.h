#pragma once

class CE_BinLoad final
{
public:

    std::vector<std::string> LoadBin(const std::wstring& path);
};

using LoadBin = CE_BinLoad; //편의성을 위해 객체의 이름을 재정의, 충돌 시 주석처리