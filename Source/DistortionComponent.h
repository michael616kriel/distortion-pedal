/*
  ==============================================================================

    DistortionComponent.h
    Created: 25 Jul 2021 6:14:40pm
    Author:  Mike

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CustomLookAndFeel.h"

//==============================================================================
/*
*/
class DistortionComponent : public juce::Component
{
public:
    DistortionComponent(juce::AudioProcessorValueTreeState&);
    ~DistortionComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:

    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

    juce::AudioProcessorValueTreeState& valueTreeState;

    juce::Label driveLabel;
    juce::Slider driveSlider;
    std::unique_ptr<SliderAttachment> driveAttachment;

    juce::Label rangeLabel;
    juce::Slider rangeSlider;
    std::unique_ptr<SliderAttachment> rangeAttachment;

    juce::Label blendLabel;
    juce::Slider blendSlider;
    std::unique_ptr<SliderAttachment> blendAttachment;

    juce::Label volumeLabel;
    juce::Slider volumeSlider;
    std::unique_ptr<SliderAttachment> volumeAttachment;


    juce::Label toneHighLabel;
    juce::Slider toneHighSlider;
    std::unique_ptr<SliderAttachment> toneHighAttachment;

    juce::Label toneLowLabel;
    juce::Slider toneLowSlider;
    std::unique_ptr<SliderAttachment> toneLowAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DistortionComponent)
};
