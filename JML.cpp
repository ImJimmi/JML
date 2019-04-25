#include "JML.h"

//==============================================================================
JML::JML()
{
    // components
    componentMap["x"] = [this](const String& value, ComponentDefinition& def) {
        def.bounds.setX(getAttributeValue("x", value, def.component));
    };
    componentMap["y"] = [this](const String& value, ComponentDefinition& def) {
        def.bounds.setY(getAttributeValue("y", value, def.component));
    };
    componentMap["width"] = [this](const String& value, ComponentDefinition& def) {
        def.bounds.setWidth(getAttributeValue("width", value, def.component));
    };
    componentMap["height"] = [this](const String& value, ComponentDefinition& def) {
        def.bounds.setHeight(getAttributeValue("height", value, def.component));
    };
    componentMap["min-x"] = [this](const String& value, ComponentDefinition& def) {
        def.minBounds.setX(getAttributeValue("min-x", value, def.component));
    };
    componentMap["min-y"] = [this](const String& value, ComponentDefinition& def) {
        def.minBounds.setY(getAttributeValue("min-y", value, def.component));
    };
    componentMap["min-width"] = [this](const String& value, ComponentDefinition& def) {
        def.minBounds.setWidth(getAttributeValue("min-width", value, def.component));
    };
    componentMap["min-height"] = [this](const String& value, ComponentDefinition& def) {
        def.minBounds.setHeight(getAttributeValue("min-height", value, def.component));
    };
    componentMap["max-x"] = [this](const String& value, ComponentDefinition& def) {
        def.maxBounds.setX(getAttributeValue("max-x", value, def.component));
    };
    componentMap["max-y"] = [this](const String& value, ComponentDefinition& def) {
        def.maxBounds.setY(getAttributeValue("max-y", value, def.component));
    };
    componentMap["max-width"] = [this](const String& value, ComponentDefinition& def) {
        def.maxBounds.setWidth(getAttributeValue("max-width", value, def.component));
    };
    componentMap["max-height"] = [this](const String& value, ComponentDefinition& def) {
        def.maxBounds.setHeight(getAttributeValue("max-height", value, def.component));
    };
    componentMap["margin"] = [](const String& value, ComponentDefinition& def) {
        auto args = StringArray::fromTokens(value, true);

        if (args.size() == 1)
            def.margin = BorderSize<int>(args[0].getIntValue());
        else if (args.size() == 2)
            def.margin = BorderSize<int>(args[1].getIntValue(), args[0].getIntValue(),
                                         args[1].getIntValue(), args[0].getIntValue());
        else if (args.size() == 4)
            def.margin = BorderSize<int>(args[0].getIntValue(), args[1].getIntValue(),
                                         args[2].getIntValue(), args[3].getIntValue());
    };

    // grid
    // justify items
    gridJustifyItemsMap["start"] = Grid::JustifyItems::start;
    gridJustifyItemsMap["end"] = Grid::JustifyItems::end;
    gridJustifyItemsMap["center"] = Grid::JustifyItems::center;
    gridJustifyItemsMap["stretch"] = Grid::JustifyItems::stretch;

    // align items
    gridAlignItemsMap["start"] = Grid::AlignItems::start;
    gridAlignItemsMap["end"] = Grid::AlignItems::end;
    gridAlignItemsMap["center"] = Grid::AlignItems::center;
    gridAlignItemsMap["stretch"] = Grid::AlignItems::stretch;

    // justify content
    gridJustifyContentMap["start"] = Grid::JustifyContent::start;
    gridJustifyContentMap["end"] = Grid::JustifyContent::end;
    gridJustifyContentMap["center"] = Grid::JustifyContent::center;
    gridJustifyContentMap["stretch"] = Grid::JustifyContent::stretch;
    gridJustifyContentMap["spaceAround"] = Grid::JustifyContent::spaceAround;
    gridJustifyContentMap["spaceBetween"] = Grid::JustifyContent::spaceBetween;
    gridJustifyContentMap["spaceEvenly"] = Grid::JustifyContent::spaceEvenly;

    // align content
    gridAlignContentMap["start"] = Grid::AlignContent::start;
    gridAlignContentMap["end"] = Grid::AlignContent::end;
    gridAlignContentMap["center"] = Grid::AlignContent::center;
    gridAlignContentMap["stretch"] = Grid::AlignContent::stretch;
    gridAlignContentMap["spaceAround"] = Grid::AlignContent::spaceAround;
    gridAlignContentMap["spaceBetween"] = Grid::AlignContent::spaceBetween;
    gridAlignContentMap["spaceEvenly"] = Grid::AlignContent::spaceEvenly;

    // auto flow
    gridAutoFlowMap["row"] = Grid::AutoFlow::row;
    gridAutoFlowMap["column"] = Grid::AutoFlow::column;
    gridAutoFlowMap["row-dense"] = Grid::AutoFlow::rowDense;
    gridAutoFlowMap["column-dense"] = Grid::AutoFlow::columnDense;

    // grid attributes
    gridMap["gap"] = [](const String & value, Grid & grid) {
        grid.setGap(Grid::Px(value.getIntValue()));
    };
    gridMap["justify-items"] = [&](const String& value, Grid& grid) {
        auto result = gridJustifyItemsMap.find(value);

        if (result != gridJustifyItemsMap.end())
            grid.justifyItems = result->second;
    };
    gridMap["align-items"] = [&](const String& value, Grid& grid) {
        auto result = gridAlignItemsMap.find(value);

        if (result != gridAlignItemsMap.end())
            grid.alignItems = result->second;
    };
    gridMap["justify-content"] = [&](const String& value, Grid& grid) {
        auto result = gridJustifyContentMap.find(value);

        if (result != gridJustifyContentMap.end())
            grid.justifyContent = result->second;
    };
    gridMap["align-content"] = [&](const String& value, Grid& grid) {
        auto result = gridAlignContentMap.find(value);

        if (result != gridAlignContentMap.end())
            grid.alignContent = result->second;
    };
    gridMap["auto-flow"] = [&](const String& value, Grid& grid) {
        auto result = gridAutoFlowMap.find(value);

        if (result != gridAutoFlowMap.end())
            grid.autoFlow = result->second;
    };
    gridMap["columns"] = [](const String& value, Grid& grid) {
        grid.templateColumns.resize(value.getIntValue());
        grid.templateColumns.fill(Grid::TrackInfo(1_fr));
    };
    gridMap["rows"] = [](const String& value, Grid& grid) {
        grid.templateRows.resize(value.getIntValue());
        grid.templateRows.fill(Grid::TrackInfo(1_fr));
    };
    gridMap["column-gap"] = [](const String& value, Grid& grid) {
        grid.columnGap = Grid::Px(value.getIntValue());
    };
    gridMap["row-gap"] = [](const String& value, Grid& grid) {
        grid.rowGap = Grid::Px(value.getIntValue());
    };

    // grid items
    // justify self
    gridItemJustifySelfMap["start"] = GridItem::JustifySelf::start;
    gridItemJustifySelfMap["end"] = GridItem::JustifySelf::end;
    gridItemJustifySelfMap["center"] = GridItem::JustifySelf::center;
    gridItemJustifySelfMap["stretch"] = GridItem::JustifySelf::stretch;
    gridItemJustifySelfMap["auto"] = GridItem::JustifySelf::autoValue;

    // align self
    gridItemAlignSelfMap["start"] = GridItem::AlignSelf::start;
    gridItemAlignSelfMap["end"] = GridItem::AlignSelf::end;
    gridItemAlignSelfMap["center"] = GridItem::AlignSelf::center;
    gridItemAlignSelfMap["stretch"] = GridItem::AlignSelf::stretch;
    gridItemAlignSelfMap["auto"] = GridItem::AlignSelf::autoValue;

    gridItemMap["area"] = [](const String& value, GridItem& item) {
        auto args = StringArray::fromTokens(value, true);

        if (args.size() == 1)
            item.setArea(value);
        else if (args.size() == 2)
            item.setArea(args[0].getIntValue(), args[1].getIntValue());
        else if (args.size() == 4)
            item.setArea(args[0].getIntValue(), args[1].getIntValue(),
                         args[2].getIntValue(), args[3].getIntValue());
    };
    gridItemMap["order"] = [](const String& value, GridItem& item) {
        item.order = value.getIntValue();
    };
    gridItemMap["justify-self"] = [&](const String& value, GridItem& item) {
        auto result = gridItemJustifySelfMap.find(value);

        if (result != gridItemJustifySelfMap.end())
            item.justifySelf = result->second;
    };
    gridItemMap["align-self"] = [&](const String& value, GridItem& item) {
        auto result = gridItemAlignSelfMap.find(value);

        if (result != gridItemAlignSelfMap.end())
            item.alignSelf = result->second;
    };
    gridItemMap["column"] = [](const String& value, GridItem& item) {
        auto args = StringArray::fromTokens(value, true);

        if (args.size() == 1)
            item.column = { args[0].getIntValue(), args[0].getIntValue() };
        else if (args.size() == 2)
            item.column = { args[0].getIntValue(), args[1].getIntValue() };
    };
    gridItemMap["row"] = [](const String& value, GridItem& item) {
        auto args = StringArray::fromTokens(value, true);

        if (args.size() == 1)
            item.row = { args[0].getIntValue(), args[0].getIntValue() };
        else if (args.size() == 2)
            item.row = { args[0].getIntValue(), args[1].getIntValue() };
    };
    gridItemMap["width"] = [](const String& value, GridItem& item) {
        item.width = value.getFloatValue();
    };
    gridItemMap["min-width"] = [](const String& value, GridItem& item) {
        item.minWidth = value.getFloatValue();
    };
    gridItemMap["max-width"] = [](const String & value, GridItem & item) {
        item.maxWidth = value.getFloatValue();
    };
    gridItemMap["height"] = [](const String& value, GridItem& item) {
        item.height = value.getFloatValue();
    };
    gridItemMap["min-height"] = [](const String& value, GridItem& item) {
        item.minHeight = value.getFloatValue();
    };
    gridItemMap["max-height"] = [](const String& value, GridItem& item) {
        item.maxHeight = value.getFloatValue();
    };
    gridItemMap["margin"] = [](const String& value, GridItem& item) {
        auto args = StringArray::fromTokens(value, true);

        if (args.size() == 1)
            item.margin = { args[0].getFloatValue() };
        else if (args.size() == 2)
            item.margin = { args[1].getFloatValue(), args[0].getFloatValue(),
                            args[1].getFloatValue(), args[0].getFloatValue() };
        else if (args.size() == 4)
            item.margin = { args[0].getFloatValue(), args[1].getFloatValue(),
                            args[2].getFloatValue(), args[3].getFloatValue() };
    };
    
}

