#include "pch.h"
#include "FileIO_XML.h"

void FileIO_XML::Begin()
{
    SaveXML save("MyTest");

    std::vector<std::pair<std::string, std::string>> noGroup
    {
        {"add1", std::to_string(100)},
        {"add2", std::to_string(11.11)},
        {"txt1", "SampleText1"},
        {"add3", std::to_string(0.123123)},
        {"txt2", "SampleText2"},
        {"add4", std::to_string(400)},
        {"txt3", "SampleText3"}
    };

    std::vector<std::pair<std::string, std::string>> group
    {
        {"value1", std::to_string(100)},
        {"value2", std::to_string(11.11)},
        {"value3", std::to_string(0.123123)},
        {"value4", std::to_string(400)},
        {"txt", "Example!"}
    };

    save.Add(noGroup);
    save.AddGroup("SampleGroup", group);

    LoadXML load("MyTest");
    std::cout << "[XML LOADER] : " << load.GetGroupString("SampleGroup", "txt") << '\n' << std::endl;

    SceneMNGR->LoadScene(L"EASING");
}

void FileIO_XML::Construct()
{
}

void FileIO_XML::Destruct()
{

}

void FileIO_XML::End()
{
    std::cout << "XML OUT" << std::endl;
}

void FileIO_XML::Update()
{
}

void FileIO_XML::ASyncUpdate()
{
}
