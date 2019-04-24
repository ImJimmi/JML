#include "JML.h"

//==============================================================================
JML::JML()
{
    // bounds
    boundsMaps["x"] = [](const int value, Rectangle<int>& bounds) {
        bounds.setX(value);
    };
    boundsMaps["y"] = [](const int value, Rectangle<int>& bounds) {
        bounds.setY(value);
    };
    boundsMaps["width"] = [](const int value, Rectangle<int>& bounds) {
        bounds.setWidth(value);
    };
    boundsMaps["height"] = [](const int value, Rectangle<int>& bounds) {
        bounds.setHeight(value);
    };

    // min-bounds
    boundsMaps["min-x"] = [](const int value, Rectangle<int>& bounds) {
        bounds.setX(value);
    };
    boundsMaps["min-y"] = [](const int value, Rectangle<int>& bounds) {
        bounds.setY(value);
    };
    boundsMaps["min-width"] = [](const int value, Rectangle<int>& bounds) {
        bounds.setWidth(value);
    };
    boundsMaps["min-height"] = [](const int value, Rectangle<int>& bounds) {
        bounds.setHeight(value);
    };

    // max-bounds
    boundsMaps["max-x"] = [](const int value, Rectangle<int>& bounds) {
        bounds.setX(value);
    };
    boundsMaps["max-y"] = [](const int value, Rectangle<int>& bounds) {
        bounds.setY(value);
    };
    boundsMaps["max-width"] = [](const int value, Rectangle<int>& bounds) {
        bounds.setWidth(value);
    };
    boundsMaps["max-height"] = [](const int value, Rectangle<int>& bounds) {
        bounds.setHeight(value);
    };

    // margin
    marginMaps["margin"] = [](const int value, BorderSize<int>& margin) {
        margin.setLeft(value);
        margin.setRight(value);
        margin.setTop(value);
        margin.setBottom(value);
    };
    marginMaps["margin-x"] = [](const int value, BorderSize<int>& margin) {
        margin.setLeft(value);
        margin.setRight(value);
    };
    marginMaps["margin-y"] = [](const int value, BorderSize<int>& margin) {
        margin.setTop(value);
        margin.setBottom(value);
    };
    marginMaps["margin-left"] = [](const int value, BorderSize<int>& margin) {
        margin.setLeft(value);
    };
    marginMaps["margin-right"] = [](const int value, BorderSize<int>& margin) {
        margin.setRight(value);
    };
    marginMaps["margin-top"] = [](const int value, BorderSize<int>& margin) {
        margin.setTop(value);
    };
    marginMaps["margin-bottom"] = [](const int value, BorderSize<int>& margin) {
        margin.setBottom(value);
    };

    // grid
    gridMaps["rows"] = [](const int value, Grid& grid) {
        grid.templateRows.resize(value);
        grid.templateRows.fill(Grid::TrackInfo(1_fr));
    };
    gridMaps["columns"] = [](const int value, Grid& grid) {
        grid.templateColumns.resize(value);
        grid.templateColumns.fill(Grid::TrackInfo(1_fr));
    };
    gridMaps["gap"] = [](const int value, Grid& grid) {
        grid.setGap(Grid::Px(value));
    };
    gridMaps["row-gap"] = [](const int value, Grid& grid) {
        grid.rowGap = Grid::Px(value);
    };
    gridMaps["column-gap"] = [](const int value, Grid& grid) {
        grid.columnGap = Grid::Px(value);
    };
}

JML::~JML()
{
}

//==============================================================================
void JML::setJMLFile(const File& file)
{
    jmlRoot = parseXML(file);
}

//==============================================================================
void JML::setComponentForTag(const String& tag, Component* component)
{
    tagList.set(tag, (int)component);
}

//==============================================================================
void JML::perform()
{
    performLayout(jmlRoot.get());
}

