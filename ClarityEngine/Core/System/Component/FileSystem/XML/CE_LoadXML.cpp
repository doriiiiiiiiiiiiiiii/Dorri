#include "pch.h"
#include "CE_LoadXML.h"

CE_LoadXML::CE_LoadXML(const std::string& path)
{
    _path = path;

    CE_LoadXML::Init();
}

CE_LoadXML::~CE_LoadXML()
{

}

void CE_LoadXML::Init()
{
    tinyxml2::XMLError err = _doc.LoadFile((_path + ".xml").c_str());

    _node = _doc.FirstChildElement(_path.c_str());
}

std::string CE_LoadXML::GetString(const std::string& key)
{
    LPCSTR tmpString = nullptr;

    _element = _node->FirstChildElement(key.c_str());
    tmpString = _element->GetText();

    return std::string(tmpString);
}

INT64 CE_LoadXML::GetINT64(const std::string& key)
{
    INT64 tmpInt64 = 0;

    _element = _node->FirstChildElement(key.c_str());
    _element->QueryInt64Text(&tmpInt64);

    return tmpInt64;
}

DOUBLE CE_LoadXML::GetDOUBLE(const std::string& key)
{
    DOUBLE tmpDouble = 0.0;

    _element = _node->FirstChildElement(key.c_str());
    _element->QueryDoubleText(&tmpDouble);

    return tmpDouble;
}

std::string CE_LoadXML::GetGroupString(const std::string& element, const std::string& key)
{
    LPCSTR tmpGroupString = nullptr;

    _element = _node->FirstChildElement(element.c_str());
    tmpGroupString = _element->Attribute(key.c_str());

    return std::string(tmpGroupString);
}

INT64 CE_LoadXML::GetGroupINT64(const std::string& element, const std::string& key)
{
    INT64 tmpGroupInt64 = 0;

    _element = _node->FirstChildElement(element.c_str());
    _element->Int64Attribute(key.c_str());

    return tmpGroupInt64;
}

DOUBLE CE_LoadXML::GetGroupDOUBLE(const std::string& element, const std::string& key)
{
    DOUBLE tmpGroupDouble = 0.0;

    _element = _node->FirstChildElement(element.c_str());
    _element->DoubleAttribute(key.c_str());

    return tmpGroupDouble;
}