//==============================================================================
void JML::setJMLFile(const File& file)
{
    jassert(file.existsAsFile());

    jmlRoot = parseXML(file);
    
    jassert(jmlRoot->getTagName().equalsIgnoreCase("jml"));
}

void JML::setJMLRoot(std::unique_ptr<XmlElement> root)
{
    jassert(root);

    jmlRoot = std::move(root);
}

//==============================================================================
void JML::setComponentForTag(const String& tag, Component* component)
{
    tagsMap[tag] = reinterpret_cast<uintptr_t>(component);
}

//==============================================================================
void JML::perform()
{
    performLayoutForElement(jmlRoot.get());
}

//==============================================================================
void JML::performLayoutForElement(XmlElement* element)
{
    for (int i = 0; i < element->getNumChildElements(); i++)
    {
        auto child = element->getChildElement(i);

        if (child->getTagName() == "grid")
            performGridLayout(child, element);
        else
            layoutComponent(child);

        if (child->getNumChildElements())
            performLayoutForElement(child);
    }
}

void JML::layoutComponent(XmlElement* element)
{
    ComponentDefinition def;
    def.component = getComponentForElement(element);
    def.bounds = def.component->getBounds();
    def.minBounds = { 0, 0, 0, 0 };
    def.maxBounds = { 99999, 99999, 99999, 99999 };
    def.margin = BorderSize<int>(0);

    for (int i = 0; i < element->getNumAttributes(); i++)
    {
        auto attribName = element->getAttributeName(i);
        auto attribValue = element->getAttributeValue(i);

        auto componentProcess = componentMap.find(attribName);

        if (componentProcess != componentMap.end())
            (*componentProcess).second(attribValue, def);
    }

    def.bounds.setX(jmax(def.minBounds.getX(), def.bounds.getX()));
    def.bounds.setY(jmax(def.minBounds.getY(), def.bounds.getY()));
    def.bounds.setWidth(jmax(def.minBounds.getWidth(), def.bounds.getWidth()));
    def.bounds.setHeight(jmax(def.minBounds.getHeight(), def.bounds.getHeight()));

    def.bounds.setX(jmin(def.maxBounds.getX(), def.bounds.getX()));
    def.bounds.setY(jmin(def.maxBounds.getY(), def.bounds.getY()));
    def.bounds.setWidth(jmin(def.maxBounds.getWidth(), def.bounds.getWidth()));
    def.bounds.setHeight(jmin(def.maxBounds.getHeight(), def.bounds.getHeight()));

    def.margin.subtractFrom(def.bounds);

    def.component->setBounds(def.bounds);
}