//==============================================================================
void JML::performLayout(XmlElement* element)
{
    for (int i = 0; i < element->getNumChildElements(); i++)
    {
        auto child = element->getChildElement(i);

        if (child->getTagName() == "grid")
            performGridLayout(child);
        else
            layoutComponent(child);

        if (child->getNumChildElements())
            performLayout(child);
    }
}

void JML::performGridLayout(XmlElement* element)
{
    jassert(element != nullptr);

    Grid grid;
    auto child = element->getChildElement(0);
    auto parent = reinterpret_cast<Component*>((int)tagList.getValueAt(tagList.indexOf(child->getTagName())))->getParentComponent();
    auto bounds = parent->getLocalBounds();

    for (int i = 0; i < element->getNumAttributes(); i++)
    {
        auto attribName = element->getAttributeName(i);
        auto attribValue = element->getAttributeValue(i).getIntValue();

        auto func = gridMaps.find(attribName);

        if (func != gridMaps.end())
        {
            (*func).second(attribValue, grid);
            continue;
        }

        if (attribName.equalsIgnoreCase("template-rows")
            || attribName.equalsIgnoreCase("template-columns"))
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
                Grid::TrackInfo ti;

                if (arg.containsIgnoreCase("fr"))
                    ti = Grid::TrackInfo(Grid::Fr(arg.upToFirstOccurrenceOf("fr", false, true).getIntValue()));
                else
                    ti = Grid::TrackInfo(Grid::Px(arg.getIntValue()));

                if (rows)
                    grid.templateRows.add(ti);
                else
                    grid.templateColumns.add(ti);
            }
        }
        else if (attribName.equalsIgnoreCase("template-areas"))
        {
            auto args = StringArray::fromTokens(element->getAttributeValue(i),
                                                " ", "'");

            for (auto arg : args)
                grid.templateAreas.add(arg.unquoted());
        }
        else if (attribName.equalsIgnoreCase("align-content"))
        {
            auto value = element->getAttributeValue(i).toLowerCase();
            Grid::AlignContent ac;

            if (value == "center")
                ac = Grid::AlignContent::center;
            else if (value == "end")
                ac = Grid::AlignContent::end;
            else if (value == "space-around")
                ac = Grid::AlignContent::spaceAround;
            else if (value == "space-between")
                ac = Grid::AlignContent::spaceBetween;
            else if (value == "space-evenly")
                ac = Grid::AlignContent::spaceEvenly;
            else if (value == "start")
                ac = Grid::AlignContent::start;
            else if (value == "stretch")
                ac = Grid::AlignContent::stretch;

            grid.alignContent = ac;
        }
        else if (attribName.equalsIgnoreCase("align-items"))
        {
            auto value = element->getAttributeValue(i).toLowerCase();
            Grid::AlignItems ai;

            if (value == "center")
                ai = Grid::AlignItems::center;
            else if (value == "end")
                ai = Grid::AlignItems::end;
            else if (value == "start")
                ai = Grid::AlignItems::start;
            else if (value == "stretch")
                ai = Grid::AlignItems::stretch;

            grid.alignItems = ai;
        }
        else if (attribName.equalsIgnoreCase("justify-content"))
        {
            auto value = element->getAttributeValue(i).toLowerCase();
            Grid::JustifyContent jc;

            if (value == "center")
                jc = Grid::JustifyContent::center;
            else if (value == "end")
                jc = Grid::JustifyContent::end;
            else if (value == "space-around")
                jc = Grid::JustifyContent::spaceAround;
            else if (value == "space-between")
                jc = Grid::JustifyContent::spaceBetween;
            else if (value == "space-evenly")
                jc = Grid::JustifyContent::spaceEvenly;
            else if (value == "start")
                jc = Grid::JustifyContent::start;
            else if (value == "stretch")
                jc = Grid::JustifyContent::stretch;

            grid.justifyContent = jc;
        }
        else if (attribName.equalsIgnoreCase("justify-items"))
        {
            auto value = element->getAttributeValue(i).toLowerCase();
            Grid::JustifyItems ji;

            if (value == "center")
                ji = Grid::JustifyItems::center;
            else if (value == "end")
                ji = Grid::JustifyItems::end;
            else if (value == "start")
                ji = Grid::JustifyItems::start;
            else if (value == "stretch")
                ji = Grid::JustifyItems::stretch;

            grid.justifyItems = ji;
        }
    }

    for (int i = 0; i < element->getNumChildElements(); i++)
    {
        auto child = element->getChildElement(i);
        auto component = reinterpret_cast<Component*>((int)tagList.getValueAt(tagList.indexOf(child->getTagName())));
        
        auto row = 1;
        auto column = 1;

        GridItem item(component);

        for (int j = 0; j < child->getNumAttributes(); j++)
        {
            auto attribName = child->getAttributeName(j);
            auto attribValue = child->getAttributeValue(j);

            if (attribName == "grid-row")
                item.row = { attribValue.getIntValue(), attribValue.getIntValue() };
            else if (attribName == "grid-column")
                item.column = { attribValue.getIntValue(), attribValue.getIntValue() };
            else if (attribName == "grid-area")
                item.setArea(attribValue);
        }

        grid.items.add(item);
    }
    
    BorderSize<int> margin;

    for (int i = 0; i < element->getNumAttributes(); i++)
    {
        auto attribName = element->getAttributeName(i);
        auto attribValue = getAttributeValue(attribName,
                                             element->getAttributeValue(i),
                                             parent);

        {
            auto func = marginMaps.find(attribName);

            if (func != marginMaps.end())
            {
                (*func).second(attribValue, margin);
                continue;
            }
        }

        {
            auto func = gridMaps.find(attribName);

            if (func != gridMaps.end())
            {
                (*func).second(attribValue, grid);
                continue;
            }
        }
    }

    margin.subtractFrom(bounds);
    grid.performLayout(bounds);
}

