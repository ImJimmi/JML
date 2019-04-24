/*******************************************************************************
    BEGIN_JUCE_MODULE_DECLARATION

    ID:               jml
    vendor:           James Johnson
    version:          1.0.0
    name:             JUCE Markup Language
    description:      JML
    dependencies:     juce_core, juce_gui_basics

    END_JUCE_MODULE_DECLARATION
*******************************************************************************/

#pragma once
#define JML_H_INCLUDED

#include <juce_core/juce_core.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include <unordered_map>

using namespace juce;

//==============================================================================
class JML
{
public:
    //==========================================================================
    JML();
    ~JML();

    //==========================================================================
    void setJMLFile(const File& file);

    //==========================================================================
    void setComponentForTag(const String& tag, Component* component);

    //==========================================================================
    void perform();

    //==========================================================================
    JUCE_DECLARE_SINGLETON(JML, true)

private:
    //==========================================================================
    void performLayout(XmlElement* element);

    void performGridLayout(XmlElement* element);
    void layoutComponent(XmlElement* element);

    //==========================================================================
    const int getAttributeValue(const String& name, const String& value,
                                Component* component);

    //==========================================================================
    std::unique_ptr<XmlElement> jmlRoot;
    NamedValueSet tagList;

    std::unordered_map<String, std::function<void(const int, Rectangle<int>&)>> boundsMaps;
    std::unordered_map<String, std::function<void(const int, BorderSize<int>&)>> marginMaps;
    std::unordered_map<String, std::function<void(const int, Grid&)>> gridMaps;
};
