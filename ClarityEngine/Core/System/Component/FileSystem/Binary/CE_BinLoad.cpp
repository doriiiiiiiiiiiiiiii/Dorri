#include "pch.h"
#include "CE_BinLoad.h"

std::vector<std::string> CE_BinLoad::LoadBin(const std::wstring& path)
{
    std::vector<std::string> data;

    std::ifstream file((path + L".bin"), std::ios::in | std::ios::binary);

    if (!file.is_open())
    {
        return data;
    }

    std::string line;

    while (std::getline(file, line))
    {
        data.push_back(line);
    }

    file.close();

    return data;
}