void JML::layoutComponent(XmlElement* element)
{
    auto component = reinterpret_cast<Component*>((int)tagList.getValueAt(tagList.indexOf(element->getTagName())));

    Rectangle<int> bounds = component->getBounds();
    Rectangle<int> minBounds = { 0, 0, 0, 0 };
    Rectangle<int> maxBounds = { 9999, 9999, 9999, 9999 };
    BorderSize<int> margin = { 0, 0, 0, 0 };

    for (int i = 0; i < element->getNumAttributes(); i++)
    {
        auto attribName = element->getAttributeName(i);
        auto attribValue = getAttributeValue(attribName,
                                             element->getAttributeValue(i),
                                             component);

        // bounds attributes
        {
            auto func = boundsMaps.find(attribName);

            if (func != boundsMaps.end())
            {
                if (attribName.contains("min-"))
                    (*func).second(attribValue, minBounds);
                else if (attribName.contains("max-"))
                    (*func).second(attribValue, maxBounds);
                else
                    (*func).second(attribValue, bounds);

                continue;
            }
        }

        // margin attributes
        {
            auto func = marginMaps.find(attribName);

            if (func != marginMaps.end())
            {
                (*func).second(attribValue, margin);
                continue;
            }
        }
    }

    bounds.setX(jmax(minBounds.getX(), bounds.getX()));
    bounds.setY(jmax(minBounds.getY(), bounds.getY()));
    bounds.setWidth(jmax(minBounds.getWidth(), bounds.getWidth()));
    bounds.setHeight(jmax(minBounds.getHeight(), bounds.getHeight()));

    bounds.setX(jmin(maxBounds.getX(), bounds.getX()));
    bounds.setY(jmin(maxBounds.getY(), bounds.getY()));
    bounds.setWidth(jmin(maxBounds.getWidth(), bounds.getWidth()));
    bounds.setHeight(jmin(maxBounds.getHeight(), bounds.getHeight()));

    margin.subtractFrom(bounds);

    component->setBounds(bounds);
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
    if (attribValue.contains("px"))
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

//==============================================================================
JUCE_IMPLEMENT_SINGLETON(JML)
