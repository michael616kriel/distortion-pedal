/*
  ==============================================================================

    ReverbComponent.h
    Created: 25 Jul 2021 6:13:45pm
    Author:  Mike

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ReverbComponent : public juce::Component, public juce::AudioProcessorValueTreeState::Listener
{
public:
    ReverbComponent(juce::AudioProcessorValueTreeState&);
    ~ReverbComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void parameterChanged(const juce::String& parameter, float newValue) override;

private:
    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    typedef juce::AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;

    juce::AudioProcessorValueTreeState& valueTreeState;

    juce::Label pedalLabel;

    juce::Label roomSizeLabel;
    juce::Slider roomSizeSlider;
    std::unique_ptr<SliderAttachment> roomSizeAttachment;

    juce::Label dampingLabel;
    juce::Slider dampingSlider;
    std::unique_ptr<SliderAttachment> dampingAttachment;

    juce::Label wetLevelLabel;
    juce::Slider wetLevelSlider;
    std::unique_ptr<SliderAttachment> wetLevelAttachment;

    juce::Label dryLevelLabel;
    juce::Slider dryLevelSlider;
    std::unique_ptr<SliderAttachment> dryLevelAttachment;

    juce::Label widthLabel;
    juce::Slider widthSlider;
    std::unique_ptr<SliderAttachment> widthAttachment;

    juce::Label freezeModeLabel;
    juce::Slider freezeModeSlider;
    std::unique_ptr<SliderAttachment> freezeModeAttachment;

    juce::TextButton bypassButton;
    std::unique_ptr<ButtonAttachment> bypassAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ReverbComponent)
};
