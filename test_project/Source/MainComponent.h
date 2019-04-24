#pragma once

#include "JuceHeader.h"

//==============================================================================
class MainComponent :   public Component
{
public:
    //==========================================================================
    MainComponent()
    {
        auto jml = JML::getInstance();
        jml->setJMLFile(File::getCurrentWorkingDirectory().getChildFile("..\\..\\..\\samples\\sample.jml"));

        addAndMakeVisible(button1);
        button1.setButtonText("One");
        jml->setComponentForTag("button1", &button1);

        addAndMakeVisible(button2);
        button2.setButtonText("Two");
        jml->setComponentForTag("button2", &button2);

        setName("MainComponent");
        setSize(400, 300);
    }

    ~MainComponent()
    {
        JML::deleteInstance();
    }

    //==========================================================================
    void paint (Graphics& g) override
    {
    }

    void resized() override
    {
        JML::getInstanceWithoutCreating()->perform();
    }


private:
    //==========================================================================
    TextButton button1;
    TextButton button2;

    //==========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
