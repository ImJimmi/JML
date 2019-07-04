#pragma once

//==============================================================================
namespace jml
{
    using namespace juce;

    //==========================================================================
    class BlockLayoutManager
    {
    public:
        //======================================================================
        BlockLayoutManager(XmlElement* elementForLayout,
                           Component* componentToPerformLayoutFor,
                           bool performLayoutNow = true);

        void performLayout();

    private:
        //======================================================================
        XmlElement* element = nullptr;
        Component* component = nullptr;

        //======================================================================
        /** Converts an attributes value (as a string) to the correct integer
            value.

            This allows for the use of relative values like "50%" instead of
            just fixed values.
         */
        const int attributeStringToInt(const String& name, String value);
    };
}