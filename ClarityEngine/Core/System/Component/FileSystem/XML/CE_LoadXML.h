#pragma once

class CE_LoadXML final
{
private:

    tinyxml2::XMLDocument _doc;
    tinyxml2::XMLNode* _node = nullptr;
    tinyxml2::XMLElement* _element = nullptr;

    //파일경로(nodeName)
    std::string _path;

private:

    void Init();

public:

    CE_LoadXML(const std::string& path);
    ~CE_LoadXML();

    std::string GetString(const std::string& key);
    INT64 GetINT64(const std::string& key);
    DOUBLE GetDOUBLE(const std::string& key);

    std::string GetGroupString(const std::string& element, const std::string& key);
    INT64 GetGroupINT64(const std::string& element, const std::string& key);
    DOUBLE GetGroupDOUBLE(const std::string& element, const std::string& key);
};

using LoadXML = CE_LoadXML; //편의성을 위해 객체의 이름을 재정의, 충돌 시 주석처리