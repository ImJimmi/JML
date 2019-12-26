#pragma once

//======================================================================================================================
namespace jml
{
    //==================================================================================================================
    using namespace juce;

    //==================================================================================================================
    class BlockLayout
    {
    public:
        //==============================================================================================================
        static void build(ComponentLayoutSpecification* layout);
        static void perform(ComponentLayoutSpecification* layout);

    private:
        //==============================================================================================================
        static BorderSize<int> getBorderSizeFromAttribute(const String& value,
                                                          ComponentLayoutSpecification* layout);
    };
}   // namespace jml