void JML::performGridLayout(XmlElement* element, XmlElement* owner)
{
    Grid grid;

    auto bounds = getComponentForElement(owner)->getLocalBounds();

    // setup grid with the element's attributes
    for (int i = 0; i < element->getNumAttributes(); i++)
    {
        auto attribName = element->getAttributeName(i).toLowerCase();
        auto attribValue = element->getAttributeValue(i).toLowerCase();

        auto gridProcessor = gridMap.find(attribName);

        if (gridProcessor != gridMap.end())
        {
            (*gridProcessor).second(attribValue, grid);
            continue;
        }
        
        if (attribName == "template-rows" || attribName == "template-columns")
        {
            auto args = StringArray::fromTokens(element->getAttributeValue(i),
                                                true);
            
            bool rows = attribName.containsIgnoreCase("rows");
            
            if (rows)
                grid.templateRows.clear();
            else
                grid.templateColumns.clear();
            
            for (auto arg : args)
            {
                Grid::TrackInfo info;
            
                if (arg.containsIgnoreCase("fr"))
                    info = Grid::TrackInfo(Grid::Fr(arg.upToFirstOccurrenceOf("fr", false, true).getIntValue()));
                else
                    info = Grid::TrackInfo(Grid::Px(arg.getIntValue()));
            
                if (rows)
                    grid.templateRows.add(info);
                else
                    grid.templateColumns.add(info);
            }
        }
        else if (attribName == "template-areas")
        {
            auto args = StringArray::fromTokens(element->getAttributeValue(i),
                                                " ", "'");
            
            for (auto arg : args)
                grid.templateAreas.add(arg.unquoted());
        }
        else if (attribName == "auto-columns" || attribName == "auto-rows")
        {
            Grid::TrackInfo info;

            if (attribValue.contains("fr"))
                info = Grid::TrackInfo(Grid::Fr(attribValue.upToFirstOccurrenceOf("fr", false, true).getIntValue()));
            else
                info = Grid::TrackInfo(Grid::Px(attribValue.getIntValue()));

            if (attribName == "auto-columns")
                grid.templateColumns = info;
            else
                grid.templateRows = info;
        }
        else if (attribName == "margin")
        {
            BorderSize<int> margin;

            auto args = StringArray::fromTokens(attribValue, true);

            if (args.size() == 1)
                margin = BorderSize<int>(args[0].getIntValue());
            else if (args.size() == 2)
                margin = BorderSize<int>(args[1].getIntValue(), args[0].getIntValue(),
                                         args[1].getIntValue(), args[0].getIntValue());
            else if (args.size() == 4)
                margin = BorderSize<int>(args[0].getIntValue(), args[1].getIntValue(),
                                         args[2].getIntValue(), args[3].getIntValue());

            margin.subtractFrom(bounds);
        }
    }

    // now setup each of the child elements in the grid
    for (int i = 0; i < element->getNumChildElements(); i++)
    {
        auto child = element->getChildElement(i);
        auto component = getComponentForElement(child);

        GridItem item(component);

        for (auto j = 0; j < child->getNumAttributes(); j++)
        {
            auto attribName = child->getAttributeName(j);
            auto attribValue = child->getAttributeValue(j);

            auto gridItemProcessor = gridItemMap.find(attribName);

            if (gridItemProcessor != gridItemMap.end())
            {
                (*gridItemProcessor).second(attribValue, item);
                continue;
            }
        }

        grid.items.add(item);
    }

    grid.performLayout(bounds);
}

