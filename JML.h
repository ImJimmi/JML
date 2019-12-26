/***********************************************************************************************************************
    BEGIN_JUCE_MODULE_DECLARATION

    ID:               jml
    vendor:           James Johnson
    version:          0.2.0
    name:             JUCE Markup Language
    description:      JML
    dependencies:     juce_core, juce_gui_basics

    END_JUCE_MODULE_DECLARATION
***********************************************************************************************************************/

#pragma once
#define JML_H_INCLUDED

// JUCE includes
#include <juce_core/juce_core.h>
#include <juce_gui_basics/juce_gui_basics.h>

// JML includes
#include "core/jml_ComponentLayoutSpecification.h"
#include "core/jml_Functions.h"

#include "layout/jml_BlockLayout.h"
#include "layout/jml_FlexLayout.h"
#include "layout/jml_GridLayout.h"

#include "core/jml_Core.h"
