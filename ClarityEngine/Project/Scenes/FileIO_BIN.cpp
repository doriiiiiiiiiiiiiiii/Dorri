#include "pch.h"
#include "FileIO_BIN.h"

void FileIO_BIN::Begin()
{
    SaveBin save;

    std::vector<std::string> save_nums
    {
        {std::to_string(100)},
        {std::to_string(1.1)},
        {std::to_string(200)},
        {std::to_string(0.2)},
        {std::to_string(300)},
        {std::to_string(1412.1223)},
        {"TestString1"},
        {std::to_string(-111.23212)},
        {"TestString2"},
        {std::to_string(-9911.2212)},
        {std::to_string(600)},
        {"TestString3"},
        {std::to_string(700)},
        {"TestString4"}
    };
    save.SaveBin(L"MyTest", save_nums);


    LoadBin load;

    std::vector<std::string> load_nums;

    load_nums = load.LoadBin(L"MyTest");

    for (const auto& element : load_nums)
    {
        std::cout << "[BIN LOADER] : " << element << std::endl;
    }
}

void FileIO_BIN::Construct()
{
}

void FileIO_BIN::Destruct()
{
}

void FileIO_BIN::End()
{
}


void FileIO_BIN::Update()
{
}

void FileIO_BIN::ASyncUpdate()
{
}
