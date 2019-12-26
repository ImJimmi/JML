#pragma once

//======================================================================================================================
namespace jml
{
    //==================================================================================================================
    struct ComponentLayoutSpecification
    {
        //==============================================================================================================
        enum class Flow
        {
            Column, // Child components are positioned vertically
            Row     // Child components are positioned horizontally
        };

        //==============================================================================================================
        operator bool() { return component != nullptr; }

        //==============================================================================================================
        juce::Rectangle<int> bounds;
        juce::Rectangle<int> minBounds;
        juce::Rectangle<int> maxBounds{ 99999, 99999, 99999, 99999 };

        juce::BorderSize<int> padding;
        juce::BorderSize<int> margin;

        bool autoWidth = true;
        bool autoHeight = true;
        bool autoLeft = true;
        bool autoTop = true;

        bool autoMarginLeft = false;

        Flow flow = Flow::Column;

        ComponentLayoutSpecification* parent = nullptr;
        int indexAmongSiblings = 0;
        std::vector<ComponentLayoutSpecification> children;

        juce::String tagName;
        juce::Component* component;
        juce::ValueTree properties;
    };
}   // namespace jml
