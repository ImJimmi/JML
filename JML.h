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

    //==========================================================================
    void setJMLFile(const File& file);
    void setJMLRoot(std::unique_ptr<XmlElement> root);

    //==========================================================================
    void setComponentForTag(const String& tag, Component* component);

    //==========================================================================
    void perform();

private:
    //==========================================================================
    void performLayoutForElement(XmlElement* element);

    void layoutComponent(XmlElement* element);
    void performGridLayout(XmlElement* element, XmlElement* parent);

    //==========================================================================
    const int getAttributeValue(const String& name, const String& value,
                                Component* component);

    Component* getComponentForElement(XmlElement* element);

    //==========================================================================
    std::unique_ptr<XmlElement> jmlRoot;
    std::unordered_map<String, uintptr_t> tagsMap;

    // component maps
    struct ComponentDefinition
    {
        Component* component;
        Rectangle<int> bounds;
        Rectangle<int> minBounds;
        Rectangle<int> maxBounds;
        BorderSize<int> margin;
    };

    std::unordered_map<String, std::function<void(const String&, ComponentDefinition&)>> componentMap;

    // grid maps
    std::unordered_map<String, std::function<void(const String&, Grid&)>> gridMap;
    std::unordered_map<String, Grid::JustifyItems> gridJustifyItemsMap;
    std::unordered_map<String, Grid::AlignItems> gridAlignItemsMap;
    std::unordered_map<String, Grid::JustifyContent> gridJustifyContentMap;
    std::unordered_map<String, Grid::AlignContent> gridAlignContentMap;
    std::unordered_map<String, Grid::AutoFlow> gridAutoFlowMap;

    std::unordered_map<String, std::function<void(const String&, GridItem&)>> gridItemMap;
    std::unordered_map<String, GridItem::JustifySelf> gridItemJustifySelfMap;
    std::unordered_map<String, GridItem::AlignSelf> gridItemAlignSelfMap;

};
