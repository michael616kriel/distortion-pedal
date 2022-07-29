/*
  ==============================================================================

    DelayComponent.h
    Created: 25 Jul 2021 6:14:09pm
    Author:  Mike

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CustomLookAndFeel.h"

//==============================================================================
/*
*/
class DelayComponent : public juce::Component, public juce::AudioProcessorValueTreeState::Listener
{
public:
    DelayComponent(juce::AudioProcessorValueTreeState&);
    ~DelayComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void parameterChanged(const juce::String& parameter, float newValue) override;

private:

    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    typedef juce::AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;

    juce::AudioProcessorValueTreeState& valueTreeState;

    juce::Label pedalLabel;

    juce::Label maxDelayTimeLabel;
    juce::Slider maxDelayTimeSlider;
    std::unique_ptr<SliderAttachment> maxDelayTimeAttachment;

    juce::Label delayTimeLabel;
    juce::Slider delayTimeSlider;
    std::unique_ptr<SliderAttachment> delayTimeAttachment;

    juce::Label wetLevelLabel;
    juce::Slider wetLevelSlider;
    std::unique_ptr<SliderAttachment> wetLevelAttachment;

    juce::Label feedbackLabel;
    juce::Slider feedbackSlider;
    std::unique_ptr<SliderAttachment> feedbackAttachment;

    juce::TextButton bypassButton;
    std::unique_ptr<ButtonAttachment> bypassAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DelayComponent)
};
