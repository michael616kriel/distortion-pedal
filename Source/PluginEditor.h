/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomLookAndFeel.h"
#include "ReverbComponent.h"
#include "DistortionComponent.h"
#include "DelayComponent.h"

//==============================================================================
/**
*/
class DistortionPedalAudioProcessorEditor  : public juce::AudioProcessorEditor
{

typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

public:
    DistortionPedalAudioProcessorEditor (DistortionPedalAudioProcessor&, juce::AudioProcessorValueTreeState&);
    ~DistortionPedalAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DistortionPedalAudioProcessor& audioProcessor;

    CustomLookAndFeel customLookAndFeel;

    juce::AudioProcessorValueTreeState& valueTreeState;

    ReverbComponent reverbComponent;
    DistortionComponent distortionComponent;
    DelayComponent delayComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionPedalAudioProcessorEditor)
};
