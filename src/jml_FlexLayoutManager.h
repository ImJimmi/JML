#pragma once

//==============================================================================
namespace jml
{
    using namespace juce;

    //==========================================================================
    class FlexLayoutManager
    {
    public:
        //======================================================================
        FlexLayoutManager(std::unordered_map<String, Component*>& tags,
                          XmlElement* elementForLayout,
                          Component* componentToPerformLayoutFor,
                          bool performLayoutNow = true);

        void performLayout();

    private:
        //======================================================================
        std::unordered_map<String, Component*>& tagsMap;

        XmlElement* element = nullptr;
        Component* component = nullptr;

        // FlexBox maps
        std::unordered_map<String, FlexBox::AlignContent> alignContentMap;
        std::unordered_map<String, FlexBox::AlignItems> alignItemsMap;
        std::unordered_map<String, FlexBox::Direction> directionMap;
        std::unordered_map<String, FlexBox::JustifyContent> justifyContentMap;
        std::unordered_map<String, FlexBox::Wrap> wrapMap;

        // FlexItem maps
        std::unordered_map<String, FlexItem::AlignSelf> alignSelfMap;
    };
}