//==============================================================================
namespace jml
{
    //==========================================================================
    GridLayoutManager::GridLayoutManager(std::unordered_map<String, Component*>& tags,
                                         XmlElement* ele,
                                         Component* comp,
                                         bool performLayoutNow)
        :   tagsMap(tags),
            element(ele),
            component(comp)
    {
        jassert(element != nullptr);
        jassert(component != nullptr);

        // setup the AlignContent mappings
        {
            alignContentMap["center"] =           Grid::AlignContent::center;
            alignContentMap["end"] =              Grid::AlignContent::end;
            alignContentMap["space-around"] =     Grid::AlignContent::spaceAround;
            alignContentMap["space-between"] =    Grid::AlignContent::spaceBetween;
            alignContentMap["space-evenly"] =     Grid::AlignContent::spaceEvenly;
            alignContentMap["start"] =            Grid::AlignContent::start;
            alignContentMap["stretch"] =          Grid::AlignContent::stretch;
        }

        // setup the AlignItems mappings
        {
            alignItemsMap["center"] =     Grid::AlignItems::center;
            alignItemsMap["end"] =        Grid::AlignItems::end;
            alignItemsMap["start"] =      Grid::AlignItems::start;
            alignItemsMap["stretch"] =    Grid::AlignItems::stretch;
        }

        // setup the AutoFlow mappings
        {
            autoFlowMap["column"] =       Grid::AutoFlow::column;
            autoFlowMap["column-dense"] = Grid::AutoFlow::columnDense;
            autoFlowMap["row"] =          Grid::AutoFlow::row;
            autoFlowMap["row-dense"] =    Grid::AutoFlow::rowDense;
        }

        // setup the JustifyContent mappings
        {
            justifyContentMap["center"] =         Grid::JustifyContent::center;
            justifyContentMap["end"] =            Grid::JustifyContent::end;
            justifyContentMap["space-around"] =   Grid::JustifyContent::spaceAround;
            justifyContentMap["space-between"] =  Grid::JustifyContent::spaceBetween;
            justifyContentMap["space-evenly"] =   Grid::JustifyContent::spaceEvenly;
            justifyContentMap["start"] =          Grid::JustifyContent::start;
            justifyContentMap["stretch"] =        Grid::JustifyContent::stretch;
        }

        // setup the JustifyItems mappings
        {
            justifyItemsMap["center"] =   Grid::JustifyItems::center;
            justifyItemsMap["end"] =      Grid::JustifyItems::end;
            justifyItemsMap["start"] =    Grid::JustifyItems::start;
            justifyItemsMap["stretch"] =  Grid::JustifyItems::stretch;
        }

        // setup the AlignSelf mappings
        {
            alignSelfMap["auto"] =      GridItem::AlignSelf::autoValue;
            alignSelfMap["center"] =    GridItem::AlignSelf::center;
            alignSelfMap["end"] =       GridItem::AlignSelf::end;
            alignSelfMap["start"] =     GridItem::AlignSelf::start;
            alignSelfMap["stretch"] =   GridItem::AlignSelf::stretch;
        }

        // setup the JustifySelf mappings
        {
            justifySelfMap["auto"] =    GridItem::JustifySelf::autoValue;
            justifySelfMap["center"] =  GridItem::JustifySelf::center;
            justifySelfMap["end"] =     GridItem::JustifySelf::end;
            justifySelfMap["start"] =   GridItem::JustifySelf::start;
            justifySelfMap["stretch"] = GridItem::JustifySelf::stretch;
        }

        if (performLayoutNow)
            performLayout();
    }

