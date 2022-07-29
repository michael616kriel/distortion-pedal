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
    valueTreeState.addParameterListener("reverb-bypass", this);

    addAndMakeVisible(pedalLabel);
    pedalLabel.setText("Reverb", juce::dontSendNotification);
    pedalLabel.setFont(juce::Font(18.0f, juce::Font::bold));
    pedalLabel.setJustificationType(juce::Justification::centred);
    pedalLabel.setColour(juce::Label::textColourId, juce::Colours::black);

    roomSizeLabel.setText("Room Size", juce::dontSendNotification);
    roomSizeLabel.setFont(juce::Font(10.0f, juce::Font::plain));
    roomSizeLabel.setJustificationType(juce::Justification::centred);
    roomSizeLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    addAndMakeVisible(roomSizeLabel);

    addAndMakeVisible(roomSizeSlider);
    roomSizeSlider.setSliderStyle(juce::Slider::Rotary);
    roomSizeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    roomSizeAttachment.reset(new SliderAttachment(valueTreeState, "reverb-roomSize", roomSizeSlider));

    dampingLabel.setText("Damping", juce::dontSendNotification);
    dampingLabel.setFont(juce::Font(10.0f, juce::Font::plain));
    dampingLabel.setJustificationType(juce::Justification::centred);
    dampingLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    addAndMakeVisible(dampingLabel);

    addAndMakeVisible(dampingSlider);
    dampingSlider.setSliderStyle(juce::Slider::Rotary);
    dampingSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    dampingAttachment.reset(new SliderAttachment(valueTreeState, "reverb-damping", dampingSlider));

    wetLevelLabel.setText("Wet Level", juce::dontSendNotification);
    wetLevelLabel.setFont(juce::Font(10.0f, juce::Font::plain));
    wetLevelLabel.setJustificationType(juce::Justification::centred);
    wetLevelLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    addAndMakeVisible(wetLevelLabel);

    addAndMakeVisible(wetLevelSlider);
    wetLevelSlider.setSliderStyle(juce::Slider::Rotary);
    wetLevelSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    wetLevelAttachment.reset(new SliderAttachment(valueTreeState, "reverb-wetLevel", wetLevelSlider));

    dryLevelLabel.setText("Dry Level", juce::dontSendNotification);
    dryLevelLabel.setFont(juce::Font(10.0f, juce::Font::plain));
    dryLevelLabel.setJustificationType(juce::Justification::centred);
    dryLevelLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    addAndMakeVisible(dryLevelLabel);

    addAndMakeVisible(dryLevelSlider);
    dryLevelSlider.setSliderStyle(juce::Slider::Rotary);
    dryLevelSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    dryLevelAttachment.reset(new SliderAttachment(valueTreeState, "reverb-dryLevel", dryLevelSlider));

    widthLabel.setText("Width", juce::dontSendNotification);
    widthLabel.setFont(juce::Font(10.0f, juce::Font::plain));
    widthLabel.setJustificationType(juce::Justification::centred);
    widthLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    addAndMakeVisible(widthLabel);

    addAndMakeVisible(widthSlider);
    widthSlider.setSliderStyle(juce::Slider::Rotary);
    widthSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    widthAttachment.reset(new SliderAttachment(valueTreeState, "reverb-width", widthSlider));

    freezeModeLabel.setText("Freeze Mode", juce::dontSendNotification);
    freezeModeLabel.setFont(juce::Font(10.0f, juce::Font::plain));
    freezeModeLabel.setJustificationType(juce::Justification::centred);
    freezeModeLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    addAndMakeVisible(freezeModeLabel);

    addAndMakeVisible(freezeModeSlider);
    freezeModeSlider.setSliderStyle(juce::Slider::Rotary);
    freezeModeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    freezeModeAttachment.reset(new SliderAttachment(valueTreeState, "reverb-freezeMode", freezeModeSlider));

    addAndMakeVisible(&bypassButton);
    bypassButton.setButtonText("OFF");
    bypassButton.setColour(juce::TextButton::buttonColourId, juce::Colours::red);
    bypassButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::green);
    bypassButton.setClickingTogglesState(true);
    bypassAttachment.reset(new ButtonAttachment(valueTreeState, "reverb-bypass", bypassButton));

}

ReverbComponent::~ReverbComponent()
{

}

void ReverbComponent::paint(juce::Graphics& g)
{

    g.fillAll(juce::Colour::fromRGB(202, 238, 190));

    g.setColour(juce::Colours::black);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

}

void ReverbComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    auto labelHeight = 10.0f;
    auto area = getLocalBounds().reduced(5.0f, 5.0f);

    auto headingArea = area.removeFromTop(16.0f);
    auto paramsArea = area.removeFromTop(area.proportionOfHeight(0.7f));
    auto bypassArea = area.removeFromBottom(area.proportionOfHeight(0.3f));

    auto topAreaItemSize = paramsArea.proportionOfHeight(0.5f);
    auto topArea = paramsArea.removeFromTop(topAreaItemSize);
    auto bottomArea = paramsArea.removeFromBottom(topAreaItemSize);

    auto topItemSize = topArea.proportionOfWidth(0.33f);
    auto bottomItemSize = bottomArea.proportionOfWidth(0.33f);

    pedalLabel.setBounds(headingArea);

    auto roomArea = topArea.removeFromLeft(topItemSize);
    roomSizeSlider.setBounds(roomArea.removeFromTop(roomArea.getHeight() - labelHeight));
    roomSizeLabel.setBounds(roomArea.removeFromBottom(labelHeight));

    auto dampingArea = topArea.removeFromLeft(topItemSize);
    dampingSlider.setBounds(dampingArea.removeFromTop(dampingArea.getHeight() - labelHeight));
    dampingLabel.setBounds(dampingArea.removeFromBottom(labelHeight));

    auto wetLevelArea = topArea.removeFromLeft(topItemSize);
    wetLevelSlider.setBounds(wetLevelArea.removeFromTop(wetLevelArea.getHeight() - labelHeight));
    wetLevelLabel.setBounds(wetLevelArea.removeFromBottom(labelHeight));

    auto dryLevelArea = bottomArea.removeFromLeft(bottomItemSize);
    dryLevelSlider.setBounds(dryLevelArea.removeFromTop(dryLevelArea.getHeight() - labelHeight));
    dryLevelLabel.setBounds(dryLevelArea.removeFromBottom(labelHeight));

    auto widthArea = bottomArea.removeFromLeft(bottomItemSize);
    widthSlider.setBounds(widthArea.removeFromTop(widthArea.getHeight() - labelHeight));
    widthLabel.setBounds(widthArea.removeFromBottom(labelHeight));

    auto freezeModeArea = bottomArea.removeFromLeft(bottomItemSize);
    freezeModeSlider.setBounds(freezeModeArea.removeFromTop(freezeModeArea.getHeight() - labelHeight));
    freezeModeLabel.setBounds(freezeModeArea.removeFromBottom(labelHeight));

    bypassButton.setBounds(bypassArea);
}

void ReverbComponent::parameterChanged(const juce::String& parameter, float newValue) {
    if (newValue == 1) {
        bypassButton.setButtonText("ON");
    }
    else {
        bypassButton.setButtonText("OFF");
    }
}