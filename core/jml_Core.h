#pragma once

#include <unordered_map>

//======================================================================================================================
using namespace juce;

//======================================================================================================================
/** Manages the layout of Components using an XML-formatted file or string.
    See https://github.com/ImJimmi/JML for more information.
*/
class JML
{
public:
    //==================================================================================================================
    /** Initialises the JML system using the given JML file. */
    JML(const File& file);

    /** Initialises the JML system using the given JML string. */
    JML(const String& jmlString);

    //==================================================================================================================
    /** Calculates and sets the bounds of the Components in the JML heirarchy.
        You should call this everytime your top-level Component is resized.
    */
    void performLayout(bool reparseFile = false);

    //==================================================================================================================
    /** This tells the system which Component object to use when it encounters
        the given tag in the JML file.

        You must ensure all Component's used by the JML system have a longer
        lifetime than the JML object otherwise the pointers will become invalid.

        @param tag          The tag name (must be a valid XML name).
        @param component    A pointer to the Component to map to the given tag
    */
    void setComponentForTag(const String& tag, Component* component);

    /** This tells the JML system what value to use when the given variable
        name is encountered in the JML file.

        @param variableName The name of the variable.
        @param value        The variable's value.
    */
    void setVariable(const String& variableName, var value);

    /** This returns a copy of the var object that is mapped to the given
        variable name.

        @param variableName The name of the desired variable.

        @returns    The var object mapped to the given variable name. If no
                    variable with the given name is found, returns a void var
                    object.
    */
    var getVariable(const String& variableName);

private:
    //==================================================================================================================
    void performLayoutFor(jml::ComponentLayoutSpecification*, XmlElement* element);
    void buildFor(XmlElement* element, jml::ComponentLayoutSpecification* layout);

    //==================================================================================================================
    File jmlFile;
    std::unique_ptr<XmlElement> jmlRoot;
    std::unique_ptr<jml::ComponentLayoutSpecification> topLevelLayout;

    std::unordered_map<String, Component*> tagsMap;
    std::unordered_map<String, var> variables;
};
