#pragma once

//======================================================================================================================
namespace jml
{
    //==================================================================================================================
    using namespace juce;

    //==================================================================================================================
    /** Converts a String consisting of a single unit to a floating point pixel value.
        
        Supported units:
            cm, mm, in,
            vw, vh, vmin, vmax, pw, ph, %
    */
    static float singleUnitStringToValue(const String& attributeValue,
                                         ComponentLayoutSpecification*,
                                         bool relativeToWidth = true);

    /** Returns the numeric value of the given attribute. */
    static float attributeToValue(const String& attributeName,
                                  const String& attributeValue,
                                  ComponentLayoutSpecification*);
}   // namespace jml
