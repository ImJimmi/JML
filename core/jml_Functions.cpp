#include "jml_Functions.h"

//======================================================================================================================
namespace jml
{
    //==================================================================================================================
    float singleUnitStringToValue(const String& value,
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
                return container.getWidth() * perc;
            else
                return container.getHeight() * perc;
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
                return topLevelComponent->getWidth() * perc;
            else if (value.endsWith("vh"))
                return topLevelComponent->getHeight() * perc;
            else if (value.endsWith("vmin"))
            {
                auto min = std::min(topLevelComponent->getWidth(), topLevelComponent->getHeight());
                return min * perc;
            }
            else // if (name.endsWith("vmax"))
            {
                auto max = std::max(topLevelComponent->getWidth(), topLevelComponent->getHeight());
                return max * perc;
            }
        }
        else if (value.endsWith("pw") || value.endsWith("ph"))
        {
            if (auto parentLayout = layout->parent)
            {
                auto parentBounds = parentLayout->component->getBounds();

                if (parentLayout->parent == nullptr)
                    parentLayout->margin.subtractFrom(parentBounds);

                parentLayout->padding.subtractFrom(parentBounds);

                auto perc = value.getFloatValue() / 100.f;

                if (value.endsWith("pw"))
                    return parentBounds.getWidth() * perc;
                else
                    return parentBounds.getHeight() * perc;
            }
            else
            {
                /** You can't use pw or ph on a top-level component! */
                jassertfalse;
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

            return valueInInches * (float)logicalPixelsPerInch;
        }
        else if (value == "auto")
        {
            return 0.f;
        }
        else
        {
            if (value.contains("."))
                return value.getFloatValue();
            else
                return value.getIntValue();
        }
    }

    float attributeToValue(const String& name,
                           const String& v,
                           ComponentLayoutSpecification* layout)
    {
        auto value = v;

        // handle parenthesis
        while (value.contains(")"))
        {
            auto substring = value.fromLastOccurrenceOf("(", false, true).upToFirstOccurrenceOf(")", false, true);
            auto temp = attributeToValue(name, substring, layout);
            value = value.replace("(" + substring + ")", String(temp));
        }

        // ensure all operators have whitesapace around them
        value.replace("^", " ^ ");
        value.replace("/", " / ");
        value.replace("*", " * ");
        value.replace("+", " + ");
        value.replace("-", " - ");

        auto tokens = StringArray::fromTokens(value, false);

        for (String op : { "^", "/", "*", "+", "-" })
        {
            while (tokens.contains(op))
            {
                auto i = tokens.indexOf(op);

                auto relativeToWidth = name.contains("width") || name.contains("x");

                auto left = singleUnitStringToValue(tokens[i - 1], layout, relativeToWidth);
                auto right = singleUnitStringToValue(tokens[i + 1], layout, relativeToWidth);

                auto newValue = 0.f;

                if (op == "^")
                    newValue = std::pow(left, right);
                else if (op == "/")
                    newValue = left / right;
                else if (op == "*")
                    newValue = left * right;
                else if (op == "+")
                    newValue = left + right;
                else if (op == "-")
                    newValue = left - right;

                tokens.removeRange(i - 1, 3);
                tokens.insert(i - 1, String(newValue));
            }
        }

#if JUCE_DEBUG
        if (tokens.size() != 1)
        {
            for (auto& token : tokens)
                DBG(token);
        }
#endif
        jassert(tokens.size() == 1);
        return tokens[0].getFloatValue();
    }
}
