/*
  ==============================================================================

    DistortionComponent.cpp
    Created: 25 Jul 2021 6:14:40pm
    Author:  Mike

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DistortionComponent.h"

//==============================================================================
DistortionComponent::DistortionComponent(juce::AudioProcessorValueTreeState& vts) : valueTreeState(vts)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    valueTreeState.addParameterListener("drive-bypass", this);

    addAndMakeVisible(pedalLabel);
    pedalLabel.setText("Distortion", juce::dontSendNotification);
    pedalLabel.setFont(juce::Font(18.0f, juce::Font::bold));
    pedalLabel.setJustificationType(juce::Justification::centred);
    pedalLabel.setColour(juce::Label::textColourId, juce::Colours::black);

    driveLabel.setText("Drive", juce::dontSendNotification);
    driveLabel.setFont(juce::Font(10.0f, juce::Font::plain));
    driveLabel.setJustificationType(juce::Justification::centred);
    driveLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    addAndMakeVisible(driveLabel);

    addAndMakeVisible(driveSlider);
    driveSlider.setSliderStyle(juce::Slider::Rotary);
    driveSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    driveAttachment.reset(new SliderAttachment(valueTreeState, "drive-drive", driveSlider));

    rangeLabel.setText("Range", juce::dontSendNotification);
    rangeLabel.setFont(juce::Font(10.0f, juce::Font::plain));
    rangeLabel.setJustificationType(juce::Justification::centred);
    rangeLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    addAndMakeVisible(rangeLabel);

    addAndMakeVisible(rangeSlider);
    rangeSlider.setSliderStyle(juce::Slider::Rotary);
    rangeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    rangeAttachment.reset(new SliderAttachment(valueTreeState, "drive-range", rangeSlider));

    blendLabel.setText("Blend", juce::dontSendNotification);
    blendLabel.setFont(juce::Font(10.0f, juce::Font::plain));
    blendLabel.setJustificationType(juce::Justification::centred);
    blendLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    addAndMakeVisible(blendLabel);

    addAndMakeVisible(blendSlider);
    blendSlider.setSliderStyle(juce::Slider::Rotary);
    blendSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    blendAttachment.reset(new SliderAttachment(valueTreeState, "drive-blend", blendSlider));

    volumeLabel.setText("Volume", juce::dontSendNotification);
    volumeLabel.setFont(juce::Font(10.0f, juce::Font::plain));
    volumeLabel.setJustificationType(juce::Justification::centred);
    volumeLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    addAndMakeVisible(volumeLabel);

    addAndMakeVisible(volumeSlider);
    volumeSlider.setSliderStyle(juce::Slider::Rotary);
    volumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    volumeAttachment.reset(new SliderAttachment(valueTreeState, "drive-volume", volumeSlider));

    addAndMakeVisible(&bypassButton);
    bypassButton.setButtonText("OFF");
    bypassButton.setColour(juce::TextButton::buttonColourId, juce::Colours::red);
    bypassButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::green);
    bypassButton.setClickingTogglesState(true);
    bypassAttachment.reset(new ButtonAttachment(valueTreeState, "drive-bypass", bypassButton));

}

DistortionComponent::~DistortionComponent()
{

}

void DistortionComponent::paint(juce::Graphics& g)
{

    g.fillAll(juce::Colour::fromRGB(152, 226, 247));

    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

}

void DistortionComponent::resized()
{

    auto labelHeight = 10.0f;
    auto area = getLocalBounds().reduced(5.0f, 5.0f);

    auto headingArea = area.removeFromTop(16.0f);
    auto paramsArea = area.removeFromTop(area.proportionOfHeight(0.7f));
    auto bypassArea = area.removeFromBottom(area.proportionOfHeight(0.3f));

    auto topAreaItemSize = paramsArea.proportionOfHeight(0.5f);
    auto topArea = paramsArea.removeFromTop(topAreaItemSize);
    auto bottomArea = paramsArea.removeFromBottom(topAreaItemSize);

    auto topItemSize = topArea.proportionOfWidth(0.5f);
    auto bottomItemSize = bottomArea.proportionOfWidth(0.5f);

    pedalLabel.setBounds(headingArea);

    auto driveArea = topArea.removeFromLeft(topItemSize);
    driveSlider.setBounds(driveArea.removeFromTop(driveArea.getHeight() - labelHeight));
    driveLabel.setBounds(driveArea.removeFromBottom(labelHeight));

    auto rangArea = topArea.removeFromLeft(topItemSize);
    rangeSlider.setBounds(rangArea.removeFromTop(rangArea.getHeight() - labelHeight));
    rangeLabel.setBounds(rangArea.removeFromBottom(labelHeight));

    auto blendArea = bottomArea.removeFromLeft(bottomItemSize);
    blendSlider.setBounds(blendArea.removeFromTop(blendArea.getHeight() - labelHeight));
    blendLabel.setBounds(blendArea.removeFromBottom(labelHeight));

    auto volumeArea = bottomArea.removeFromLeft(bottomItemSize);
    volumeSlider.setBounds(volumeArea.removeFromTop(volumeArea.getHeight() - labelHeight));
    volumeLabel.setBounds(volumeArea.removeFromBottom(labelHeight));

    bypassButton.setBounds(bypassArea);
   
}

void DistortionComponent::parameterChanged(const juce::String& parameter, float newValue) {
    if (newValue == 1) {
        bypassButton.setButtonText("ON");
    }
    else {
        bypassButton.setButtonText("OFF");
    }
}