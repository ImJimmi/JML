/*******************************************************************************
    BEGIN_JUCE_MODULE_DECLARATION

    ID:               jml
    vendor:           James Johnson
    version:          0.2.0
    name:             JUCE Markup Language
    description:      JML
    dependencies:     juce_core, juce_gui_basics

    END_JUCE_MODULE_DECLARATION
*******************************************************************************/

#pragma once
#define JML_H_INCLUDED

// JUCE includes
#include <juce_core/juce_core.h>
#include <juce_gui_basics/juce_gui_basics.h>

// STL includes
#include <unordered_map>

// JML includes
#include "src/jml_BlockLayoutManager.h"
#include "src/jml_FlexLayoutManager.h"
#include "src/jml_GridLayoutManager.h"

using namespace juce;

//==============================================================================
class JML   :   public Timer
{
public:
    //==========================================================================
    JML() {}
    JML(const File& file);

    //==========================================================================
    void setJMLFile(const File& file);
    void setJMLRoot(std::unique_ptr<XmlElement> root);

    /** If called, the JML file will be repeatedly parsed and the layout will be
        performed with the new XML tree
    */
    void watch(const int updatesPerSecond);

    //==========================================================================
    void timerCallback() override;

    //==========================================================================
    /** Performs the laying out of the Components. */
    void performLayout();

    /** Converts an attributes value (as a string) to the correct integer
        value.

        This allows for the use of relative values like "50%" instead of
        just fixed values.
     */
    static const int attributeStringToInt(Component* component,
                                          const String& attributeName,
                                          String attributeValue);

    //==========================================================================
    void setComponentForTag(const String& tag, Component* component);

private:
    //==========================================================================
    void performLayoutForElement(XmlElement* element);

    void layoutComponent(XmlElement* element);
    void performGridLayout(XmlElement* element, XmlElement* parent);

    //==========================================================================
    Component* getComponentForElement(XmlElement* element);

    //==========================================================================
    File jmlFile;
    std::unique_ptr<XmlElement> jmlRoot;
    std::unordered_map<String, Component*> tagsMap;

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