    //==========================================================================
    void GridLayoutManager::performLayout()
    {
        // setup the gGrid
        Grid grid;
        StringArray columnTokens;
        StringArray rowTokens;
        BorderSize<int> margin;

        for (int i = 0; i < element->getNumAttributes(); i++)
        {
            auto name = element->getAttributeName(i).toLowerCase();
            auto value = element->getAttributeValue(i).trim();

            if (name == "align-content")
            {
                grid.alignContent = alignContentMap[value];
            }
            else if (name == "align-items")
            {
                grid.alignItems = alignItemsMap[value];
            }
            else if (name == "auto-columns")
            {
                if (value.endsWith("fr"))
                {
                    auto fraction = value.upToFirstOccurrenceOf("fr", false, true).getIntValue();
                    grid.autoColumns = Grid::TrackInfo(Grid::Fr(fraction));
                }
                else
                {
                    auto fraction = value.getIntValue();
                    grid.autoColumns = Grid::TrackInfo(Grid::Px(fraction));
                }
            }
            else if (name == "auto-flow")
            {
                grid.autoFlow = autoFlowMap[value];
            }
            else if (name == "auto-rows")
            {
                if (value.endsWith("fr"))
                {
                    auto fraction = value.upToFirstOccurrenceOf("fr", false, true).getIntValue();
                    grid.autoRows = Grid::TrackInfo(Grid::Fr(fraction));
                }
                else
                {
                    auto fraction = value.getIntValue();
                    grid.autoRows = Grid::TrackInfo(Grid::Px(fraction));
                }
            }
            else if (name == "column-gap")
            {
                grid.columnGap = Grid::Px(value.getIntValue());
            }
            else if (name == "columns")
            {
                auto numColumns = value.getIntValue();

                columnTokens.clear();

                for (int i = 0; i < numColumns; i++)
                    columnTokens.add("1fr");
            }
            else if (name == "gap")
            {
                auto gap = JML::attributeStringToInt(component, name, value);
                grid.setGap(Grid::Px(gap));
            }
            else if (name == "justify-content")
            {
                grid.justifyContent = justifyContentMap[value];
            }
            else if (name == "justify-items")
            {
                grid.justifyItems = justifyItemsMap[value];
            }
            else if (name == "margin")
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
            else if (name == "row-gap")
            {
                grid.rowGap = Grid::Px(value.getIntValue());
            }
            else if (name == "rows")
            {
                auto numRows = value.getIntValue();

                rowTokens.clear();

                for (int i = 0; i < numRows; i++)
                    rowTokens.add("1fr");
            }
            else if (name == "template-areas")
            {
                auto tokens = StringArray::fromTokens(value, " ", "'");

                for (const auto& token : tokens)
                    grid.templateAreas.add(token.unquoted());
            }
            else if (name == "template-columns")
            {
                columnTokens = StringArray::fromTokens(value, false);
            }
            else if (name == "template-rows")
            {
                rowTokens = StringArray::fromTokens(value, false);
            }
        }

        for (const auto& token : columnTokens)
        {
            if (token.endsWith("fr"))
            {
                auto fraction = token.upToFirstOccurrenceOf("fr", false, true).getIntValue();
                grid.templateColumns.add(Grid::Fr(fraction));
            }
            else
            {
                auto fraction = token.getIntValue();
                grid.templateColumns.add(Grid::Px(fraction));
            }
        }

        for (const auto& token : rowTokens)
        {
            if (token.endsWith("fr"))
            {
                auto fraction = token.upToFirstOccurrenceOf("fr", false, true).getIntValue();
                grid.templateRows.add(Grid::Fr(fraction));
            }
            else
            {
                auto fraction = token.getIntValue();
                grid.templateRows.add(Grid::Px(fraction));
            }
        }

        // setup the GridItems
        for (int i = 0; i < element->getNumChildElements(); i++)
        {
            auto childElement = element->getChildElement(i);
            auto childComponent = reinterpret_cast<Component*>(tagsMap[childElement->getTagName()]);

            GridItem item(childComponent);

            for (int j = 0; j < childElement->getNumAttributes(); j++)
            {
                auto name = childElement->getAttributeName(j).toLowerCase();
                auto value = childElement->getAttributeValue(j).trim();

                if (name == "align-self")
                {
                    item.alignSelf = alignSelfMap[value];
                }
                else if (name == "area")
                {
                    item.area = value;
                }
                else if (name == "column")
                {
                    auto tokens = StringArray::fromTokens(value, false);

                    GridItem::StartAndEndProperty startAndEnd;

                    if (tokens.size() == 1)
                    {
                        startAndEnd.start = tokens[0].getIntValue();
                        startAndEnd.end = tokens[0].getIntValue();
                    }
                    else if (tokens.size() == 2)
                    {
                        startAndEnd.start = tokens[0].getIntValue();
                        startAndEnd.end = tokens[1].getIntValue();
                    }

                    item.column = startAndEnd;
                }
                else if (name == "height")
                {
                    item.height = value.getFloatValue();
                }
                else if (name == "justify-self")
                {
                    item.justifySelf = justifySelfMap[value];
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
                else if (name == "row")
                {
                    auto tokens = StringArray::fromTokens(value, false);

                    GridItem::StartAndEndProperty startAndEnd;

                    if (tokens.size() == 1)
                    {
                        startAndEnd.start = tokens[0].getIntValue();
                        startAndEnd.end = tokens[0].getIntValue();
                    }
                    else if (tokens.size() == 2)
                    {
                        startAndEnd.start = tokens[0].getIntValue();
                        startAndEnd.end = tokens[1].getIntValue();
                    }

                    item.row = startAndEnd;
                }
                else if (name == "width")
                {
                    item.width = value.getFloatValue();
                }
            }

            grid.items.add(item);
        }

        grid.performLayout(margin.subtractedFrom(component->getBounds()));
    }
}
