#pragma once

//==============================================================================
namespace jml
{
    using namespace juce;

    //==========================================================================
    class GridLayoutManager
    {
    public:
        //======================================================================
        GridLayoutManager(std::unordered_map<String, Component*>& tags,
                          XmlElement* elementForLayout,
                          Component* componentToPerformLayoutFor,
                          bool performLayoutNow = true);

        void performLayout();

    private:
        //======================================================================
        std::unordered_map<String, Component*>& tagsMap;

        XmlElement* element = nullptr;
        Component* component = nullptr;

        // Grid maps
        std::unordered_map<String, Grid::AlignContent> alignContentMap;
        std::unordered_map<String, Grid::AlignItems> alignItemsMap;
        std::unordered_map<String, Grid::AutoFlow> autoFlowMap;
        std::unordered_map<String, Grid::JustifyContent> justifyContentMap;
        std::unordered_map<String, Grid::JustifyItems> justifyItemsMap;

        // GridItem maps
        std::unordered_map<String, GridItem::AlignSelf> alignSelfMap;
        std::unordered_map<String, GridItem::JustifySelf> justifySelfMap;
    };
}