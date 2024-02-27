#include "pch.h"
#include "CE_SaveXML.h"

CE_SaveXML::CE_SaveXML(const std::string& path)
{
    _path = path;
    CE_SaveXML::Init();
}

CE_SaveXML::~CE_SaveXML()
{

}

void CE_SaveXML::Init()
{
    _node = _doc.NewElement(_path.c_str());
    assert(_node);

    _element = _doc.NewElement(_path.c_str());
    assert(_element);

    _doc.InsertFirstChild(_node);
}

void CE_SaveXML::Add(const std::vector<std::pair<std::string, std::string>>& datas)
{
    for (const auto& value : datas)
    {
        _element = _doc.NewElement(value.first.c_str());
        _element->SetText(value.second.c_str());
        _node->InsertEndChild(_element->DeepClone(&_doc));
    }

    tinyxml2::XMLError err = _doc.SaveFile((_path + ".xml").c_str());
}

void CE_SaveXML::AddGroup(const std::string& itemName, const std::vector<std::pair<std::string, std::string>>& datas)
{
    _element = _doc.NewElement(itemName.c_str());

    for (const auto& value : datas)
    {
        _element->SetAttribute(value.first.c_str(), value.second.c_str());
    }

    _node->InsertEndChild(_element->DeepClone(&_doc));

    tinyxml2::XMLError err = _doc.SaveFile((_path + ".xml").c_str());
}