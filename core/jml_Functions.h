#pragma once

//======================================================================================================================
namespace jml
{
    //==================================================================================================================
    using namespace juce;

    //==================================================================================================================
    /** Supported units:
     *      cm, mm, in,
     *      vw, vh, vmin, vmax, %
    */
    static int getPixelValueFromAttribute(const String& attributeValue,
                                          ComponentLayoutSpecification*,
                                          bool relativeToWidth = true);
}   // namespace jml
