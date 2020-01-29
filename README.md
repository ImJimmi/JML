# JML – JUCE Markup Language
JML is an attempt to create a more intuitive GUI layout system for the [JUCE](https://github.com/WeAreROLI/JUCE) framework.

JML is largely inspired by HTML in its design and implementation. The system uses a set of guidelines for XML documents that are interpreted by the JML JUCE module to position graphical elements within an interface. The defined XML attributes and hierarchy guidelines are designed to make it much easier to write, read, and edit GUI code than the existing methods presented by JUCE.

See the [docs](./docs/) folder for some examples of JML code and a full list of supported attributes.

### Usage
This repository is structured as a JUCE module for easy integration into new or existing projects.

To get the latest version, simply clone this repository: `git clone https://github.com/ImJimmi/JML.git`.
Then add the JML module to your JUCE project and save the project in the Projucer.

If you are using git as source control for your JUCE project (which you probably should) then it may be good idea to instead add this repository as a submodule to your own repository: `git submodule add https://github.com/ImJimmi/JML.git`.

### Planned Features
* __Grid and FlexBox support__ - Reintroduce support for JUCE's `Grid` and `FlexBox` classes. These layout styles are based on the CSS modules of the same names.
* __Embedded SVG__ - The ability to embed SVG elements into JML code.
* __Relative Values__ - The ability to specify values relative to properties of other Components. For example: `x="myButton.centre.x + 10"`.
