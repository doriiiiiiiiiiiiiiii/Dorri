#pragma once

class CE_BinSave final
{
public:

    void SaveBin(const std::wstring& path, const std::vector<std::string>& data);
};

using SaveBin = CE_BinSave; //편의성을 위해 객체의 이름을 재정의, 충돌 시 주석처리