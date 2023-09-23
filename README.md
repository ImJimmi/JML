# JML - JUCE Markup Language

## DEPRECATED

Please see [JIVE](https://github.com/ImJimmi/JIVE) for a new and improved decalrative UI framework for JUCE.

---

JML is an attempt to create a markup language for designing GUI's in [JUCE](https://github.com/WeAreROLI/JUCE).

This repository is structured as a JUCE module so it can be easily implementing into JUCE projects. The JML module interprets an XML file and uses the list of defined tags and attributes to position components within a JUCE project.

The convention for JML files is the use the `.jml` extension and to start the file with the `<jml>` tag. This is only a convention and isn't actually required - although a root element is required within the chosen file. The syntax for JML files is identical to XML (the module uses JUCE's `XmlElement` class).

## Examples
This very basic example positions two buttons in the top-left corner of the parent component:
```xml
<jml>
  <button1 x="10" y="10" width="150" height="50"/>
  <button2 x="10" y="70" width="150", height="50"/>
</jml>
```

The corresponding C++ code:
```c++
MyComponent()
{
    JML jml;
    jml.setJMLFile(File("sample.jml"));
    
    jml.setComponentForTag("button1", &button1);
    jml.setComponentForTag("button2", &button2);
}

void resized()
{
    jml.perform();
}
```

The JML file can be altered without ever having to rewrite or even recompile the C++ code.

---

This example uses the grid system to position buttons in a 2x2 grid:
```xml
<jml display="grid" rows="2" columns="2" template-areas="'a b' 'c d'" gap="10" margin="10">
  <button1 width="100" area="c"/>
  <button2 row="1 3" column="2"/>
  <button3 height="25" align-self="center"/>
</jml>
```

And the corresponding C++ code:
```c++
MyComponent()
{
    JML jml;
    jml.setJMLFile(File("sample.jml"));
    jml.setComponentForTag("mainComponent", this);

    for (auto button : buttons)
        jml.setComponentForTag(button->getName(), button);
}

void resized()
{
    jml.perform();
}
```

This is equivalent to the following code when not using JML:
```c++
void MainComponent::resized()
{
    Grid grid;
    grid.templateRows = { Grid::TrackInfo(1_fr), Grid::TrackInfo(1_fr) };
    grid.templateColumns = { Grid::TrackInfo(1_fr), Grid::TrackInfo(1_fr) };
    grid.templateAreas = { "a b", "c d" };
    grid.setGap(10_px);

    grid.items = { GridItem(buttons[0]).withWidth(100.f).withArea("c"),
                   GridItem(buttons[1]).withRow({ 1, 3 }).withColumn({ 2 }),
                   GridItem(buttons[2]).withHeight(25.f).withAlignSelf(GridItem::AlignSelf::center) };

    grid.performLayout(getLocalBounds().reduced(10));
}
```

In both cases, this is the result:

![JML grid example](https://i.imgur.com/9fW4oFj.png)


## Getting Started

1. Clone this repository: `git clone https://github.com/ImJimmi/JML.git`
2. Add the JML module to your JUCE project
3. In your top-most Component class, create a JML object: `JML jml;`
4. Set the JML file to use using `jml.setJMLFile(File("myJMLFile.jml"));`
4. Set the Components to use for each tag in the JML file using `jml.setComponentForTag("tagName", &component);`
5. Call `jml.perform()` in the `resized()` method
