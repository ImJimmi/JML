#pragma once

#include "JuceHeader.h"

//==============================================================================
class MainComponent :   public Component
{
public:
    //==========================================================================
    MainComponent()
    {
        jml.setJMLFile(File::getCurrentWorkingDirectory().getChildFile("..\\..\\..\\samples\\sample.jml"));
        jml.setComponentForTag("mainComponent", this);

        for (int i = 0; i < 7; i++)
        {
            auto name = "button" + String(i);
            auto button = buttons.add(new TextButton(name));

            addAndMakeVisible(button);
            jml.setComponentForTag(name, button);
        }

        setSize(400, 300);
    }

    ~MainComponent()
    {
    }

    //==========================================================================
    void paint (Graphics& g) override
    {
    }

    void resized() override
    {
        jml.perform();
    }


private:
    //==========================================================================
    JML jml;

    OwnedArray<TextButton> buttons;

    //==========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
