//==============================================================================
namespace jml
{
    //==========================================================================
    BlockLayoutManager::BlockLayoutManager(XmlElement* ele,
                                           Component* comp,
                                           bool performLayoutNow)
        :   element(ele),
            component(comp)
    {
        jassert(element != nullptr);
        jassert(component != nullptr);

        if (performLayoutNow)
            performLayout();
    }

    //==========================================================================
    void BlockLayoutManager::performLayout()
    {
        Rectangle<int> bounds(component->getBounds());
        Rectangle<int> minBounds(0, 0, 0, 0);
        Rectangle<int> maxBounds(9999, 9999, 9999, 9999);
        BorderSize<int> margin(0);

        auto display = element->getStringAttribute("display").toLowerCase();
        auto shouldHandleMargin = display == "block" || display.isEmpty();

        for (int i = 0; i < element->getNumAttributes(); i++)
        {
            auto name = element->getAttributeName(i).toLowerCase();
            auto value = element->getAttributeValue(i).trim();

            if (name == "margin" && shouldHandleMargin)
            {
                auto tokens = StringArray::fromTokens(value, false);

                if (tokens.size() == 1)
                    margin = BorderSize<int>(tokens[0].getIntValue());
                else if (tokens.size() == 2)
                {
                    margin.setTop(tokens[1].getIntValue());
                    margin.setRight(tokens[0].getIntValue());
                    margin.setBottom(tokens[1].getIntValue());
                    margin.setLeft(tokens[0].getIntValue());
                }
                else if (tokens.size() == 3)
                {
                    margin.setTop(tokens[0].getIntValue());
                    margin.setRight(tokens[1].getIntValue());
                    margin.setBottom(tokens[2].getIntValue());
                    margin.setLeft(tokens[1].getIntValue());
                }
                else if (tokens.size() == 4)
                {
                    margin.setTop(tokens[0].getIntValue());
                    margin.setRight(tokens[1].getIntValue());
                    margin.setBottom(tokens[2].getIntValue());
                    margin.setLeft(tokens[3].getIntValue());
                }
                else
                {
                    // Invalid number of values in margin string.
                    // Should be 1, 2, 3, or 4
                    jassertfalse;
                }
            }
            else
            {
                auto numericValue = JML::attributeStringToInt(component, name, value);

                if (name == "x")
                    bounds.setX(numericValue);
                else if (name == "y")
                    bounds.setY(numericValue);
                else if (name == "width")
                    bounds.setWidth(numericValue);
                else if (name == "height")
                    bounds.setHeight(numericValue);

                else if (name == "min-x")
                    minBounds.setX(numericValue);
                else if (name == "min-y")
                    minBounds.setY(numericValue);
                else if (name == "min-width")
                    minBounds.setWidth(numericValue);
                else if (name == "min-height")
                    minBounds.setHeight(numericValue);

                else if (name == "max-x")
                    maxBounds.setX(numericValue);
                else if (name == "max-y")
                    maxBounds.setY(numericValue);
                else if (name == "max-width")
                    maxBounds.setWidth(numericValue);
                else if (name == "max-height")
                    maxBounds.setHeight(numericValue);
            }
        }

        bounds.setX(jmax(minBounds.getX(), jmin(maxBounds.getX(), bounds.getX())));
        bounds.setY(jmax(minBounds.getY(), jmin(maxBounds.getY(), bounds.getY())));
        bounds.setWidth(jmax(minBounds.getWidth(), jmin(maxBounds.getWidth(), bounds.getWidth())));
        bounds.setHeight(jmax(minBounds.getHeight(), jmin(maxBounds.getHeight(), bounds.getHeight())));

        margin.subtractFrom(bounds);

        component->setBounds(bounds);
    }
}