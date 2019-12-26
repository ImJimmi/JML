#pragma once

#include <unordered_map>

//======================================================================================================================
using namespace juce;

//======================================================================================================================
class JML
{
public:
    //==================================================================================================================
    JML(const File& file);
    JML(const String& jmlString);

    //==================================================================================================================
    void performLayout();

    //==================================================================================================================
    void setComponentForTag(const String& tag, Component* component);

private:
    //==================================================================================================================
    void performLayoutFor(jml::ComponentLayoutSpecification*, XmlElement* element);
    void buildFor(XmlElement* element, jml::ComponentLayoutSpecification* layout);

    //==================================================================================================================
    std::unordered_map<String, Component*> tagsMap;

    File jmlFile;
    std::unique_ptr<XmlElement> jmlRoot;
    std::unique_ptr<jml::ComponentLayoutSpecification> topLevelLayout;
};
