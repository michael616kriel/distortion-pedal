/*
  ==============================================================================

    DelayComponent.cpp
    Created: 25 Jul 2021 6:14:09pm
    Author:  Mike

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DelayComponent.h"

//==============================================================================
DelayComponent::DelayComponent(juce::AudioProcessorValueTreeState& vts) : valueTreeState(vts)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    valueTreeState.addParameterListener("delay-bypass", this);

    addAndMakeVisible(pedalLabel);
    pedalLabel.setText("Delay", juce::dontSendNotification);
    pedalLabel.setFont(juce::Font(18.0f, juce::Font::bold));
    pedalLabel.setJustificationType(juce::Justification::centred);
    pedalLabel.setColour(juce::Label::textColourId, juce::Colours::black);

    maxDelayTimeLabel.setText("Max Delay Time", juce::dontSendNotification);
    maxDelayTimeLabel.setFont(juce::Font(10.0f, juce::Font::plain));
    maxDelayTimeLabel.setJustificationType(juce::Justification::centred);
    maxDelayTimeLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    addAndMakeVisible(maxDelayTimeLabel);

    addAndMakeVisible(maxDelayTimeSlider);
    maxDelayTimeSlider.setSliderStyle(juce::Slider::Rotary);
    maxDelayTimeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    maxDelayTimeAttachment.reset(new SliderAttachment(valueTreeState, "delay-maxDelayTime", maxDelayTimeSlider));

    delayTimeLabel.setText("Delay Time", juce::dontSendNotification);
    delayTimeLabel.setFont(juce::Font(10.0f, juce::Font::plain));
    delayTimeLabel.setJustificationType(juce::Justification::centred);
    delayTimeLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    addAndMakeVisible(delayTimeLabel);

    addAndMakeVisible(delayTimeSlider);
    delayTimeSlider.setSliderStyle(juce::Slider::Rotary);
    delayTimeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    delayTimeAttachment.reset(new SliderAttachment(valueTreeState, "delay-delayTime", delayTimeSlider));

    wetLevelLabel.setText("Wet Level", juce::dontSendNotification);
    wetLevelLabel.setFont(juce::Font(10.0f, juce::Font::plain));
    wetLevelLabel.setJustificationType(juce::Justification::centred);
    wetLevelLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    addAndMakeVisible(wetLevelLabel);

    addAndMakeVisible(wetLevelSlider);
    wetLevelSlider.setSliderStyle(juce::Slider::Rotary);
    wetLevelSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    wetLevelAttachment.reset(new SliderAttachment(valueTreeState, "delay-wetLevel", wetLevelSlider));

    feedbackLabel.setText("Feedback", juce::dontSendNotification);
    feedbackLabel.setFont(juce::Font(10.0f, juce::Font::plain));
    feedbackLabel.setJustificationType(juce::Justification::centred);
    feedbackLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    addAndMakeVisible(feedbackLabel);

    addAndMakeVisible(feedbackSlider);
    feedbackSlider.setSliderStyle(juce::Slider::Rotary);
    feedbackSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    feedbackAttachment.reset(new SliderAttachment(valueTreeState, "delay-feedback", feedbackSlider));

    addAndMakeVisible(&bypassButton);
    bypassButton.setButtonText("OFF");

    bypassButton.setColour(juce::TextButton::buttonColourId, juce::Colours::red);
    bypassButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::green);
    bypassButton.setClickingTogglesState(true);
    bypassAttachment.reset(new ButtonAttachment(valueTreeState, "delay-bypass", bypassButton));


}

DelayComponent::~DelayComponent()
{

}

void DelayComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour::fromRGB(208, 177, 252));

    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

}

void DelayComponent::resized()
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

    auto maxDelayTimeArea = topArea.removeFromLeft(topItemSize);
    maxDelayTimeSlider.setBounds(maxDelayTimeArea.removeFromTop(maxDelayTimeArea.getHeight() - labelHeight));
    maxDelayTimeLabel.setBounds(maxDelayTimeArea.removeFromBottom(labelHeight));

    auto delayTimeArea = topArea.removeFromLeft(topItemSize);
    delayTimeSlider.setBounds(delayTimeArea.removeFromTop(delayTimeArea.getHeight() - labelHeight));
    delayTimeLabel.setBounds(delayTimeArea.removeFromBottom(labelHeight));

    auto wetLevelArea = bottomArea.removeFromLeft(bottomItemSize);
    wetLevelSlider.setBounds(wetLevelArea.removeFromTop(wetLevelArea.getHeight() - labelHeight));
    wetLevelLabel.setBounds(wetLevelArea.removeFromBottom(labelHeight));

    auto feedbackArea = bottomArea.removeFromLeft(bottomItemSize);
    feedbackSlider.setBounds(feedbackArea.removeFromTop(feedbackArea.getHeight() - labelHeight));
    feedbackLabel.setBounds(feedbackArea.removeFromBottom(labelHeight));

    bypassButton.setBounds(bypassArea);

}

void DelayComponent::parameterChanged(const juce::String& parameter, float newValue) {
    if (newValue == 1) {
        bypassButton.setButtonText("ON");
    }
    else {
        bypassButton.setButtonText("OFF");
    }
}