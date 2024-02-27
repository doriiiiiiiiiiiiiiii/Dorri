#pragma once

class CE_SaveXML final
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

    CE_SaveXML(const std::string& path);
    ~CE_SaveXML();

    //'std::to_string()'을 사용하여 정수 또는 부동 소수점 값을 변환하세요.
    void Add(const std::vector<std::pair<std::string, std::string>>& datas);
    void AddGroup(const std::string& itemName, const std::vector<std::pair<std::string, std::string>>& datas);
};

using SaveXML = CE_SaveXML; //편의성을 위해 객체의 이름을 재정의, 충돌 시 주석처리