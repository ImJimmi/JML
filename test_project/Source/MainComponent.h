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
        jml.setComponentForTag("jml", this);

        for (int i = 0; i < 5; i++)
        {
            auto name = "Button " + String(i + 1);
            auto button = buttons.add(new TextButton(name));

            addAndMakeVisible(button);
            jml.setComponentForTag("button" + String(i), (Component*)button);
        }

        jml.watch(10);

        setSize(300, 200);
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
        try
        {
            jml.performLayout();
        }
        catch (const std::exception& e)
        {
            DBG(e.what());
            jassertfalse;
        }
    }


private:
    //==========================================================================
    JML jml;

    OwnedArray<TextButton> buttons;

    //==========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