//==============================================================================
const int JML::getAttributeValue(const String& attribName,
                                 const String& attribValue,
                                 Component* component)
{
    auto result = 0;

    // percentages
    if (attribValue.contains("%"))
    {
        auto proportion = attribValue.upToFirstOccurrenceOf("%", false, true).getFloatValue() / 100.f;

        if (attribName.contains("-x") || attribName.contains("-width")
            || attribName == "x" || attribName == "width")
        {
            result = roundToInt(component->getParentComponent()->getWidth() * proportion);
        }
        else if (attribName.contains("-y") || attribName.contains("-height")
            || attribName == "y" || attribName == "height")
        {
            result = roundToInt(component->getParentComponent()->getHeight() * proportion);
        }
        else
        {
            /** If you've hit this, you're using an attribute name that
               doesn't correspond to either the x or y axes.

               For the x-axis we use x, width, left, or right.
               For the y-axis we use y, height, top, or bottom.
             */
            DBG("Attribute name doesn't correspond to x or y axes: '" + attribName + "'");
            jassertfalse;
        }
    }
    // pixel values
    else if (attribValue.contains("px"))
    {
        result = attribValue.upToFirstOccurrenceOf("px", false, true).getIntValue();
    }
    // plain values
    else
    {
        result = attribValue.getIntValue();
    }

    return result;
}

Component* JML::getComponentForElement(XmlElement* element)
{
    return reinterpret_cast<Component*>(tagsMap[element->getTagName()]);
}
