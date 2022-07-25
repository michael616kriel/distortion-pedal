/*
  ==============================================================================

    ReverbComponent.cpp
    Created: 25 Jul 2021 6:13:45pm
    Author:  Mike

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ReverbComponent.h"

//==============================================================================
ReverbComponent::ReverbComponent(juce::AudioProcessorValueTreeState& vts) : valueTreeState(vts)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    roomSizeLabel.setText("Room Size", juce::dontSendNotification);
    roomSizeLabel.setFont(juce::Font(12.0f, juce::Font::plain));
    roomSizeLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(roomSizeLabel);

    addAndMakeVisible(roomSizeSlider);
    roomSizeSlider.setSliderStyle(juce::Slider::Rotary);
    roomSizeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    roomSizeAttachment.reset(new SliderAttachment(valueTreeState, "reverb-roomSize", roomSizeSlider));

    dampingLabel.setText("Damping", juce::dontSendNotification);
    dampingLabel.setFont(juce::Font(12.0f, juce::Font::plain));
    dampingLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(dampingLabel);

    addAndMakeVisible(dampingSlider);
    dampingSlider.setSliderStyle(juce::Slider::Rotary);
    dampingSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    dampingAttachment.reset(new SliderAttachment(valueTreeState, "reverb-damping", dampingSlider));

    wetLevelLabel.setText("Wet Level", juce::dontSendNotification);
    wetLevelLabel.setFont(juce::Font(12.0f, juce::Font::plain));
    wetLevelLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(wetLevelLabel);

    addAndMakeVisible(wetLevelSlider);
    wetLevelSlider.setSliderStyle(juce::Slider::Rotary);
    wetLevelSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    wetLevelAttachment.reset(new SliderAttachment(valueTreeState, "reverb-wetLevel", wetLevelSlider));

    dryLevelLabel.setText("Dry Level", juce::dontSendNotification);
    dryLevelLabel.setFont(juce::Font(12.0f, juce::Font::plain));
    dryLevelLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(dryLevelLabel);

    addAndMakeVisible(dryLevelSlider);
    dryLevelSlider.setSliderStyle(juce::Slider::Rotary);
    dryLevelSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    dryLevelAttachment.reset(new SliderAttachment(valueTreeState, "reverb-dryLevel", dryLevelSlider));

    widthLabel.setText("Width", juce::dontSendNotification);
    widthLabel.setFont(juce::Font(12.0f, juce::Font::plain));
    widthLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(widthLabel);

    addAndMakeVisible(widthSlider);
    widthSlider.setSliderStyle(juce::Slider::Rotary);
    widthSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    widthAttachment.reset(new SliderAttachment(valueTreeState, "reverb-width", widthSlider));

    freezeModeLabel.setText("Freeze Mode", juce::dontSendNotification);
    freezeModeLabel.setFont(juce::Font(12.0f, juce::Font::plain));
    freezeModeLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(freezeModeLabel);

    addAndMakeVisible(freezeModeSlider);
    freezeModeSlider.setSliderStyle(juce::Slider::Rotary);
    freezeModeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    freezeModeAttachment.reset(new SliderAttachment(valueTreeState, "reverb-freezeMode", freezeModeSlider));

}

ReverbComponent::~ReverbComponent()
{

}

void ReverbComponent::paint(juce::Graphics& g)
{

    g.fillAll(juce::Colours::black);   // clear the background

    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

}

void ReverbComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    auto labelHeight = 10.0f;
    auto area = getLocalBounds();
    auto width = area.getWidth() / 3;

    auto areaHeight = area.getHeight() / 2;
    auto areaTop = area.removeFromTop(areaHeight).reduced(5.0f, 5.0f);
    auto areaBottom = area.removeFromBottom(areaHeight).reduced(5.0f, 5.0f);

    auto roomArea = areaTop.removeFromLeft(width);
    roomSizeSlider.setBounds(roomArea.removeFromTop(roomArea.getHeight() - labelHeight));
    roomSizeLabel.setBounds(roomArea.removeFromBottom(labelHeight));

    auto dampingArea = areaTop.removeFromLeft(width);
    dampingSlider.setBounds(dampingArea.removeFromTop(dampingArea.getHeight() - labelHeight));
    dampingLabel.setBounds(dampingArea.removeFromBottom(labelHeight));

    auto wetLevelArea = areaTop.removeFromLeft(width);
    wetLevelSlider.setBounds(wetLevelArea.removeFromTop(wetLevelArea.getHeight() - labelHeight));
    wetLevelLabel.setBounds(wetLevelArea.removeFromBottom(labelHeight));

    auto dryLevelArea = areaBottom.removeFromLeft(width);
    dryLevelSlider.setBounds(dryLevelArea.removeFromTop(dryLevelArea.getHeight() - labelHeight));
    dryLevelLabel.setBounds(dryLevelArea.removeFromBottom(labelHeight));

    auto widthArea = areaBottom.removeFromLeft(width);
    widthSlider.setBounds(widthArea.removeFromTop(widthArea.getHeight() - labelHeight));
    widthLabel.setBounds(widthArea.removeFromBottom(labelHeight));

    auto freezeModeArea = areaBottom.removeFromLeft(width);
    freezeModeSlider.setBounds(freezeModeArea.removeFromTop(freezeModeArea.getHeight() - labelHeight));
    freezeModeLabel.setBounds(freezeModeArea.removeFromBottom(labelHeight));

}
