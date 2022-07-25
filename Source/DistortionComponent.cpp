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

    driveLabel.setText("Drive", juce::dontSendNotification);
    driveLabel.setFont(juce::Font(12.0f, juce::Font::plain));
    driveLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(driveLabel);

    addAndMakeVisible(driveSlider);
    driveSlider.setSliderStyle(juce::Slider::Rotary);
    driveSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    driveAttachment.reset(new SliderAttachment(valueTreeState, "drive-drive", driveSlider));

    rangeLabel.setText("Range", juce::dontSendNotification);
    rangeLabel.setFont(juce::Font(12.0f, juce::Font::plain));
    rangeLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(rangeLabel);

    addAndMakeVisible(rangeSlider);
    rangeSlider.setSliderStyle(juce::Slider::Rotary);
    rangeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    rangeAttachment.reset(new SliderAttachment(valueTreeState, "drive-range", rangeSlider));

    blendLabel.setText("Blend", juce::dontSendNotification);
    blendLabel.setFont(juce::Font(12.0f, juce::Font::plain));
    blendLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(blendLabel);

    addAndMakeVisible(blendSlider);
    blendSlider.setSliderStyle(juce::Slider::Rotary);
    blendSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    blendAttachment.reset(new SliderAttachment(valueTreeState, "drive-blend", blendSlider));

    volumeLabel.setText("Volume", juce::dontSendNotification);
    volumeLabel.setFont(juce::Font(12.0f, juce::Font::plain));
    volumeLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(volumeLabel);

    addAndMakeVisible(volumeSlider);
    volumeSlider.setSliderStyle(juce::Slider::Rotary);
    volumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    volumeAttachment.reset(new SliderAttachment(valueTreeState, "drive-volume", volumeSlider));


    toneHighLabel.setText("Tone high", juce::dontSendNotification);
    toneHighLabel.setFont(juce::Font(12.0f, juce::Font::plain));
    toneHighLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(toneHighLabel);

    addAndMakeVisible(toneHighSlider);
    toneHighSlider.setSliderStyle(juce::Slider::Rotary);
    toneHighSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    toneHighAttachment.reset(new SliderAttachment(valueTreeState, "drive-tone-high", toneHighSlider));

    toneLowLabel.setText("Tone Low", juce::dontSendNotification);
    toneLowLabel.setFont(juce::Font(12.0f, juce::Font::plain));
    toneLowLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(toneLowLabel);

    addAndMakeVisible(toneLowSlider);
    toneLowSlider.setSliderStyle(juce::Slider::Rotary);
    toneLowSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    toneLowAttachment.reset(new SliderAttachment(valueTreeState, "drive-tone-low", toneLowSlider));


}

DistortionComponent::~DistortionComponent()
{

}

void DistortionComponent::paint(juce::Graphics& g)
{

    g.fillAll(juce::Colours::black);   // clear the background

    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

}

void DistortionComponent::resized()
{

    auto labelHeight = 10.0f;
    auto area = getLocalBounds().reduced(5.0f, 5.0f);
    auto topArea = getLocalBounds().removeFromTop(getLocalBounds().getHeight() / 2).reduced(5.0f, 5.0f);
    auto bottomArea = getLocalBounds().removeFromBottom(getLocalBounds().getHeight() / 2).reduced(5.0f, 5.0f);
    auto width = getLocalBounds().getWidth() / 4;

    auto driveArea = topArea.removeFromLeft(width);
    driveSlider.setBounds(driveArea.removeFromTop(driveArea.getHeight() - labelHeight));
    driveLabel.setBounds(driveArea.removeFromBottom(labelHeight));

    auto rangArea = topArea.removeFromLeft(width);
    rangeSlider.setBounds(rangArea.removeFromTop(rangArea.getHeight() - labelHeight));
    rangeLabel.setBounds(rangArea.removeFromBottom(labelHeight));

    auto blendArea = topArea.removeFromLeft(width);
    blendSlider.setBounds(blendArea.removeFromTop(blendArea.getHeight() - labelHeight));
    blendLabel.setBounds(blendArea.removeFromBottom(labelHeight));

    auto volumeArea = topArea.removeFromLeft(width);
    volumeSlider.setBounds(volumeArea.removeFromTop(volumeArea.getHeight() - labelHeight));
    volumeLabel.setBounds(volumeArea.removeFromBottom(labelHeight));

    bottomArea.removeFromLeft(width);

    auto toneHighArea = bottomArea.removeFromLeft(width);
    toneHighSlider.setBounds(toneHighArea.removeFromTop(toneHighArea.getHeight() - labelHeight));
    toneHighLabel.setBounds(toneHighArea.removeFromBottom(labelHeight));

    auto toneLowArea = bottomArea.removeFromLeft(width);
    toneLowSlider.setBounds(toneLowArea.removeFromTop(toneLowArea.getHeight() - labelHeight));
    toneLowLabel.setBounds(toneLowArea.removeFromBottom(labelHeight));

}

