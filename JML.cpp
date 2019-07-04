#include "JML.h"

#include "src/jml_BlockLayoutManager.cpp"
#include "src/jml_FlexLayoutManager.cpp"
#include "src/jml_GridLayoutManager.cpp"

//==============================================================================
JML::JML(const File& file)
{
    setJMLFile(file);
}

//==============================================================================
void JML::setJMLFile(const File& file)
{
    jassert(file.existsAsFile());
    jmlFile = file;

    jmlRoot = parseXML(file);
}

void JML::setJMLRoot(std::unique_ptr<XmlElement> root)
{
    jassert(root);

    jmlRoot = std::move(root);
}

void JML::watch(const int updatesPerSecond)
{
    startTimer(updatesPerSecond);
}

//==============================================================================
void JML::timerCallback()
{
    jmlRoot = parseXML(jmlFile);
    performLayout();
}

//==============================================================================
void JML::performLayout()
{
    jassert(jmlRoot != nullptr);
    performLayoutForElement(jmlRoot.get());
}

const int JML::attributeStringToInt(Component* component,
                                    const String& name, String s)
{
    if (s.endsWith("%"))
    {
        auto parent = component->getParentComponent();

        if (parent != nullptr)
        {
            auto perc = s.upToLastOccurrenceOf("%", false, true).getFloatValue() / 100.f;

            if (name.contains("x") || name.contains("width"))
                return roundToInt(parent->getWidth() * perc);
            else if (name.contains("y") || name.contains("height"))
                return roundToInt(parent->getHeight() * perc);
            else
            {
                // The attribute name doesn't contain any of the accepted
                // specifiers! (See above).
                jassertfalse;
                return roundToInt(perc * 100.f);
            }
        }
        else
        {
            // You can't use % on the top-level component! It has no parent!
            jassertfalse;
        }
    }
    else
    {
        return s.getIntValue();
    }
}

//==============================================================================
void JML::setComponentForTag(const String& tag, Component* component)
{
    jassert(component != nullptr);
    jassert(tag.isNotEmpty());

    tagsMap[tag] = component;
}

//==============================================================================
void JML::performLayoutForElement(XmlElement* element)
{
    jassert(element != nullptr);

    auto component = tagsMap[element->getTagName()];

    jassert(component != nullptr);

    // do Block layout by default
    jml::BlockLayoutManager(element, component);

    // perform Grid and Flex layouts
    if (element->hasAttribute("display"))
    {
        auto display = element->getStringAttribute("display").toLowerCase();

        if (display == "grid")
            jml::GridLayoutManager(tagsMap, element, component);
        else if (display == "flex")
            jml::FlexLayoutManager(tagsMap, element, component);
        else
        {
            jassertfalse;
        }
    }

    for (int i = 0; i < element->getNumChildElements(); i++)
    {
        performLayoutForElement(element->getChildElement(i));
    }
}

//==============================================================================
Component* JML::getComponentForElement(XmlElement* element)
{
    jassert(element != nullptr);
    return reinterpret_cast<Component*>(tagsMap[element->getTagName()]);
}
