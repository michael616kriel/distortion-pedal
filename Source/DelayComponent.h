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
class DelayComponent : public juce::Component
{
public:
    DelayComponent(juce::AudioProcessorValueTreeState&);
    ~DelayComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:

    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

    juce::AudioProcessorValueTreeState& valueTreeState;

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

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DelayComponent)
};
