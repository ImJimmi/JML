#include "jml_Functions.h"

//======================================================================================================================
namespace jml
{
    //==================================================================================================================
    int getPixelValueFromAttribute(const String& value,
                                   ComponentLayoutSpecification* layout,
                                   bool relativeToWidth)
    {
        if (value.endsWith("%"))
        {
            /** You can't use relative values on a top-level Component! */
            jassert(layout->parent);

            auto container = layout->parent->padding.subtractedFrom(layout->parent->component->getBounds());

            // get the percentage value (0 - 1)
            auto perc = value.getFloatValue() / 100.f;

            // return the relative value
            if (relativeToWidth)
                return (int)std::round(container.getWidth() * perc);
            else
                return (int)std::round(container.getHeight() * perc);
        }
        else if (value.endsWith("vw") || value.endsWith("vh") || value.endsWith("vmin") || value.endsWith("vmax"))
        {
            // get the top level component
            auto topLevelComponent = layout->component->getTopLevelComponent();
            
            /** You can't use relative values on a top-level Component! */
            jassert(topLevelComponent != layout->component);

            // get the percentage value (0 - 1)
            auto perc = value.getFloatValue() / 100.f;

            // return the relative value
            if (value.endsWith("vw"))
                return (int)std::round(topLevelComponent->getWidth() * perc);
            else if (value.endsWith("vh"))
                return (int)std::round(topLevelComponent->getHeight() * perc);
            else if (value.endsWith("vmin"))
            {
                auto min = std::min(topLevelComponent->getWidth(), topLevelComponent->getHeight());
                return (int)std::round(min * perc);
            }
            else // if (name.endsWith("vmax"))
            {
                auto max = std::max(topLevelComponent->getWidth(), topLevelComponent->getHeight());
                return (int)std::round(max * perc);
            }
        }
        else if (value.endsWith("in") || value.endsWith("cm") || value.endsWith("mm"))
        {
            // get the dpi value for the main display
            auto mainDisplay = Desktop::getInstance().getDisplays().getMainDisplay();
            auto logicalPixelsPerInch = mainDisplay.dpi / mainDisplay.scale;

            auto valueInInches = 0.f;

            if (value.endsWith("in"))
                valueInInches = value.getFloatValue();
            else if (value.endsWith("cm"))
                valueInInches = value.getFloatValue() * 2.54f;
            else // if (name.endswith("mm"))
                valueInInches = value.getFloatValue() * 25.4f;

            return (int)std::round(valueInInches * logicalPixelsPerInch);
        }
        else if (value == "auto")
        {
            return 0;
        }
        else
        {
            if (value.contains("."))
                return (int)std::round(value.getFloatValue());
            else
                return value.getIntValue();
        }
        
    }
}
