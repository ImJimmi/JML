#include "jml_Core.h"

//======================================================================================================================
JML::JML(const File& file)
{
    jassert(file.existsAsFile());
    jmlFile = file;
    jmlRoot = parseXML(file);

    /** The XML parser failed to parse the provided file! */
    jassert(jmlRoot);
}

JML::JML(const String& jmlString)
{
    jmlRoot = parseXML(jmlString);

    /** The XML parser failed to parse the provided string! */
    jassert(jmlRoot);
}

//======================================================================================================================
void JML::performLayout(bool reparseFile)
{
    if (reparseFile)
    {
        jmlRoot = parseXML(jmlFile);

        /** The XML parser failed to parse the provided file! */
        jassert(jmlRoot);
    }

    topLevelLayout.reset(new jml::ComponentLayoutSpecification);
    performLayoutFor(topLevelLayout.get(), jmlRoot.get());
}

//======================================================================================================================
void JML::setComponentForTag(const String& tag, Component* component)
{
    /** You must provide a valid pointer to a Component! */
    jassert(component);

    /** You can't use an empty String for a tag! */
    jassert(tag.isNotEmpty());

    /** You must use a valid XML name for the tag! */
    jassert(XmlElement::isValidXmlName(tag));

    tagsMap[tag] = component;
}

void JML::setVariable(const String& name, var value)
{
    /** Variables can't have empty names! */
    jassert(name.isNotEmpty());

    variables[name] = value;
}

var JML::getVariable(const String& name)
{
    return variables[name];
}

//======================================================================================================================
void JML::performLayoutFor(jml::ComponentLayoutSpecification* layout, XmlElement* element)
{
    buildFor(element, layout);
    jml::BlockLayout::perform(layout);

    // perform layout for each of this element's children
    jassert(layout->children.size() == element->getNumChildElements());

    for (int i = 0; i < layout->children.size(); i++)
        performLayoutFor(&layout->children[i], element->getChildElement(i));
}

void JML::buildFor(XmlElement* element, jml::ComponentLayoutSpecification* layout)
{
    // handle variables
    for (int i = 0; i < element->getNumAttributes(); i++)
    {
        auto value = element->getAttributeValue(i);

        while (value.contains("{{"))
        {
            auto variableString = value.fromFirstOccurrenceOf("{{", true, false).upToFirstOccurrenceOf("}}", true, false);
            auto variableName = variableString.replace("{{", "").replace("}}", "").trim();

            auto result = variables.find(variableName);
            if (result != variables.end())
            {
                auto variableValue = variables[variableName].toString();
                value = value.replace(variableString, variableValue);
            }
            else
            {
                /** The specified variable hasn't been added to the map yet! */
                jassertfalse;
            }
        }

        element->setAttribute(element->getAttributeName(i), value);
    }

    // initialise members
    layout->tagName = element->getTagName();
    layout->component = tagsMap[layout->tagName];
    layout->isInline = element->getStringAttribute("display", "block").startsWith("inline-");

    // setup properties
    layout->properties = ValueTree("properties");

    for (int i = 0; i < element->getNumAttributes(); i++)
        layout->properties.setProperty(element->getAttributeName(i), element->getAttributeValue(i), nullptr);

    // build layout
    jml::BlockLayout::build(layout);

    // create children
    for (int i = 0; i < element->getNumChildElements(); i++)
    {
        // add a new child to the layout
        layout->children.push_back({});
        auto& childLayout = layout->children.back();

        // set the current layout as the new child's parent
        childLayout.parent = layout;
        childLayout.indexAmongSiblings = i;
    }
}
