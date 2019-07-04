//==============================================================================
namespace jml
{
    //==========================================================================
    FlexLayoutManager::FlexLayoutManager(std::unordered_map<String, Component*>& tags,
                                         XmlElement* ele,
                                         Component* comp,
                                         bool performLayoutNow)
        :   tagsMap(tags),
            element(ele),
            component(comp)
    {
        jassert(element != nullptr);
        jassert(component != nullptr);

        // setup AlignContent mappings
        {
            alignContentMap["center"] =         FlexBox::AlignContent::center;
            alignContentMap["end"] =            FlexBox::AlignContent::flexEnd;
            alignContentMap["start"] =          FlexBox::AlignContent::flexStart;
            alignContentMap["space-around"] =   FlexBox::AlignContent::spaceAround;
            alignContentMap["space-between"] =  FlexBox::AlignContent::spaceBetween;
            alignContentMap["stretch"] =        FlexBox::AlignContent::stretch;
        }

        // setup AlignItems mappings
        {
            alignItemsMap["center"] =   FlexBox::AlignItems::center;
            alignItemsMap["end"] =      FlexBox::AlignItems::flexEnd;
            alignItemsMap["start"] =    FlexBox::AlignItems::flexStart;
            alignItemsMap["stretch"] =  FlexBox::AlignItems::stretch;
        }

        // setup Direction mappings
        {
            directionMap["column"] =            FlexBox::Direction::column;
            directionMap["column-reverse"] =    FlexBox::Direction::columnReverse;
            directionMap["row"] =               FlexBox::Direction::row;
            directionMap["row-reverse"] =       FlexBox::Direction::rowReverse;
        }

        // setup Direction mappings
        {
            justifyContentMap["center"] =           FlexBox::JustifyContent::center;
            justifyContentMap["end"] =              FlexBox::JustifyContent::flexEnd;
            justifyContentMap["start"] =            FlexBox::JustifyContent::flexStart;
            justifyContentMap["space-around"] =     FlexBox::JustifyContent::spaceAround;
            justifyContentMap["space-between"] =    FlexBox::JustifyContent::spaceBetween;
        }

        // setup Direction mappings
        {
            wrapMap["nowrap"] = FlexBox::Wrap::noWrap;
            wrapMap["wrap"] = FlexBox::Wrap::wrap;
            wrapMap["wrap-reverse"] = FlexBox::Wrap::wrapReverse;
        }

        // setup AlignSelf mappings
        {
            alignSelfMap["auto"] =      FlexItem::AlignSelf::autoAlign;
            alignSelfMap["center"] =    FlexItem::AlignSelf::center;
            alignSelfMap["end"] =       FlexItem::AlignSelf::flexEnd;
            alignSelfMap["start"] =     FlexItem::AlignSelf::flexStart;
            alignSelfMap["stretch"] =   FlexItem::AlignSelf::stretch;
        }

        if (performLayoutNow)
            performLayout();
    }

    //==========================================================================
    void FlexLayoutManager::performLayout()
    {
        FlexBox flex;

        for (int i = 0; i < element->getNumAttributes(); i++)
        {
            auto name = element->getAttributeName(i).toLowerCase();
            auto value = element->getAttributeValue(i).trim();

            if (name == "align-content")
            {
                flex.alignContent = alignContentMap[value];
            }
            else if (name == "align-items")
            {
                flex.alignItems = alignItemsMap[value];
            }
            else if (name == "direction")
            {
                flex.flexDirection = directionMap[value];
            }
            else if (name == "justify-content")
            {
                flex.justifyContent = justifyContentMap[value];
            }
            else if (name == "wrap")
            {
                flex.flexWrap = wrapMap[value];
            }
        }

        for (int i = 0; i < element->getNumChildElements(); i++)
        {
            auto childElement = element->getChildElement(i);
            auto childComponent = reinterpret_cast<Component*>(tagsMap[childElement->getTagName()]);

            FlexItem item(*childComponent);

            for (int j = 0; j < element->getNumAttributes(); j++)
            {
                auto name = childElement->getAttributeName(j).toLowerCase();
                auto value = childElement->getAttributeValue(j).trim();

                if (name == "align-self")
                {
                    item.alignSelf = alignSelfMap[value];
                }
                else if (name == "basis")
                {
                    item.flexBasis = value.getFloatValue();
                }
                else if (name == "grow")
                {
                    item.flexGrow = value.getFloatValue();
                }
                else if (name == "shrink")
                {
                    item.flexShrink = value.getFloatValue();
                }
                else if (name == "height")
                {
                    item.height = value.getFloatValue();
                }
                else if (name == "margin")
                {
                    auto tokens = StringArray::fromTokens(value, false);

                    if (tokens.size() == 1)
                    {
                        item.margin.top = tokens[0].getFloatValue();
                        item.margin.right = tokens[0].getFloatValue();
                        item.margin.bottom = tokens[0].getFloatValue();
                        item.margin.left = tokens[0].getFloatValue();
                    }
                    else if (tokens.size() == 2)
                    {
                        item.margin.top = tokens[0].getFloatValue();
                        item.margin.right = tokens[1].getFloatValue();
                        item.margin.bottom = tokens[0].getFloatValue();
                        item.margin.left = tokens[1].getFloatValue();
                    }
                    else if (tokens.size() == 3)
                    {
                        item.margin.top = tokens[0].getFloatValue();
                        item.margin.right = tokens[1].getFloatValue();
                        item.margin.bottom = tokens[2].getFloatValue();
                        item.margin.left = tokens[1].getFloatValue();
                    }
                    else if (tokens.size() == 4)
                    {
                        item.margin.top = tokens[0].getFloatValue();
                        item.margin.right = tokens[1].getFloatValue();
                        item.margin.bottom = tokens[2].getFloatValue();
                        item.margin.left = tokens[3].getFloatValue();
                    }
                    else
                    {
                        jassertfalse;
                    }
                }
                else if (name == "max-height")
                {
                    item.maxHeight = value.getFloatValue();
                }
                else if (name == "max-width")
                {
                    item.maxWidth = value.getFloatValue();
                }
                else if (name == "min-height")
                {
                    item.minHeight = value.getFloatValue();
                }
                else if (name == "min-width")
                {
                    item.minWidth = value.getFloatValue();
                }
                else if (name == "order")
                {
                    item.order = value.getIntValue();
                }
                else if (name == "width")
                {
                    item.width = value.getFloatValue();
                }
            }

            flex.items.add(item);
        }

        flex.performLayout(component->getBounds());
    }
}
